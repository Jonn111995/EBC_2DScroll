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

/// <summary>
/// �Q�[�����ɕ\�������I�u�W�F�N�g�̊��N���X
/// </summary>
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

	/// <summary>
	/// �`�揇�̎擾
	/// </summary>
	/// <returns>�`�揇</returns>
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/// <summary>
	/// �`�揇�̃Z�b�g
	/// </summary>
	/// <param name="new_priority">�Z�b�g����`�揇</param>
	void SetDrawSortPriority(const int new_priority);

	/// <summary>
	/// ������Ԃ�Play�ɕύX
	/// </summary>
	void SetPlaying() { game_object_state = EGameObjectState::kPLAYING; }
	/// <summary>
	/// ������Ԃ��|�[�Y�ɕύX
	/// </summary>
	void SetPause() { game_object_state = EGameObjectState::kPAUSE; }
	/// <summary>
	/// ������Ԃ��I����ԂɕύX
	/// </summary>
	void SetEnd() { game_object_state = EGameObjectState::kEND; }

	/// <summary>
	/// �I�u�W�F�N�g
	/// </summary>
	/// <returns></returns>
	EGameObjectState GetGameObjectState() { return game_object_state; }

	/// <summary>
	/// ������ԂɕύX
	/// </summary>
	void OnActive() { active_state = EActivation::kACTIVE; }
	/// <summary>
	/// �x�~��ԂɕύX
	/// </summary>
	void OffActive() { active_state = EActivation::kNONE_ACTIVE; }

protected:
	/// <summary>
	/// �`�揇�B���l��������������`����s��
	/// </summary>
	int draw_sort_priority;

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�̏����X�e�[�g
	/// </summary>
	EGameObjectState game_object_state;

	/// <summary>
	/// ���̃I�u�W�F�N�g�����������ǂ�����\���X�e�[�g
	/// </summary>
	EActivation active_state;
};