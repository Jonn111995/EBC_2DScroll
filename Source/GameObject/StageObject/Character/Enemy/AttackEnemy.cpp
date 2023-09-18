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

	int array_size = sizeof(*walk_enemy_graphic_handle);
	now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
	anim_speed = 5.0f;
	min_anim_frame = 0.0f;
	max_anim_frame = now_animations.size() - 1.0f;
	move_amount = range_move / 2;
	enemy_state = EEnemyState::kSERCH;
	equip_weapon = new Hand();
	equip_weapon->Initialize();
	equip_weapon->SetOwner(this);
	//equip_weapon->SetWeaponType(EWeaponType::KENEMY);
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
			Move(delta_time);
			break;
		case EEnemyState::kCHASE:
			break;
		case EEnemyState::kATTACK:
			if (animation_frame >= max_anim_frame - 0.2f) {
				ChangeEnemyState(EEnemyState::kSERCH);
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
		__super::Update(delta_time);
		break;
	}
}

void AttackEnemy::Draw(const Vector2D& screen_offset) {

	//int x2 = serch_range.serch_range_center.x - serch_range.serch_range_extent.x -screen_offset.x;
	//int y2 = serch_range.serch_range_center.y - serch_range.serch_range_extent.y -screen_offset.y;
	////デバック用
	//DrawBox(x2, y2, x2 + serch_range.serch_range_extent.x * 2, y2 + serch_range.serch_range_extent.y * 2, GetColor(255, 0, 0), false);

	__super::Draw(screen_offset);

	equip_weapon->Draw(screen_offset);
}

void AttackEnemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);
}

void AttackEnemy::Move(float delta_time) {

	SetSerchRange();
	if (enemy_event->SerchPlayer(this)) {
		ChangeEnemyState(EEnemyState::kATTACK);
	}
	__super::Move(delta_time);
}

void AttackEnemy::EnterState() {

	switch (enemy_state) {
		case EEnemyState::kSERCH: {
			int array_size = sizeof(*walk_enemy_graphic_handle);
			SetSpeed(GetSpeed() / 10.f);
			now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
			anim_speed = 5.0f;
			min_anim_frame = 0.0f;
			max_anim_frame = now_animations.size() - 1.0f;
			break;
		}
		case EEnemyState::kATTACK:{
			//SetSpeed(MOVEMENT_SPEED * 1.2);
			int array_size = sizeof(*attack_enemy_graphic_handle);
			SetSpeed(GetSpeed() * 10.f);
			now_animations.assign(attack_enemy_graphic_handle, attack_enemy_graphic_handle + array_size);
			anim_speed = 5.0f;
			min_anim_frame = 0.0f;
			max_anim_frame = now_animations.size() - 1.0f;
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
		//SetSpeed(MOVEMENT_SPEED);
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