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
	/**
	 * ������
	 */
	void Initialize();

	/**
	 * �X�V
	 * @param delta_seconds	�O�t���[���Ƃ̍�������(s)
	 */
	void Update(float delta_seconds);

	/**
	 * ���
	 */
	void Finalize();

private:
	/**
	 * �`��
	 */
	void Draw();

	/**
	 * �V�[���̑J��
	 * @param	new_scene_type	�J�ڂ������V�[��
	 */
	void ChangeScene(SceneType new_scene_type);

	/**
	 * �V�[���̐���
	 * @param	new_scene_type	��������V�����V�[��
	 * @return	���������V�[��
	 */
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