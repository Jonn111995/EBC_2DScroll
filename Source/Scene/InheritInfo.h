#pragma once
#include "EStageID.h"

/// <summary>
/// 次のレベルに引き継ぐデータを保持
/// </summary>
struct InheritInfo {

public:
	/// <summary>
	/// スコア
	/// </summary>
	int score = 0;

	/// <summary>
	/// リスポーン回数
	/// </summary>
	int respawn_remain = 0;

	/// <summary>
	/// ステージ名
	/// </summary>
	std::string stage_name = "";

	/// <summary>
	/// ステージID
	/// </summary>
	EStageID stage_id = EStageID::kNONE;
};