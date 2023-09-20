#pragma once
#include "../SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>
class TitleScene : public SceneBase {
public:
	TitleScene();
	virtual ~TitleScene();
public:
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual SceneType Update(const float delta_time) override;
	/// <inheritdoc />
	virtual void Draw() override;
	/// <inheritdoc />
	virtual void Finalize() override;
	/// <inheritdoc />
	virtual SceneType GetSceneType() const override { return SceneType::TITLE_SCENE; };

private:
	/// <summary>
	/// タイトル画面の背景
	/// </summary>
	int title_graphic;

	/// <summary>
	/// 決定ボタンの効果音
	/// </summary>
	int decide_sound;

	/// <summary>
	/// タイトル画面のBGM
	/// </summary>
	int title_bgm;

	/// <summary>
	/// タイトル文字のフォントハンドル
	/// </summary>
	int title_font;
};