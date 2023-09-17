#pragma once
#include <string>
#include "../SceneBase.h"

/// <summary>
/// BootSceneのステート
/// </summary>
enum class EBootSceneState {
	kPLAYING,
	kEND,
};

/// <summary>
/// 起動画面
/// 現在は、ただの演出用途
/// </summary>
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
public:
	/// <summary>
	/// Boot文字のアニメーションを更新
	/// </summary>
	/// <param name="delta_time"></param>
	void UpdateBootAnimation(const float delta_time);
private:

	/// <summary>
	/// Bootステート
	/// </summary>
	EBootSceneState boot_scene_state;

	/// <summary>
	/// bootの文字を格納する
	/// </summary>
	std::string boot_array[4];

	/// <summary>
	/// boot_array_から一つ選ばれた文字を代入する
	/// </summary>
	std::string use_boot;

	/// <summary>
	/// 配列の要素番号を指定するインデクス番号
	/// </summary>
	float boot_array_num;

	/// <summary>
	/// カウント時間
	/// </summary>
	float boot_count_time;
};