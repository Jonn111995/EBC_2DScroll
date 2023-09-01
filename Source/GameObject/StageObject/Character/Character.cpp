#include "Character.h"
#include "DxLib.h"
#include "Interface/CharacterEventInterface.h"

/// <summary>
/// �L�����N�^�[�̊�b�N���X
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
	, now_animations({0})
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
		//delta_move_amount.y -= move_amount;
		new_position.y = GetPosition().y;
	}

	//���Z�b�g���Ȃ��ƑO��̃t���[���̒l�Ɏ��̃t���[���̒l��������Ă��܂��̂Ń��Z�b�g�B
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
	int x2 = x + body_collision.center_position.x - body_collision.box_extent.x;
	int y2 = y + body_collision.center_position.y - body_collision.box_extent.y;

	//�f�o�b�N�p
	DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);
}

void Character::GiveDamage(Character& target)
{
}

void Character::GetDamage(Character& opponent, const int damage)
{
}
