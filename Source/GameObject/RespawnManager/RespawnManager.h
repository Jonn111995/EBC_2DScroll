#pragma once
#include <vector>
#include "../GameObject.h"
#include "../StageObject/Interface/IStageObjectInterface.h"
#include "../Source/Utility/Vector2D.h"

class Character;
IStageObjectInterface;

/// <summary>
/// ���X�|�[���}�l�[�W���̃X�e�[�g
/// </summary>
enum class ERespawnManagerState {
	kOBSERVE,			//�`�F�b�N�|�C���g�Ď���
	kINFORM_PASS_POINT	//�ʉߒʒm��
};

/// <summary>
/// ���X�|�[���������Ǘ�
/// </summary>
class RespawnManager : public GameObject{
public:
	RespawnManager();
	virtual ~RespawnManager();

public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="delta_seconds">�O�t���[���Ƃ̍�������(s)</param>
	virtual void Update(float delta_seconds);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset);

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize();
public:
	/// <summary>
	/// �`�F�b�N�|�C���g���X�g���Z�b�g
	/// </summary>
	/// <param name="check_point_list">�`�F�b�N�|�C���g���X�g</param>
	void SetCheckPointList(std::vector<Vector2D> check_point_list);

	/// <summary>
	/// �`�F�b�N�|�C���g��ʉ߂������ǂ������Ď�����I�u�W�F�N�g���Z�b�g
	/// </summary>
	/// <param name="observe_object">�Ď��Ώۂ̃I�u�W�F�N�g</param>
	void SetObserveObject(Character& observe_object) { this->observe_object = &observe_object; }

	/// <summary>
	/// �L�����N�^�[�̃��X�|�[�������s
	/// </summary>
	void RespawnObject();

	void SetIStageObjectEvent(IStageObjectInterface* stage_object_event) { this->stage_object_event = stage_object_event; }
private:

	ERespawnManagerState now_state;
	/// <summary>
	/// �ǐՂ���I�u�W�F�N�g
	/// </summary>
	Character* observe_object;

	IStageObjectInterface* stage_object_event;

	/// <summary>
	/// ���݂̃`�F�b�N�|�C���g
	/// </summary>
	Vector2D now_check_point;

	/// <summary>
	/// ���̃`�F�b�N�|�C���g
	/// </summary>
	Vector2D next_check_point;

	/// <summary>
	/// �`�F�b�N�|�C���g�̏ꏊ�ꗗ
	/// </summary>
	std::vector<Vector2D> check_point_list;

	/// <summary>
	/// �`�F�b�N�|�C���g�ʉߎ��̌��ʉ�
	/// </summary>
	int inform_pass_check_point_sound;

	/// <summary>
	/// �`�F�b�N�|�C���g��ʉ߂������H
	/// </summary>
	bool is_pass_check_point;

	/// <summary>
	/// �Ō�̃`�F�b�N�|�C���g��ʉ߂������H
	/// </summary>
	bool is_pass_last;

	/// <summary>
	/// �ʒm�J�E���g����
	/// </summary>
	float inform_count_time;

	float inform_movement;
	float initial_velocity = -30;
	float plus = 1.f;

};
