#include "SampleScene.h"
#include "../Source/System/ScreenInfo.h"
#include "../../GameObject/SampleObject/SampleObject.h"
#include "../Source/GameObject/StageObject/Character/Player/Player.h"
#include "../Source/GameObject/Field/Field.h"

SampleScene::SampleScene()
{
}

bool SampleScene::CheckCanMove(const Vector2D& move_to_position, const BoxCollisionParams& collision) {
	return field->CheckMove(move_to_position,collision);
}

bool SampleScene::CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) {
	return field->CheckStande(move_to_position, collision);
}

void SampleScene::Initialize()
{
	// 親クラスのInitialize()
	__super::Initialize();

	ScreenInfo::CreateInstance();
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	// SampleObjectを生成

	field = CreateObject<Field>();
	field->InitializeField("C/Users/n5919/EBC_2DScroll/Source/CSVFile/mapdata.csv");
	Character* chara = CreateObject<Player>(Vector2D(screen_info->GetCenterX(), screen_info->GetCenterY()));
	chara->SetICharacterEvent(this);
}

SceneType SampleScene::Update(float delta_seconds)
{
	// 親クラスのUpdate()
	return __super::Update(delta_seconds);
}

void SampleScene::Draw()
{
	// 親クラスのDraw()
	__super::Draw();
}

void SampleScene::Finalize()
{
	// 親クラスのFinalize()
	__super::Finalize();
}