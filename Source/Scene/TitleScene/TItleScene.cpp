#include "TitleScene.h"
#include "DxLib.h"

#include "../Source/System/SoundManager.h"
namespace {
	const SceneType NEXT_SCENE = SceneType::IN_GAME_SCENE;
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize() {
	SoundManager::CreateInstance();
	SoundManager* sound_manager = SoundManager::GetInstance();

	title_graphic = LoadGraph("Resources/Images/pipo-bg001.jpg");
	decide_sound = LoadSoundMem("Resources/sound/decide03.mp3");
	decide_sound = sound_manager->LoadSoundResource("Resources/sound/decide03.mp3");
}

SceneType TitleScene::Update(float delta_seconds) {
	SoundManager* sound_manager = SoundManager::GetInstance();

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		PlaySoundMem(decide_sound, DX_PLAYTYPE_NORMAL);
		return NEXT_SCENE;
	}

	return GetSceneType();
}

void TitleScene::Draw() {
	DrawGraph(0, 0, title_graphic, true);
}

void TitleScene::Finalize() {
	DeleteGraph(title_graphic);
	title_graphic = 0;
}

void TitleScene::DestroyBookDeleteObject()
{
}
