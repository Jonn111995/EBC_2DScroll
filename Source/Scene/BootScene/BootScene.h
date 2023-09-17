#pragma once
#include <string>
#include "../SceneBase.h"

namespace {
	const SceneType NEXT_SCENE = SceneType::TITLE_SCENE;
}

enum class EBootSceneState {

	kPLAYING,
	kEND,
};

class BootScene : public SceneBase {
public:
	BootScene();
	virtual ~BootScene();
public:
	/// <inheritdoc />
	virtual void Initialize();

	/// <inheritdoc />
	virtual SceneType Update(float delta_seconds);

	/// <inheritdoc />
	virtual void Draw();

	/// <inheritdoc />
	virtual void Finalize();

	/// <inheritdoc />
	virtual SceneType GetSceneType()const override { return SceneType::BOOT_SCENE; };

	/// <inheritdoc />
	virtual void BookDeleteObject(GameObject* delete_object) { delete_objects_list.push_back(delete_object); }

	/// <inheritdoc />
	virtual void DestroyBookDeleteObject();
private:
	EBootSceneState boot_scene_state;

	//boot�̕������i�[����ϐ��B
	std::string boot_array_[4] = { "Boot   ","Boot.  ","Boot.. ","Boot..." };

	//boot_array_�����I�΂ꂽ������������ϐ�
	std::string use_boot_;

	//�z��̗v�f�ԍ����w�肷��ϐ�
	float boot_array_num_;

	float boot_count_time;
};