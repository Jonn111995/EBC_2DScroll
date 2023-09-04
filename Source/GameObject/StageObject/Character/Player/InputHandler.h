#pragma once
#include "EButton.h"
#include <vector>

/// <summary>
/// ���̓`�F�b�N�@�\.
/// </summary>
class InputHandler{

private:
	/// <summary>
	/// �L�[�̉����������
	/// </summary>
	bool check_key_status[10] = { false };
	/// <summary>
	/// �L�[�̉������
	/// �e�L�[�̏��������s���邩�ۂ���\��.
	/// </summary>
	bool return_key_status[10] = { false };
	/// <summary>
	/// �L�[�̉����b��
	/// </summary>
	float  push_time[10] = { 0.0f };
public:
	/// <summary>
	/// �L�[�̎��
	/// </summary>
	EButton button_type[4] = { kLEFT_B, kRIGHT_B, kJUMP_B, kATTACK_B };

public:
	InputHandler();
	virtual ~InputHandler();

	/// <summary>
	/// �L�[�����̊m�F������
	/// </summary>
	/// <param name="delta_time">���t���[���b</param>
	/// <returns>�e�L�[�̉������</returns>
	std::vector<bool> CheckInput(float delta_time);

private:
	/// <summary>
	/// �L�[�������ꑱ���Ă��邩�ǂ������`�F�b�N
	/// </summary>
	/// <param name="key">�m�F����L�[</param>
	/// <param name="status">�L�[�̉������</param>
	/// <param name="time">���t���[���b</param>
	/// <param name="push_time">�L�[�������Ă���b��</param>
	/// <returns>true: �����ꑱ���Ă���@false: �����ꑱ���Ă��Ȃ�</returns>
	bool CheckKeyKeepingPush(int key, bool& status, float delta_time, float& push_time);
	bool CheckMouseKeepingClick(int key, bool& status, float delta_time, float& push_time);

	/// <summary>
	/// ���ړ��{�^���̃`�F�b�N
	/// </summary>
	/// <param name="time">���t���[���b</param>
	/// <returns>true:������Ă��� false:������Ă��Ȃ�</returns>
	bool CheckLeftButton(float time);
	/// <summary>
	/// �E�ړ��{�^���̃`�F�b�N
	/// </summary>
	/// <param name="time">���t���[���b</param>
	/// <returns>true:������Ă��� false:������Ă��Ȃ�</returns>
	bool CheckRightButton(float time);
	/// <summary>
	/// �W�����v�{�^���̃`�F�b�N
	/// </summary>
	/// <param name="time">���t���[���b</param>
	/// <returns>true:���������s false:���s���Ȃ� </returns>
	bool CheckJumpButton(float time);
	/// <summary>
	/// �U���{�^���̃`�F�b�N
	/// </summary>
	/// <param name="time">���t���[���b</param>
	/// <returns>true:�����ꂽ false:������Ă��Ȃ�</returns>
	bool CheckAttackButton(float time);

};

