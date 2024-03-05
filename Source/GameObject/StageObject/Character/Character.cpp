#include "Character.h"
#include "DxLib.h"
#include "../Source/System/SoundManager.h"
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
	, direction(kRIGHT)
	, character_event(nullptr)
	, hp_ui(nullptr)
	, input_direction({0.f,0.f})
	//, now_animations()
	/*, animation_frame(0.f)
	, anim_speed(0.f)
	, min_anim_frame(0.f)
	, max_anim_frame(0.f)*/
	, initial_velocity(0.f)
	, count_time(0.f)
{
}

Character::~Character() {
}

void Character::Initialize() {
	__super::Initialize();
	SoundManager* sound_manager = SoundManager::GetInstance();
	get_damage_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/Action/se_get_damage.mp3");
	//character_anim = new Animation;
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
			DrawTurnGraph(screen_x, screen_y, character_anim.now_animations[character_anim.animation_frame], true);
		}
		else {
			DrawGraph(screen_x, screen_y, character_anim.now_animations[character_anim.animation_frame], true);
		}
		break;
	case kENEMY_TYPE:

		if (GetDirection() == kRIGHT) {
			DrawGraph(screen_x, screen_y, character_anim.now_animations[character_anim.animation_frame], true);
		}
		else {
		    DrawTurnGraph(screen_x, screen_y, character_anim.now_animations[character_anim.animation_frame], true);
		}
	}
	unsigned int color = GetColor(255, 0, 0);
	int x2 = body_collision.center_position2.x - screen_offset.x - body_collision.box_extent.x;
	int y2 = body_collision.center_position2.y - screen_offset.y - body_collision.box_extent.y;

	//デバック用
	//DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);

}

void Character::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);

	//衝突した辺を取得
	//4つの要素を持ったbool配列
	//上、下、右、左の順でbool値が並ぶ
	const bool* is_hitted_surface = hit_collision.is_hit_surfaces;
	//その配列のポイントをインクリメントして、右のbool値を参照
	is_hitted_surface++;
	is_hitted_surface++;

	//左右の辺、どちらに当たったかで分岐
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
	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->PlayLoadSound(get_damage_sound);
	is_no_damage = true;
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
	Vector2D new_position = { 0.f, 0.f };

	input_direction.y += GRAVITY_ACCELARATION;
	//入力された方向ベクトルを元に、移動量を計算
	delta_move_amount = input_direction.Normalize() * move_speed * delta_time;

	//ここから当たり判定
	bool is_can_move_x = character_event->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);
	new_position.x = UpdateXPosition(is_can_move_x, delta_move_amount.x);

	bool is_can_move_y = character_event->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
	new_position.y = UpdateYPosition(is_can_move_y, delta_move_amount.y);

	//中心座標を更新
	Vector2D amount = new_position - GetPosition();
	body_collision.center_position2 += amount;

	//リセットしないと前回のフレームの値に次のフレームの値が足されてしまうのでリセット。
	input_direction = { 0.f, 0.f };

	SetPosition(new_position);
}

float Character::UpdateXPosition(const bool is_can_move_to_x, const float update_x_amount) {

	if (is_can_move_to_x) {
		return GetPosition().x + update_x_amount;
	}
	else {
		return GetPosition().x;
	}
}

float Character::UpdateYPosition(const bool is_can_move_to_y, const float update_y_amount) {

	if (is_can_move_to_y) {
		return GetPosition().y + update_y_amount;
	}
	else {
		return GetPosition().y;
	}
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
