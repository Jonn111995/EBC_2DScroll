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
	//�ŏ��͕K��Boot��ʂ���n�܂�
	ChangeScene(SceneType::BOOT_SCENE);
}

void SceneManager::Update(const float delta_time) {

	SceneType result_scene_type = current_scene->Update(delta_time);
	current_scene->DestroyBookDeleteObject();

	// ���݂�Update����󂯎�����V�[�����ʂ̏ꍇ�A�V�[���̑J�ڂ��s��
	if (result_scene_type != current_scene->GetSceneType()) {
		ChangeScene(result_scene_type);
	}

	Draw();
}

void SceneManager::Finalize() {

	// CurrentScene�̉��
	if (current_scene != nullptr) {
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Draw()
{
	// ����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ��N���A
	ClearDrawScreen();

	// �V�[���̕`��
	current_scene->Draw();

	// ��ʂ��X�V
	ScreenFlip();
}

void SceneManager::ChangeScene(SceneType new_scene_type) {
	// �V�[���̐���
	SceneBase* new_scene = CreateScene(new_scene_type);
	assert(new_scene != nullptr);

	// ���݂̃V�[���̉��
	// �ŏ��̃V�[���������̂�CurrentScene��nullptr
	if (current_scene != nullptr) {

		current_scene->Finalize();
		InheritPreSceneData(*current_scene, *new_scene);
		delete current_scene;
	}

	// �V�����V�[���̊J�n
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
	//���̃X�e�[�W==IN_GAME_SCENE�̂��߃t�H�[�X���[
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
