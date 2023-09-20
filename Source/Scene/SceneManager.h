#pragma once

// �V�[���^�C�v�̑O���錾
enum class SceneType : unsigned short;

/// <summary>
/// �e�V�[�����Ǘ�����N���X
/// �V�[���̐��� / �j����ύX���s�� 
/// </summary>
class SceneManager {
public:
	SceneManager();
	virtual ~SceneManager();

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// Scene��Update���Ă�
	/// </summary>
	/// <param name="delta_time">�O�t���[���Ƃ̍�������(s)</param>
	void Update(const float delta_time);

	/// <summary>
	/// ���
	/// </summary>
	void Finalize();

private:
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���̑J��
	/// </summary>
	/// <param name="new_scene_type">�J�ڂ������V�[��</param>
	void ChangeScene(SceneType new_scene_type);

	/// <summary>
	/// �V�[���̐���
	/// </summary>
	/// <param name="new_scene_type">��������V�����V�[��</param>
	/// <returns>���������V�[��</returns>
	class SceneBase* CreateScene(SceneType new_scene_type);

	/// <summary>
	/// �O��̃X�e�[�W�ł̃f�[�^�����̃X�e�[�W�Ɉ����p��
	/// �X�R�A�A�c�@���A�X�e�[�W���A���̃X�e�[�WID�������p��
	/// </summary>
	/// <param name="pre_scene">�O��̃V�[��</param>
	/// <param name="new_scene">���̃V�[��</param>
	void InheritPreSceneData(const SceneBase& pre_scene, SceneBase& new_scene);

private:
	/// <summary>
	/// ���݂̃V�[��
	/// </summary>
	class SceneBase* current_scene;
};