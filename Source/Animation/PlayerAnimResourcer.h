#pragma once
#include <vector>
#include"../Source/GameObject/StageObject/Character/Player/EPlayerState.h"

/// <summary>
/// �v���C���[�̃A�j���[�V�����n���h�����Ǘ�����
/// </summary>
class PlayerAnimResourcer {

private:
	/// <summary>
	/// �ҋ@�A�j���[�V�����n���h��
	/// </summary>
	int loaded_sprite_wait[4];
	/// <summary>
	/// �ړ��A�j���[�V�����n���h��
	/// </summary>
	int loaded_sprite_run[8];
	/// <summary>
	/// �W�����v�A�j���[�V�����n���h��
	/// </summary>
	int loaded_sprite_jump[6];
	/// <summary>
	/// �U���A�j���[�V�����n���h��
	/// </summary>
	int loaded_sprite_attack[3];

	int loaded_sprite_damage;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�e�[�g�ɍ��킹���O���t�B�b�N�n���h�����擾
	/// </summary>
	/// <param name="now_state">�v���C���[�̃X�e�[�g</param>
	/// <returns>�O���t�B�b�N�n���h��</returns>
	std::vector<int> GetAnimaitonHandle(EPlayerState now_state);
private:
	/// <summary>
	/// �O���t�B�b�N�n���h����Ԃ�
	/// </summary>
	/// <param name="now_state">���݂̃X�e�[�g</param>
	/// <param name="out_array_size">�n���h���z��̃T�C�Y</param>
	/// <returns>�O���t�B�b�N�n���h��</returns>
	int* GetAnimationHandleHelper(EPlayerState now_state, int& out_array_size);

};

