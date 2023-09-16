#include "Character.h"
#include "DxLib.h"
#include "Interface/CharacterEventInterface.h"
#include "../Source/GameObject/UI/UIImplement/HpUI.h"

/// <summary>
/// キャラクターの基礎クラス
/// </summary>
Character::Character()
	: hp(100)
	, MAX_HP(hp)
	, attack(0)
	, deffence(0)
	, move_speed(MOVEMENT_SPEED)
	, is_move(false)
	, is_get_damaged(false)
	, direction(kRIGHT)
	, character_event(nullptr)
	, hp_ui(nullptr)
	, input_direction({0.f,0.f})
	, now_animations()
	, animation_frame(0.f)
	, anim_speed(0.f)
	, min_anim_frame(0.f)
	, max_anim_frame(0.f)
	, initial_velocity(0.f)
	, count_time(0.f)
{
}

Character::~Character() {
}

void Character::Initialize() {
	__super::Initialize();
}

void Character::Finalize() {
	__super::Finalize();
	character_event = nullptr;
	hp_ui = nullptr;
}

void Character::Update(float delta_time) {
	__super::Update(delta_time);
	Move(delta_time);
}

void Character::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);

	int x, y;
	GetPosition().ToInt(x, y);

	int screen_x = x - screen_offset.x;
	int screen_y = y - screen_offset.y;
	switch (body_collision.object_type) {

	case kPLAYER_TYPE:
		
		if (GetDirection() == kLEFT) {
			DrawTurnGraph(screen_x, screen_y, now_animations[animation_frame], true);
		}
		else {
			DrawGraph(screen_x, screen_y, now_animations[animation_frame], true);
		}
		break;
	case kENEMY_TYPE:

		if (GetDirection() == kRIGHT) {
			DrawGraph(screen_x, screen_y, now_animations[animation_frame], true);
		}
		else {
		    DrawTurnGraph(screen_x, screen_y, now_animations[animation_frame], true);
		}
	}
	unsigned int color = GetColor(255, 0, 0);
	int x2 = body_collision.center_position2.x - screen_offset.x - body_collision.box_extent.x;
	int y2 = body_collision.center_position2.y - screen_offset.y - body_collision.box_extent.y;

	//デバック用
	DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);

}

void Character::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);

	const bool* is_hitted_surface = hit_collision.is_hit_surfaces;
	is_hitted_surface++;
	is_hitted_surface++;

	if (*is_hitted_surface) {
		knock_back_dir = { 1.f, 0.f };
	}
	else {
		knock_back_dir = { -1.f, 0.f };
	}
}


void Character::SetHpUi(HpUI& hp_ui) {
	this->hp_ui = &hp_ui;
	this->hp_ui->InitializeHP(hp);
}

void Character::SetDeadState() {
	//ここでは中身を実装しない
	//オーバーライドして中身を実装
}

void Character::GiveDamage(Character& receive_damage_chara, int damage) {
	int true_damage = damage - receive_damage_chara.GetDeffence();

	if (true_damage <= 0) {
		true_damage = 0;
	}

	receive_damage_chara.GetDamage(*this, true_damage);
}

void Character::GetDamage(Character& give_damage_chara, const int damage) {
	is_get_damaged = true;
	this->hp -= damage;

	if (hp_ui != nullptr) {
		this->character_event->UpdateHpUI(this->hp);
	}

	if (hp <= 0) {
		hp = 0;	
		this->SetDeadState();
	}
}

void Character::CallGiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) {
	character_event->GiveDamageEvent(give_gamage_chara, opponent_chara, damage);
}

void Character::UpdateHpUI(const int new_hp) {
	hp_ui->SetHP(new_hp);
}

void Character::Move(float delta_time) {

	Vector2D delta_move_amount = { 0.f, 0.f };
	Vector2D new_position = GetPosition();
	delta_move_amount = input_direction.Normalize() * move_speed * delta_time;

	bool is_can_move_x = character_event->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);
	if (is_can_move_x) {
		new_position.x += delta_move_amount.x;
	}

	input_direction.y += 50.0f;
	float move_amount = input_direction.Normalize().y * move_speed * delta_time;
	delta_move_amount.y += move_amount;

	bool is_can_move_y = character_event->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
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

void Character::ReverseDirection() {

	if (direction == kRIGHT) {
		direction = kLEFT;
	}
	else {
		direction = kRIGHT;
	}
}

bool Character::DeadMove(const float delta_time) {
	initial_velocity += GRAVITY_ACCELARATION;
	input_direction.y = initial_velocity;

	Vector2D delta_move_amount = input_direction.Normalize() * GetSpeed() * 2 * delta_time;
	SetPosition(GetPosition() + delta_move_amount);

	count_time += delta_time;
	if (count_time >= DEAD_MOVE_TIME) {
		count_time = 0.f;
		input_direction.y = 0.f;
		return true;
	}
	return false;
}

void Character::CallDestroy() {
	character_event->DeadEvent(this);
}
