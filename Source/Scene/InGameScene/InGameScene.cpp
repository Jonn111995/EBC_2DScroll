#include "DxLib.h"

#include <cassert>

#include "InGameScene.h"
#include "../Camera.h"
#include "../Source/System/ScreenInfo.h"
#include "../Source/System/SoundManager.h"
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
#include "../Source/GameObject/UI/UIImplement/StartUI.h"
#include "../Source/GameObject/UI/UIImplement/FinishUI.h"
#include "../Source/GameObject/RespawnManager/RespawnManager.h"
#include "../Source/GameObject/StageObject/Item/Coin.h"
#include "../Source/GameObject/StageObject/Item/InvincibleCan.h"
#include "../Source/GameObject/StageObject/KillObject/KillObject.h"
#include "../Source/GameObject/StageObject/Goal/Goal.h"

InGameScene::InGameScene()
	: in_game_back_graphic(0)
	, in_game_bgm(0)
	, invincible_bgm(0)
	, goal_sound(0)
	, game_over_bgm(0)
	, play_scene_state(EPlaySceneState::kPRE_START)
	, field(nullptr)
	, player(nullptr)
	, respawn_manager(nullptr)
	, game_state(nullptr)
	, game_state_ui(nullptr)
	, hp_ui(nullptr)
	, start_ui(nullptr)
	, finish_ui(nullptr)
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize() {
	__super::Initialize();

	//オブジェクトの生成と初期化
	assert(CreateGameState());
	assert(CreateUI());
	assert(CreateStage());
	assert(CreateStageObject());

	respawn_manager = CreateObject<RespawnManager>();
	respawn_manager->SetIStageObjectEvent(this);
	respawn_manager->SetCheckPointList(field->GetCheckPointList());
	respawn_manager->SetObserveObject(*player);
	camera->UpdateCamera(player->GetPosition());

	//描画させないようにしたいため
	for (auto& object : objects) {
		object->OffActive();
	}

	//リソースの読み込み
	in_game_back_graphic = LoadGraph("Resources/Images/pipo-bg001.jpg");
	SoundManager* sound_manager = SoundManager::GetInstance();
	goal_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/se_goal.mp3");
	in_game_bgm = sound_manager->LoadSoundResource("Resources/Sounds/BGM/InGameBGM_28.mp3");
	invincible_bgm = sound_manager->LoadSoundResource("Resources/Sounds/BGM/bgm_Invincible.mp3");
	game_over_bgm = sound_manager->LoadSoundResource("Resources/Sounds/BGM/bgm_game_over.mp3");

	sound_manager->PlayLoadSound(in_game_bgm, true);
	play_scene_state = EPlaySceneState::kPRE_START;
}

void InGameScene::Finalize() {
	__super::Finalize();

	//TODO::仮でコメントアウト
	//SoundManager::GetInstance()->UnLoadAllSoundResource();
	DeleteGraph(in_game_back_graphic);
	DeleteSoundMem(in_game_bgm);
	DeleteSoundMem(invincible_bgm);
	DeleteSoundMem(goal_sound);
	DeleteSoundMem(game_over_bgm);

	in_game_back_graphic = 0;
	in_game_bgm = 0;	
	invincible_bgm = 0;
	goal_sound = 0;
	game_over_bgm = 0;
	field = nullptr;
	player = nullptr;
	respawn_manager = nullptr;
	game_state = nullptr;
	game_state_ui = nullptr;
	hp_ui = nullptr;
	start_ui = nullptr;
	finish_ui = nullptr;
}

