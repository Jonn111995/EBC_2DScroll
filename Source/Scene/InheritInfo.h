#pragma once
#include "EStageID.h"

/// <summary>
/// ���̃��x���Ɉ����p���f�[�^��ێ�
/// </summary>
struct InheritInfo {

public:
	/// <summary>
	/// �X�R�A
	/// </summary>
	int score = 0;

	/// <summary>
	/// ���X�|�[����
	/// </summary>
	int respawn_remain = 0;

	/// <summary>
	/// �X�e�[�W��
	/// </summary>
	std::string stage_name = "";

	/// <summary>
	/// �X�e�[�WID
	/// </summary>
	EStageID stage_id = EStageID::kNONE;
};