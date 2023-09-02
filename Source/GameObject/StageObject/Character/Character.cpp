#include "Character.h"
#include "DxLib.h"
#include "Interface/CharacterEventInterface.h"

namespace {
	Vector2D back_velocity = { -1.f, 0.f };
}

/// <summary>
/// キャラクターの基礎クラス
/// </summary>
Character::Character()
	: hp(0)
	, attack(0)
	, deffence(0)
	, speed(MOVEMENT_SPEED)
	, bIsMove(false)
	, direction(kRIGHT)
	, ICharacterEvent(nullptr)
	, input_direction({0.f,0.f})
	, now_animations()
	, animation_frame(0.f)
	, anim_speed(0.f)
	, min_anim_frame(0.f)
	, max_anim_frame(0.f)
{
}

Character::~Character() {
}

void Character::Initialize() {
	__super::Initialize();
}

void Character::Finalize() {
	__super::Finalize();
	ICharacterEvent = nullptr;
}

void Character::Update(float delta_time) {
	__super::Update(delta_time);

	Vector2D delta_move_amount = { 0.f, 0.f };
	Vector2D new_position = GetPosition();
	delta_move_amount = input_direction.Normalize() * MOVEMENT_SPEED * delta_time;
	bool is_can_move_x = ICharacterEvent->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);

	if (is_can_move_x) {
		new_position.x += delta_move_amount.x;
	}


	input_direction.y += 50.0f;
	float move_amount = input_direction.Normalize().y * MOVEMENT_SPEED * delta_time;
	delta_move_amount.y += move_amount;

	bool is_can_move_y = ICharacterEvent->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
	if (is_can_move_y) {
		new_position.y += delta_move_amount.y;
	}
	else {
		delta_move_amount.y -= move_amount;
		new_position.y = GetPosition().y;
	}

	Vector2D amount = new_position - GetPosition();
	body_collision.center_position2 += amount;
	//リセットしないと前回のフレームの値に次のフレームの値が足されてしまうのでリセット。
	input_direction = { 0.f, 0.f };
	SetPosition(new_position);
}

void Character::Draw(const Vector2D& screen_offset) {

	__super::Draw(screen_offset);

	int x, y;
	GetPosition().ToInt(x, y);
	switch (GetDirection()) {

	case kLEFT:
		DrawTurnGraph(x, y, now_animations[animation_frame], true);
		break;

	case kRIGHT:
		DrawGraph(x, y, now_animations[animation_frame], true);
		break;
	}

	unsigned int color = GetColor(255, 0, 0);
	int x2 = body_collision.center_position2.x - body_collision.box_extent.x;
	int y2 = body_collision.center_position2.y - body_collision.box_extent.y;

	//デバック用
	DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);

}

void Character::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision)
{
}

void Character::GiveDamage(Character& target)
{
}

void Character::GetDamage(Character& opponent, const int damage)
{
}

void Character::GetDamageRecoil(const float delta_time, const Vector2D& recoil_velocity) {
	Vector2D delta_move_amount;
	Vector2D new_position = GetPosition();
	input_direction = recoil_velocity;
	delta_move_amount = input_direction.Normalize() * MOVEMENT_SPEED * delta_time;
	bool is_can_move_x = ICharacterEvent->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);

	if (is_can_move_x) {
		new_position.x += delta_move_amount.x;
	}

	input_direction.y += 50.0f;
	float move_amount = input_direction.Normalize().y * MOVEMENT_SPEED * delta_time;
	delta_move_amount.y += move_amount;

	bool is_can_move_y = ICharacterEvent->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
	if (is_can_move_y) {
		new_position.y += delta_move_amount.y;
	}
	else {
		delta_move_amount.y -= move_amount;
		new_position.y = GetPosition().y;
	}

	Vector2D amount = new_position - GetPosition();
	body_collision.center_position2 += amount;
	//リセットしないと前回のフレームの値に次のフレームの値が足されてしまうのでリセット。
	input_direction = { 0.f, 0.f };
	SetPosition(new_position);
}