SceneType InGameScene::Update(float delta_seconds) {
	switch (play_scene_state) {
	case EPlaySceneState::kPRE_START:
		//ここでキャラを動かないようにする
		for (auto& object : objects) {
			object->SetPause();
		}
		field->OnActive();
		play_scene_state = EPlaySceneState::kSTART_UI;
		break;
	case EPlaySceneState::kSTART_UI:
		//StartUIを出す
		start_ui->SetPlaying();
		start_ui->OnActive();
		start_ui->SetUIState(EUIState::kSHOW);
		play_scene_state = EPlaySceneState::kWAIT_END_START_UI;
		break;
	case EPlaySceneState::kWAIT_END_START_UI:
		//StartUIの表示が終わるまで待機
		break;
	case EPlaySceneState::kPLAYING:
	{
		//ゲーム進行中
		now_scene_type = __super::Update(delta_seconds);
		std::vector<StageObject*> stage_obj_list = field->GetStageObjectList();

		RemoveStageObject(stage_obj_list);
		CheckCollisionHit(stage_obj_list);
		camera->UpdateCamera(player->GetPosition());

		return now_scene_type;
		break;
	}
	case EPlaySceneState::kFINISH_UI:
		//終了時UIを表示
		
		SoundManager::GetInstance()->StopSound(in_game_bgm);
		game_state->SetPause();
		game_state->OffActive();
		
		respawn_manager->SetEnd();
		respawn_manager->OffActive();

		if (game_state->GetbIsClear()) {
			finish_ui->SetDisplayString("GAME CLEAR!!!");
			SoundManager::GetInstance()->PlayLoadSound(goal_sound);
		}
		else {
			finish_ui->SetDisplayString("GAME OVER...");
			SoundManager::GetInstance()->PlayLoadSound(game_over_bgm);
		}
		finish_ui->OnActive();
		finish_ui->SetUIState(EUIState::kSHOW);
		play_scene_state = EPlaySceneState::kWAIT_END_FINISH_UI;
		break;
	case EPlaySceneState::kWAIT_END_FINISH_UI:
		player->SetEnd();
		//FInishUIの表示終了を待機。
		break;
	case EPlaySceneState::kPAUSE:
		//TODO::未実装::ポーズ中
		break;
	case EPlaySceneState::kFINISH:
	{
			play_scene_state = EPlaySceneState::kFinished;
			return now_scene_type = CheckExistNextStage();
	}
	break;
	case EPlaySceneState::kFinished:
		return now_scene_type;
		break;
	}
	return 	now_scene_type = __super::Update(delta_seconds);
}

void InGameScene::Draw() {
	DrawGraph(0, 0, in_game_back_graphic, true);
	__super::Draw();
}

