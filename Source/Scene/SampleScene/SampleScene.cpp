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

	field = CreateObject<Field>();
	field->InitializeField("C/Users/n5919/EBC_2DScroll/Source/CSVFile/mapdata.csv");
	player = CreateObject<Player>();
	player->SetICharacterEvent(this);
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
}

void SampleScene::Finalize() {
	// 親クラスのFinalize()
	__super::Finalize();
}

SceneType SampleScene::Update(float delta_seconds) {

	// 親クラスのUpdate()
	SceneType now_scen_type = __super::Update(delta_seconds);

	std::vector<StageObject*> stage_obj_list = field->GetStageObjectList();

	for (auto iterator = stage_obj_list.begin(); iterator != stage_obj_list.end(); ++iterator) {
		for (auto oppnent_iterator = stage_obj_list.begin(); oppnent_iterator != stage_obj_list.end(); ++oppnent_iterator) {

			if (iterator == oppnent_iterator) {
				continue;
			}

			BoxCollisionParams opponent = (*oppnent_iterator)->GetBodyCollision();
			if (CheckBoxCollision(*iterator, (*iterator)->GetBodyCollision(), opponent)) {
				(*iterator)->OnHitBoxCollision(*oppnent_iterator,opponent);
			}
		}
	}
	return now_scen_type;
}

void SampleScene::Draw()
{
	// 親クラスのDraw()
	__super::Draw();
}

