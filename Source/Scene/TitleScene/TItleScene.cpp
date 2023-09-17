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
	decide_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/decide03.mp3");
	title_bgm = sound_manager->LoadSoundResource("Resources/Sounds/BGM/Pops_05.mp3");
	sound_manager->PlayLoadSound(title_bgm, true);
}

SceneType TitleScene::Update(float delta_seconds) {
	SoundManager* sound_manager = SoundManager::GetInstance();

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		sound_manager->PlayLoadSound(decide_sound);
		return NEXT_SCENE;
	}

	return GetSceneType();
}

void TitleScene::Draw() {
	DrawGraph(0, 0, title_graphic, true);
}

void TitleScene::Finalize() {
	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->StopSound(title_bgm);
	sound_manager->UnLoadSoundResource(title_bgm);

	DeleteGraph(title_graphic);
	title_graphic = 0;
	title_bgm = 0;
}

void TitleScene::DestroyBookDeleteObject()
{
}
