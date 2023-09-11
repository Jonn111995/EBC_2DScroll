#include "SampleScene.h"
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


SampleScene::SampleScene()
{
}

bool SampleScene::CheckCanMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {
	return field->CheckMove(move_to_position, move_amount, collision);
}

bool SampleScene::CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) {
	return field->CheckStande(move_to_position, collision);
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

void SampleScene::Initialize()
{
	// 親クラスのInitialize()
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
	player = CreateObject<Player>();
	player->SetICharacterEvent(this);
	player->SetIPlayerEvent(this);
	player->SetHpUi(*hp_ui);
	field->AddStageObject(*player);

	/*Enemy* enemy = CreateObject<Enemy>();
	enemy->SetICharacterEvent(this);
	enemy->SetIEnemyEvent(this);
	field->AddStageObject(*enemy);*/

	AttackEnemy* enemy = CreateObject<AttackEnemy>();
	enemy->SetICharacterEvent(this);
	enemy->SetIEnemyEvent(this);
	field->AddStageObject(*enemy);
	
	field->InitializeStageObjectPosition();

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

				if (iterator == oppnent_iterator) {
					continue;
				}

				BoxCollisionParams opponent = (*oppnent_iterator)->GetBodyCollision();
				if (CheckBoxCollision(*iterator, (*iterator)->GetBodyCollision(), opponent)) {
					(*iterator)->OnHitBoxCollision(*oppnent_iterator, opponent);
				}

				/*opponent = (*iterator)->GetBodyCollision();
				if (CheckBoxCollision(*oppnent_iterator, (*oppnent_iterator)->GetBodyCollision(), opponent)) {
					(*oppnent_iterator)->OnHitBoxCollision(*iterator, opponent);
				}*/
			}
		}
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

