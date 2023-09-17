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

	//bootの文字を格納する変数。
	std::string boot_array_[4] = { "Boot   ","Boot.  ","Boot.. ","Boot..." };

	//boot_array_から一つ選ばれた文字を代入する変数
	std::string use_boot_;

	//配列の要素番号を指定する変数
	float boot_array_num_;

	float boot_count_time;
};