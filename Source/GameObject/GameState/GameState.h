#pragma once
#include <string>
#include "../GameObject.h"

class IGameStateEvent;
//enum class EGameStatePhase {
//	kPRE_START,
//	KPLAYING,
//	kEND
//};
/// <summary>
/// �Q�[���S�̂̏�Ԃ��Ǘ�
/// </summary>
class GameState : public GameObject {
public:
	GameState();
	virtual ~GameState();

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;

public:
	/*void SetGameState(const EGameStatePhase new_state) { game_state_state = new_state; }
	EGameStatePhase GetGameStatePhase() const { return game_state_state; }
	*/
	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="now_score">���݂̃X�R�A</param>
	void SetScore(const int now_score);
	/// <summary>
	/// �X�R�A���擾
	/// </summary>
	/// <returns>���݃X�R�A</returns>
	int GetScore() const;
	/// <summary>
	/// ���X�|�[���c��񐔂��Z�b�g
	/// </summary>
	/// <param name="respawn_remain">�c�胊�X�|�[����</param>
	void SetRespawnRemain(const int respawn_remain);
	/// <summary>
	/// �c�胊�X�|�[���񐔂��擾
	/// </summary>
	/// <returns>�c�胊�X�|�[����</returns>
	int GetRespawnRemain();
	/// <summary>
	/// �c�莞�Ԃ��擾
	/// </summary>
	/// <returns>�c�莞��</returns>
	int GetRemainTime() const;
	/// <summary>
	/// ���݂̃X�e�[�W�����擾
	/// </summary>
	/// <param name="new_stage_name">�V�����X�e�[�W��</param>
	void SetStageName(const std::string new_stage_name);
	/// <summary>
	/// �X�e�[�W�����擾
	/// </summary>
	/// <returns>�X�e�[�W��</returns>
	std::string GetStageName() const;
	/// <summary>
	/// �N���A�������ǂ����H���Z�b�g
	/// </summary>
	/// <param name="is_clear">�N���A�������ǂ���</param>
	void SetbIsClear(const bool is_clear) ;
	/// <summary>
	/// �N���A�������ǂ������擾
	/// </summary>
	/// <returns>�N���A�������ǂ���</returns>
	bool GetbIsClear() const;

	void SetIGameStateEvent(IGameStateEvent* game_state_event_interface) { game_state_event = game_state_event_interface; }
	//void GetBeforeState(DataSuccessor&);

private:
	/// <summary>
	/// �Q�[���X�e�[�g�̏��
	/// </summary>
	//EGameStatePhase game_state_state;

	/// <summary>
	/// �Q�[���X�e�[�g�̃C�x���g�C���^�[�t�F�[�X
	/// </summary>
	IGameStateEvent* game_state_event;
	/// <summary>
	/// �X�R�A
	/// </summary>
	int score;

	/// <summary>
	/// ���X�|�[����
	/// </summary>
	int respawn_remain;

	/// <summary>
	/// �J�n����
	/// </summary>
	float start_time;

	/// <summary>
	/// ���t���[�����v����
	/// </summary>
	float count_time;

	/// <summary>
	/// �c�莞��
	/// </summary>
	int remain_time;

	/// <summary>
	/// �X�e�[�W��
	/// </summary>
	std::string stage_name;

	/// <summary>
	/// �N���A�������ǂ����H
	/// </summary>
	bool is_clear;
};