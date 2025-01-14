#include "Enemy.h"
#include "DxLib.h"
#include "../Source/GameObject/StageObject/Character/Interface/CharacterEventInterface.h"

Enemy::Enemy()
	: wait_enemy_graphic_handle()
	, walk_enemy_graphic_handle()
	, damage_enemy_graphic_handle()
	, enemy_event(nullptr)
	, enemy_state(EEnemyState::kWALK)
	, range_move(300.f)
	, move_amount(0.f)
	, prev_state(EEnemyState::kWALK)
	
{
	SetHp(10);
	SetAttack(10);
}

Enemy::~Enemy() {
}


void Enemy::Initialize() {
	__super::Initialize();

	wait_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_pp_wait.bmp"));
	damage_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_pp_damage.bmp"));
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), 4, 4, 1, 40, 48, walk_enemy_graphic_handle);

	SetDirection(kLEFT);

	int array_size = sizeof(walk_enemy_graphic_handle) / sizeof(walk_enemy_graphic_handle[0]);
	character_anim.now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
	SetSpeed(ENEMY_MOVEMENT_SPEED);
	character_anim.anim_speed = 5.0f;
	character_anim.min_anim_frame = 0.0f;
	character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
	move_amount = range_move / 2;

	body_collision.object_type = kENEMY_TYPE;
	body_collision.center_position = Vector2D(20, 28);
	body_collision.box_extent = Vector2D(10.f, 18.f);
	body_collision.hit_object_types =  kPLAYER_TYPE | kWEAPON_TYPE;
	enemy_state = EEnemyState::kWALK;
	game_object_state = EGameObjectState::kPLAYING;
}

void Enemy::Finalize() {
	enemy_event = nullptr;

	__super::Finalize();
}

void Enemy::Update(float delta_time) {

	switch (game_object_state) {
	case EGameObjectState::kPLAYING:

		switch (enemy_state) {
		case EEnemyState::kDAMAGE:
			count_time += delta_time;

			if (count_time < 0.1f) {
				input_direction = knock_back_dir;
			}
			else if (1.f < count_time) {
				is_no_damage = false;
				count_time = 0.f;
				ChangeEnemyState(EEnemyState::kWALK);
			}
			break;

		case EEnemyState::kWALK:
			break;

		case EEnemyState::kDEAD:
			if (DeadMove(delta_time)) {
				CallDestroy();
			}
			break;
		default:
			break;
		}

		__super::Update(delta_time);

		if (character_anim.animation_frame <= character_anim.min_anim_frame) {
			character_anim.animation_frame = character_anim.min_anim_frame;
		}

		//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
		if (character_anim.animation_frame >= character_anim.now_animations.size()) {
			character_anim.animation_frame = character_anim.min_anim_frame;
		}

		character_anim.animation_frame += delta_time * character_anim.anim_speed;

		//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
		if (character_anim.animation_frame >= character_anim.max_anim_frame) {
			character_anim.animation_frame = character_anim.min_anim_frame;
		}
		break;

	case EGameObjectState::kPAUSE:
		break;
	case EGameObjectState::kEND:
		
		break;
	}
}

void Enemy::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}

void Enemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {

	if (enemy_state == EEnemyState::kDEAD) {
		return;
	}

	if (hit_collision.object_type & kPLAYER_TYPE) {
		character_event->GiveDamageEvent(*this, *hit_object, GetAttack());
	}
	else if (hit_collision.object_type & kWEAPON_TYPE) {
		ChangeEnemyState(EEnemyState::kDAMAGE);
	}
	__super::OnHitBoxCollision(hit_object, hit_collision);
}

void Enemy::SetDeadState() {
	ChangeEnemyState(EEnemyState::kDEAD);
}

void Enemy::Move(float delta_time) {

	if (move_amount <= 0) {
		move_amount = range_move / 2;
		SetDirection(kLEFT);
	}
	else if (move_amount >= range_move) {
		move_amount = range_move / 2;
		SetDirection(kRIGHT);
	}

	switch (GetDirection()) {
	case kRIGHT:
		move_amount--;
		input_direction.x = -10.f;
		break;
	case kLEFT:
		move_amount++;
		input_direction.x = 10.f;
		break;
	}
	__super::Move(delta_time);
}

bool Enemy::DeadMove(const float delta_time) {
	return __super::DeadMove(delta_time);
}

void Enemy::CallDestroy() {
	game_object_state = EGameObjectState::kEND;
	__super::CallDestroy();
}

void Enemy::SetSerchRange() {

	int direct_ajust = 0;
	if (GetDirection() == kRIGHT) {
		direct_ajust = -1;
	}
	else {
		direct_ajust = 1;
	}

	float center_x = body_collision.center_position2.x + (body_collision.box_extent.x * 4) * direct_ajust;
	serch_range.serch_range_center = Vector2D(center_x, body_collision.center_position2.y);
	serch_range.serch_range_extent = { (body_collision.box_extent.x * 3), body_collision.box_extent.y };
}


void Enemy::EnterState() {

	switch (enemy_state) {
	case EEnemyState::kWALK:
	{
		int array_size = sizeof(walk_enemy_graphic_handle) / sizeof(walk_enemy_graphic_handle[0]);
		character_anim.now_animations.clear();
		character_anim.now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
		character_anim.min_anim_frame = 0.0f;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
	}
		break;
	case EEnemyState::kDEAD:
		body_collision.collision_type = kOverlap;
		initial_velocity = INITIAL_JUMP_VELOCITY;
		//無敵状態のプレイヤーに当たった時にもDamage処理をしたいので、breakしていない
	case EEnemyState::kDAMAGE:
		SetSpeed(50.f);
		character_anim.now_animations.clear();
		character_anim.now_animations.push_back(damage_enemy_graphic_handle);
		character_anim.min_anim_frame = 0.0f;
		character_anim.animation_frame = character_anim.min_anim_frame;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
		break;
	}
}

void Enemy::ExitState() {

	switch (enemy_state) {
	case EEnemyState::kWALK:
		break;
	case EEnemyState::kDAMAGE:
		break;
	case EEnemyState::kDEAD:
		body_collision.collision_type = kBLOCK;
		break;
	}
}

void Enemy::ChangeEnemyState(const EEnemyState new_state) {
	ExitState();
	enemy_state = new_state;
	EnterState();
}
