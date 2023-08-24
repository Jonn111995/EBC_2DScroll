#include "SampleScene.h"
#include "../Source/System/ScreenInfo.h"
#include "../../GameObject/SampleObject/SampleObject.h"
#include "../Source/GameObject/StageObject/Character/Player/Player.h"
#include "../Source/GameObject/Field/Field.h"

SampleScene::SampleScene()
{
}

void SampleScene::Initialize()
{
	// �e�N���X��Initialize()
	__super::Initialize();

	ScreenInfo::CreateInstance();
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	// SampleObject�𐶐�

	field = CreateObject<Field>();
	field->InitializeField("C/Users/n5919/EBC_2DScroll/Source/CSVFile/mapdata.csv");
	CreateObject<Player>(Vector2D(screen_info->GetCenterX(), screen_info->GetCenterY()));
}

SceneType SampleScene::Update(float delta_seconds)
{
	// �e�N���X��Update()
	return __super::Update(delta_seconds);
}

void SampleScene::Draw()
{
	// �e�N���X��Draw()
	__super::Draw();
}

void SampleScene::Finalize()
{
	// �e�N���X��Finalize()
	__super::Finalize();
}