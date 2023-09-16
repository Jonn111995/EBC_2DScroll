#include "SampleScene.h"
#include "../Camera.h"
#include "../Source/System/ScreenInfo.h"
#include "../../GameObject/SampleObject/SampleObject.h"
#include "../Source/GameObject/StageObject/Character/Player/Player.h"
#include "../Source/GameObject/Field/Field.h"
#include "../Source/GameObject/StageObject/Character/Enemy/Enemy.h"
#include "../Source/GameObject/StageObject/Character/Enemy/AttackEnemy.h"
#include "../Source/GameObject/StageObject/Weapon/BaseWeapon.h"
#include "../Source/GameObject/StageObject/StageObject.h"
#include "../Source/GameObject/GameState/GameState.h"
#include "../Source/GameObject/UI/UIImplement/GameStateUI.h"
#include "../Source/GameObject/UI/UIImplement/HpUI.h"
#include "../Source/GameObject/RespawnManager/RespawnManager.h"
#include "../Source/GameObject/StageObject/Item/Coin.h"
#include "../Source/GameObject/StageObject/Item/InvincibleCan.h"
#include "../Source/GameObject/StageObject/KillObject/KillObject.h"



SampleScene::SampleScene()
{
}

bool SampleScene::CheckCanMoveToX(const Vector2D& now_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {
	return field->CheckMoveToX(now_to_position, move_amount, collision);
}

bool SampleScene::CheckCanMoveToY(const Vector2D& now_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {
	return field->CheckMoveToY(now_to_position, move_amount, collision);
}

void SampleScene::AddWeapon(BaseWeapon& weapon) {
	field->AddStageObject(weapon);
}

void SampleScene::RemoveWeapon(BaseWeapon* weapon) {
	field->DeleteStageObject(weapon);
}

void SampleScene::GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) {

	Character* receive_damage_chara = nullptr;
	Character* chara = dynamic_cast<Character*>(&give_gamage_chara);
	
	if (chara != nullptr) {
		for (auto& obj : field->GetStageObjectList()) {
			if (obj == &opponent_chara) {
				receive_damage_chara = dynamic_cast<Character*>(obj);
			}
		}

		if(receive_damage_chara != nullptr ) {
			if (!receive_damage_chara->GetIsGetDmaged()) {
				chara->GiveDamage(*receive_damage_chara, damage);
			}
		}
	}
}

void SampleScene::UpdateHpUI(const int now_hp) {
	player->UpdateHpUI(now_hp);
}

void SampleScene::UpdateScoreUI(const int new_score) {
	game_state_ui->SetScore(new_score);
}

void SampleScene::UpdateRespawnRemainUI(const int respawn_remain) {
	game_state_ui->SetRespawn(respawn_remain);
}

void SampleScene::DeadEvent(const StageObject* dead_object) {
	BookDeleteObject(dead_object);
}

void SampleScene::KillEvent(const StageObject* kill_target) {

	if (kill_target == player) {
		player->SetDeadState();
	}
}

bool SampleScene::ExecuteRespawn() {
	game_state->ReduceRespawnRemain();
	//残機があるか確認
	if (game_state->GetRespawnRemain() == 0) {
		return false;
	}

	respawn_manager->RespawnObject();
	hp_ui->InitializeHP(player->GetHp());
	return true;
}

void SampleScene::ScoreUp() {
	game_state->IncreaseScore();
}

void SampleScene::ChangeInvincible(const float invincible_time) {
	player->SetInvincibleState();
	player->SetIsUseItem(true);
	player->SetInvincibleTime(invincible_time);
}

void SampleScene::DestroyItem(StageObject& delete_object) {
	BookDeleteObject(&delete_object);
}

void SampleScene::GetDrawInformPositon(Vector2D& draw_postion) {
	BoxCollisionParams player_collision = player->GetBodyCollision();
	draw_postion = Vector2D(player_collision.center_position2.x, player_collision.center_position2.y - player_collision.box_extent.y * 2 );
}


bool SampleScene::SerchPlayer(Enemy* enemy) {

	AttackEnemy* attack_enemy = dynamic_cast<AttackEnemy*>(enemy);
	if (attack_enemy != nullptr) {

		BoxCollisionParams player_collision = player->GetBodyCollision();
		BoxCollisionParams enemy_serch_range;
		enemy_serch_range.center_position2 = enemy->GetSerchRange().serch_range_center;
		enemy_serch_range.box_extent = enemy->GetSerchRange().serch_range_extent;
		
		bool check = CheckBoxCollision(attack_enemy->GetEquipWeapon(), enemy_serch_range, player_collision);

		return check;
	}

	return false;
}

void SampleScene::UpdateTimeUI(int remain_time) {
	game_state_ui->SetTime(remain_time);
}

void SampleScene::TimeOver() {

}

void SampleScene::CreateStageObject() {

	if (field == nullptr) {
		return;
	}

	std::vector<CreateObjectInfo> create_object_info_list = field->GetCreateObjectInfo();

	for (auto& create_object_info : create_object_info_list) {
		StageObject* created_object = nullptr;

		switch (create_object_info.object_type) {

		case kPLAYER_START:
			if (player != nullptr) { continue; };

			player = CreateObject<Player>(create_object_info.initiali_position);
			player->SetICharacterEvent(this);
			player->SetIPlayerEvent(this);

			created_object = player;
			break;
		case kBASE_ENEMY:
		{
			Enemy* enemy = CreateObject<Enemy>(create_object_info.initiali_position);
			enemy->SetICharacterEvent(this);
			enemy->SetIEnemyEvent(this);
			created_object = enemy;
			break;
		}
		case kATTACK_ENEMY:
		{
			AttackEnemy* enemy = CreateObject<AttackEnemy>(create_object_info.initiali_position);
			enemy->SetICharacterEvent(this);
			enemy->SetIEnemyEvent(this);
			created_object = enemy;
			break;
		}
		case kCOIN:
		{
			Coin* coin = CreateObject<Coin>(create_object_info.initiali_position);
			coin->SetIItemEvent(this);
			created_object = coin;
			
			break;
		}
		case kINVINCIBLE_CAN:
		{
			InvincibleCan* invincible_can = CreateObject<InvincibleCan>(create_object_info.initiali_position);
			invincible_can->SetIItemEvent(this);
			created_object = invincible_can;
			break;
		}
		case kKILL_POINT:
		{
			KillObject* kill_object = CreateObject<KillObject>(create_object_info.initiali_position);
			kill_object->SetIStageObjectEvent(this);
			kill_object->SetIKillEvent(this);
			created_object = kill_object;
			break;
		}
		default:
			continue;
			break;
		}

		if (created_object != nullptr) {
			field->SetInitialPosition(*created_object);
			field->AddStageObject(*created_object);
		}
	};
	
}

void SampleScene::Initialize() {
	__super::Initialize();

	ScreenInfo::CreateInstance();
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	game_state = CreateObject<GameState>();
	game_state->SetIGameStateEvent(this);
	game_state_ui = CreateObject<GameStateUI>();
	hp_ui = CreateObject<HpUI>();
	
	field = CreateObject<Field>();
	field->InitializeField("C/Users/n5919/EBC_2DScroll/Source/CSVFile/mapdata.csv");

	CreateStageObject();

	game_state_ui->SetScore(game_state->GetScore());
	game_state_ui->SetRespawn(game_state->GetRespawnRemain());
	player->SetHpUi(*hp_ui);
	respawn_manager = CreateObject<RespawnManager>();
	respawn_manager->SetCheckPointList(field->GetCheckPointList());
	respawn_manager->SetObserveObject(*player);

	camera->UpdateCamera(player->GetPosition());

	play_scene_state = EPlaySceneState::kPLAYING;
}

void SampleScene::Finalize() {
	// 親クラスのFinalize()
	__super::Finalize();
}

SceneType SampleScene::Update(float delta_seconds) {
	switch (play_scene_state) {
	case EPlaySceneState::kPRE_START:
		//ここでキャラを動かないようにする
		break;
	case EPlaySceneState::kSTART_UI:
		break;
	case EPlaySceneState::kWAIT_END_START_UI:
		break;
	case EPlaySceneState::kPLAYING:
	{
		if (game_state != nullptr && game_state->GetGameObjectState() == EGameObjectState::kPRE_START) {
			game_state->SetPlaying();
			game_state_ui->OnActive();
			hp_ui->OnActive();
		}

		SceneType now_scen_type = __super::Update(delta_seconds);

		std::vector<StageObject*> stage_obj_list = field->GetStageObjectList();

		for (auto iterator = stage_obj_list.begin(); iterator != stage_obj_list.end(); ++iterator) {
			for (auto oppnent_iterator = stage_obj_list.begin(); oppnent_iterator != stage_obj_list.end(); ++oppnent_iterator) {

				BoxCollisionParams own = (*iterator)->GetBodyCollision();
				BoxCollisionParams opponent = (*oppnent_iterator)->GetBodyCollision();

				if (iterator == oppnent_iterator || (*oppnent_iterator)->GetGameObjectState() == EGameObjectState::kEND) {
					continue;
				}
				if (own.collision_type == kOverlap || opponent.collision_type == kOverlap) {
					continue;
				}

				if (CheckBoxCollision(*iterator, own, opponent)) {
					(*iterator)->OnHitBoxCollision(*oppnent_iterator, opponent);
				}
			}
		}

		camera->UpdateCamera(player->GetPosition());

		return now_scen_type;
		break;
	}
	case EPlaySceneState::kFINISH_UI:
		break;
	case EPlaySceneState::kWAIT_END_FINISH_UI:
		break;
	case EPlaySceneState::kPAUSE:
		break;
	case EPlaySceneState::kFINISH:
		break;
	case EPlaySceneState::kFinished:
		break;
	}
}

void SampleScene::Draw()
{
	// 親クラスのDraw()
	__super::Draw();
}

