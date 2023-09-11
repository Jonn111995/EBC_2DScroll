#pragma once

class Vector2D;

enum class EGameObjectState : unsigned short {
	kPRE_START,	//�����t�F�[�Y
	kPLAYING,	//�����t�F�[�Y
	kPAUSE,		//�|�[�Y�t�F�[�Y
	kEND,		//�I���t�F�[�Y
};

enum class EActivation : unsigned short {
	kACTIVE,
	kNONE_ACTIVE
};

/**
 * �Q�[�����ɕ\�������I�u�W�F�N�g�̊��N���X
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="delta_seconds">�O�t���[���Ƃ̍�������(s)</param>
	virtual void Update(float delta_seconds) {}

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset) {}

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize() {}

	/**
	 * �V�[���̎擾
	 * @return owner_scene
	 */
	//class SceneBase* GetOwnerScene() const { return owner_scene; }

	/**
	 * �V�[���̃Z�b�g
	 * @param	new_owner_scene	�Z�b�g����Position
	 */
	//void SetOwnerScene(class SceneBase* new_owner_scene);

	/**
	 * �`�揇�̎擾
	 * @return	draw_sort_priority
	 */
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/**
	 * �`�揇�̃Z�b�g
	 * @param	new_priority	�Z�b�g����`�揇
	 */
	void SetDrawSortPriority(const int new_priority);

	void SetPlaying() { game_object_state = EGameObjectState::kPLAYING; }
	void SetPause() { game_object_state = EGameObjectState::kPAUSE; }
	EGameObjectState GetGameObjectState() { return game_object_state; }

	void OnActive() { active_state = EActivation::kACTIVE; }
	void OffActive() { active_state = EActivation::kNONE_ACTIVE; }

protected:
	// �I�[�i�[�ƂȂ�V�[��
	//class SceneBase* owner_scene;

	// �`�揇�B���l��������������`����s��
	int draw_sort_priority;
	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�̏����X�e�[�g
	/// </summary>
	EGameObjectState game_object_state;

	EActivation active_state;
};