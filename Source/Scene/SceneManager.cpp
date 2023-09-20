#include "SceneManager.h"

#include <cassert>
#include "DxLib.h"

#include "SceneBase.h"
#include "BootScene/BootScene.h"
#include "TitleScene/TitleScene.h"
#include "InGameScene/InGameScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
{
}

SceneManager::~SceneManager() {
}

void SceneManager::Initialize() {
	//最初は必ずBoot画面から始まる
	ChangeScene(SceneType::BOOT_SCENE);
}

void SceneManager::Update(const float delta_time) {

	SceneType result_scene_type = current_scene->Update(delta_time);
	current_scene->DestroyBookDeleteObject();

	// 現在とUpdateから受け取ったシーンが別の場合、シーンの遷移を行う
	if (result_scene_type != current_scene->GetSceneType()) {
		ChangeScene(result_scene_type);
	}

	Draw();
}

void SceneManager::Finalize() {

	// CurrentSceneの解放
	if (current_scene != nullptr) {
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Draw()
{
	// 裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面をクリア
	ClearDrawScreen();

	// シーンの描画
	current_scene->Draw();

	// 画面を更新
	ScreenFlip();
}

void SceneManager::ChangeScene(SceneType new_scene_type) {
	// シーンの生成
	SceneBase* new_scene = CreateScene(new_scene_type);
	assert(new_scene != nullptr);

	// 現在のシーンの解放
	// 最初のシーン生成時のみCurrentSceneがnullptr
	if (current_scene != nullptr) {

		current_scene->Finalize();
		InheritPreSceneData(*current_scene, *new_scene);
		delete current_scene;
	}

	// 新しいシーンの開始
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(SceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case SceneType::BOOT_SCENE:
		return new BootScene();

	case SceneType::TITLE_SCENE:
		return new TitleScene();

	case SceneType::NEXT_STAGE:
	//次のステージ==IN_GAME_SCENEのためフォースルー
	case SceneType::IN_GAME_SCENE:	
		return new InGameScene();
	default:					
		return nullptr;
	}
}

void SceneManager::InheritPreSceneData(const SceneBase& pre_scene, SceneBase& new_scene) {

	InheritInfo pre_game_data = pre_scene.GetInheritInfo();
	new_scene.SetInheritInfo(pre_game_data);
}
