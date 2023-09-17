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

SceneManager::~SceneManager()
{
	Finalize();
}

void SceneManager::Initialize()
{
	// �J�n�V�[����SAMPLE_SCENE�ɐݒ�
	ChangeScene(SceneType::BOOT_SCENE);
}

void SceneManager::Update(float DeltaSeconds)
{
	// �V�[���̍X�V
	SceneType result_scene_type = current_scene->Update(DeltaSeconds);
	current_scene->DestroyBookDeleteObject();

	// ���݂�Update����󂯎�����V�[�����ʂ̏ꍇ�A�V�[���̑J�ڂ��s��
	if (result_scene_type != current_scene->GetSceneType())
	{
		ChangeScene(result_scene_type);
	}

	// �`��
	Draw();
}

void SceneManager::Finalize()
{
	// CurrentScene�̉��
	if (current_scene != nullptr)
	{
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

void SceneManager::ChangeScene(SceneType new_scene_type)
{
	// �V�[���̐���
	SceneBase* new_scene = CreateScene(new_scene_type);
	assert(new_scene != nullptr);

	// ���݂̃V�[���̉��
	// �ŏ��̃V�[���������̂�CurrentScene��nullptr
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
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

	case SceneType::IN_GAME_SCENE:	
		return new InGameScene();
	default:					
		return nullptr;
	}
}