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
	// �e�N���X��Initialize()
	__super::Initialize();

	ScreenInfo::CreateInstance();
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	// SampleObject�𐶐�

	field = CreateObject<Field>();
	field->InitializeField("C/Users/n5919/EBC_2DScroll/Source/CSVFile/mapdata.csv");
	Character* chara = CreateObject<Player>(Vector2D(screen_info->GetCenterX(), screen_info->GetCenterY()));
	chara->SetICharacterEvent(this);
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