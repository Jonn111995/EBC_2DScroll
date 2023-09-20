#pragma once
#include "../SceneBase.h"

/// <summary>
/// �^�C�g�����
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
	/// �^�C�g����ʂ̔w�i
	/// </summary>
	int title_graphic;

	/// <summary>
	/// ����{�^���̌��ʉ�
	/// </summary>
	int decide_sound;

	/// <summary>
	/// �^�C�g����ʂ�BGM
	/// </summary>
	int title_bgm;

	/// <summary>
	/// �^�C�g�������̃t�H���g�n���h��
	/// </summary>
	int title_font;
};