//~Begin Override Event from Interface.
bool InGameScene::CheckCanMoveToX(const Vector2D& now_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {
	return field->CheckMoveToX(now_to_position, move_amount, collision);
}

bool InGameScene::CheckCanMoveToY(const Vector2D& now_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {
	return field->CheckMoveToY(now_to_position, move_amount, collision);
}

void InGameScene::AddWeapon(BaseWeapon& weapon) {
	field->AddStageObject(weapon);
}

void InGameScene::RemoveWeapon(BaseWeapon* weapon) {
	field->DeleteStageObject(weapon);
}

void InGameScene::GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) {

	Character* receive_damage_chara = nullptr;
	Character* chara = dynamic_cast<Character*>(&give_gamage_chara);

	if (chara != nullptr) {
		for (auto& obj : field->GetStageObjectList()) {
			if (obj == &opponent_chara) {
				receive_damage_chara = dynamic_cast<Character*>(obj);
			}
		}

		if (receive_damage_chara != nullptr) {
			if (!receive_damage_chara->GetIsNoDamage()) {
				chara->GiveDamage(*receive_damage_chara, damage);
			}
		}
	}
}

void InGameScene::UpdateHpUI(const int now_hp) {
	player->UpdateHpUI(now_hp);
}

void InGameScene::UpdateScoreUI(const int new_score) {
	game_state_ui->SetScore(new_score);
}

void InGameScene::UpdateRespawnRemainUI(const int respawn_remain) {
	game_state_ui->SetRespawn(respawn_remain);
}

void InGameScene::DeadEvent(StageObject* dead_object) {
	BookDeleteObject(dead_object);
}

void InGameScene::KillEvent(const StageObject* kill_target) {
	if (kill_target == player && player->GetPlayerState() != EPlayerState::kDEAD) {
		player->SetDeadState();
	}
}

bool InGameScene::ExecuteRespawn() {
	game_state->ReduceRespawnRemain();
	//残機があるか確認
	if (game_state->GetRespawnRemain() == 0) {
		//ゲームオーバー処理
		game_state->SetbIsClear(false);
		play_scene_state = EPlaySceneState::kFINISH_UI;
		return false;
	}

	respawn_manager->RespawnObject();
	hp_ui->InitializeHP(player->GetHp());
	return true;
}

bool InGameScene::CheckCanFinishUI() {
	if (!CheckSoundMem(goal_sound)) {
		return true;
	}
	return false;
}

void InGameScene::FInishUI(UIComponent* ui_component) {
	//削除もあり。
	ui_component->SetEnd();
	ui_component->OffActive();

	switch (play_scene_state) {
	case EPlaySceneState::kWAIT_END_START_UI:

		for (auto& object : objects) {
			object->SetPlaying();
			object->OnActive();
		}

		start_ui->OffActive();
		finish_ui->OffActive();

		play_scene_state = EPlaySceneState::kPLAYING;
		break;

	case EPlaySceneState::kWAIT_END_FINISH_UI:
		play_scene_state = EPlaySceneState::kFINISH;
		break;
	}
}

void InGameScene::GameClear() {
	game_state->SetbIsClear(true);
	play_scene_state = EPlaySceneState::kFINISH_UI;
}

void InGameScene::ScoreUp() {
	game_state->IncreaseScore();
}

void InGameScene::ChangeInvincible(const float invincible_time) {
	player->SetInvincibleState();
	player->SetIsUseItem(true);
	player->SetInvincibleTime(invincible_time);

	//TODO::仮でコメントアウト
	/*SoundManager::GetInstance()->StopSound(in_game_bgm);
	SoundManager::GetInstance()->PlayLoadSound(invincible_bgm);*/
}

void InGameScene::DestroyItem(StageObject& delete_object) {
	BookDeleteObject(&delete_object);
}

void InGameScene::GetDrawInformPositon(Vector2D& draw_postion) {
	BoxCollisionParams player_collision = player->GetBodyCollision();
	draw_postion = Vector2D(player_collision.center_position2.x, player_collision.center_position2.y - player_collision.box_extent.y * 2);
}

bool InGameScene::SerchPlayer(Enemy* enemy) {

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

void InGameScene::UpdateTimeUI(int remain_time) {
	game_state_ui->SetTime(remain_time);
}

void InGameScene::TimeOver() {
	game_state->SetbIsClear(false);
	play_scene_state = EPlaySceneState::kFINISH_UI;
}

void InGameScene::FinishInvincibleState() {
	SoundManager::GetInstance()->StopSound(invincible_bgm);
	SoundManager::GetInstance()->PlayLoadSound(in_game_bgm);
}
//~ End Overide Event from Interface

bool InGameScene::CreateGameState() {
	game_state = CreateObject<GameState>();
	if (game_state == nullptr) {
		return false;
	}

	game_state->SetIGameStateEvent(this);
	game_state->SetScore(inherit_info.score);
	game_state->SetRespawnRemain(inherit_info.respawn_remain);
	return true;
}

bool InGameScene::CreateUI() {
	if (game_state == nullptr) {
		return false;
	}

	game_state_ui = CreateObject<GameStateUI>();
	hp_ui = CreateObject<HpUI>();
	start_ui = CreateObject<StartUI>();
	start_ui->SetIUIEvent(this);
	finish_ui = CreateObject<FinishUI>();
	finish_ui->SetIUIEvent(this);

	game_state_ui->SetScore(game_state->GetScore());
	game_state_ui->SetRespawn(game_state->GetRespawnRemain());
	return true;
}


bool InGameScene::CreateStage() {
	field = CreateObject<Field>();
	if (field == nullptr) {
		return false;
	}

	assert(field->InitializeField(inherit_info.stage_id));
	return true;
}

bool InGameScene::CreateStageObject() {
	//fieldオブジェクトが必須のため。
	if (field == nullptr || hp_ui == nullptr) {
		return false;
	}

	std::vector<CreateObjectInfo> create_object_info_list = field->GetCreateObjectInfo();
	for (auto& create_object_info : create_object_info_list) {

		StageObject* created_object = nullptr;
		switch (create_object_info.object_type) {

		case kPLAYER_START:
			if (player != nullptr) {
				continue;
			};

			player = CreateObject<Player>(create_object_info.initiali_position);
			player->SetICharacterEvent(this);
			player->SetIPlayerEvent(this);
			player->SetHpUi(*hp_ui);

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
		case kGOAL:
		{
			//TODO::後で位置を修正
			Goal* goal = CreateObject<Goal>(create_object_info.initiali_position - Vector2D(12, 32));
			goal->SetIGoalEvent(this);
			created_object = goal;
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
	return true;
}

void InGameScene::RemoveStageObject(std::vector<StageObject*> stage_object_list) {

	for (int i = 0; i < delete_objects_list.size(); i++) {
		for (int j = 0; j < stage_object_list.size(); j++) {
			if (delete_objects_list[i] == stage_object_list[j]) {

				field->DeleteStageObject(stage_object_list[j]);
				stage_object_list.erase(std::remove(stage_object_list.begin(), stage_object_list.end(), stage_object_list[j]), stage_object_list.end());
			}
		}
	}
}

void InGameScene::CheckCollisionHit(std::vector<StageObject*> stage_obj_list) {

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
}

SceneType InGameScene::CheckExistNextStage() {
	//ゲーム状態を保存
	inherit_info.score = game_state->GetScore();
	inherit_info.respawn_remain = game_state->GetRespawnRemain();
	inherit_info.stage_name = game_state->GetStageName();

	//次ステージの確認とセット
	int stage_id = static_cast<int>(inherit_info.stage_id);
	stage_id++;
	EStageID stage_id_enum = static_cast<EStageID>(stage_id);
	inherit_info.stage_id = stage_id_enum;

	if (stage_id_enum == EStageID::kNONE_STAGE || !game_state->GetbIsClear()) {
		//仮。本当はリザルトレベルに遷移したい
		return SceneType::BOOT_SCENE;
	}
	return SceneType::NEXT_STAGE;
}