#include "AttackEnemy.h"
#include "DxLib.h"
#include "../Interface/CharacterEventInterface.h"
#include "../Source/GameObject/StageObject/Weapon/Hand.h"
#include "Interface/IEnemyEvent.h"
AttackEnemy::AttackEnemy()
{
}

AttackEnemy::~AttackEnemy()
{
}

void AttackEnemy::Initialize() {
	__super::Initialize();

	wait_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_rd_wait.bmp"));
	damage_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_rd_damage.bmp"));
	LoadDivGraph(_T("Resources/Images/murasuke_rd_walk.bmp"), 4, 4, 1, 40, 48, walk_enemy_graphic_handle);
	LoadDivGraph(_T("Resources/Images/murasuke_rd_attack.bmp"), 3, 3, 1, 56, 48, attack_enemy_graphic_handle);

	int array_size = sizeof(walk_enemy_graphic_handle) /sizeof(walk_enemy_graphic_handle[0]);
	character_anim.now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
	character_anim.anim_speed = 5.0f;
	character_anim.min_anim_frame = 0.0f;
	character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
	move_amount = range_move / 2;
	enemy_state = EEnemyState::kSERCH;
	equip_weapon = new Hand();
	equip_weapon->Initialize();
	equip_weapon->SetOwner(this);
	SetHp(20);
	game_object_state = EGameObjectState::kPLAYING;
}

void AttackEnemy::Finalize() {

	delete equip_weapon;
	equip_weapon = nullptr;

	__super::Finalize();
}

void AttackEnemy::Update(float delta_time) {

	switch (game_object_state) {
	case EGameObjectState::kPLAYING:
		switch (enemy_state) {
		case EEnemyState::kSERCH:
			break;
		case EEnemyState::kCHASE:
			break;
		case EEnemyState::kATTACK:
			if (character_anim.animation_frame >= character_anim.max_anim_frame - 0.2f) {
				ChangeEnemyState(EEnemyState::kWALK);
			}
			break;
		default:
			break;
		}
		__super::Update(delta_time);
		break;
	case EGameObjectState::kPAUSE:
		break;
	case EGameObjectState::kEND:
		break;
	}
}

void AttackEnemy::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);

	equip_weapon->Draw(screen_offset);
}

void AttackEnemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);
}

void AttackEnemy::Move(float delta_time) {

	if (enemy_state != EEnemyState::kDEAD) {
		SetSerchRange();
		if (enemy_event->SerchPlayer(this)) {
			ChangeEnemyState(EEnemyState::kATTACK);
		}
	}
	__super::Move(delta_time);
}

void AttackEnemy::EnterState() {

	if (enemy_state == prev_state)
	{
		return;
	}
	prev_state = enemy_state;

	switch (enemy_state) {
		case EEnemyState::kSERCH: {
			break;
		}
		case EEnemyState::kATTACK:{
			character_anim.now_animations.clear();
			int array_size = sizeof(attack_enemy_graphic_handle) / sizeof(attack_enemy_graphic_handle[0]);
			SetSpeed(GetSpeed() * 1.2f);
			character_anim.now_animations.assign(attack_enemy_graphic_handle, attack_enemy_graphic_handle + array_size);
			character_anim.anim_speed = 5.0f;
			character_anim.min_anim_frame = 0.0f;
			character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
			equip_weapon->SetWeaponDirection();
			equip_weapon->SetAttackRange(body_collision);
			character_event->AddWeapon(*equip_weapon);
			break;
		}
	}
	__super::EnterState();

}

void AttackEnemy::ExitState() {
	switch (enemy_state) {
	case EEnemyState::kSERCH:
		break;
	case EEnemyState::kATTACK:
		SetSpeed(ENEMY_MOVEMENT_SPEED);
		character_event->RemoveWeapon(equip_weapon);
		break;
	}
	__super::ExitState();
}

void AttackEnemy::ChangeEnemyState(const EEnemyState new_state) {

	ExitState();
	enemy_state = new_state;
	EnterState();
}