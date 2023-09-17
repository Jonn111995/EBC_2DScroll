#pragma once
#include "../SceneBase.h"


class TitleScene : public SceneBase {
public:
	TitleScene();
	virtual ~TitleScene();
public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="delta_seconds">���t���[������</param>
	/// <returns>���ɑJ�ڂ���V�[���^�C�v</returns>
	virtual SceneType Update(float delta_seconds);

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �V�[���^�C�v�̎擾
	/// </summary>
	/// <returns>�V�[���^�C�v</returns>
	virtual SceneType GetSceneType() const override { return SceneType::TITLE_SCENE; };

	/// <summary>
	/// �폜�\��̃I�u�W�F�N�g��\��
	/// </summary>
	/// <param name="delete_object">�폜�ΏۃI�u�W�F�N�g</param>
	virtual void BookDeleteObject(GameObject* delete_object) { delete_objects_list.push_back(delete_object); }

	/// <summary>
	/// �폜�\��̃I�u�W�F�N�g���폜
	/// </summary>
	virtual void DestroyBookDeleteObject();
private:
	int title_graphic;
};