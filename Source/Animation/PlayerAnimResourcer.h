#pragma once
#include <vector>
#include"../Source/GameObject/StageObject/Character/Player/EPlayerState.h"

/// <summary>
/// プレイヤーのアニメーションハンドルを管理する
/// </summary>
class PlayerAnimResourcer {

private:
	/// <summary>
	/// 待機アニメーションハンドル
	/// </summary>
	int loaded_sprite_wait[4];
	/// <summary>
	/// 移動アニメーションハンドル
	/// </summary>
	int loaded_sprite_run[8];
	/// <summary>
	/// ジャンプアニメーションハンドル
	/// </summary>
	int loaded_sprite_jump[6];
	/// <summary>
	/// 攻撃アニメーションハンドル
	/// </summary>
	int loaded_sprite_attack[3];

	int loaded_sprite_damage;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 解放処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// ステートに合わせたグラフィックハンドルを取得
	/// </summary>
	/// <param name="now_state">プレイヤーのステート</param>
	/// <returns>グラフィックハンドル</returns>
	std::vector<int> GetAnimaitonHandle(EPlayerState now_state);
private:
	/// <summary>
	/// グラフィックハンドルを返す
	/// </summary>
	/// <param name="now_state">現在のステート</param>
	/// <param name="out_array_size">ハンドル配列のサイズ</param>
	/// <returns>グラフィックハンドル</returns>
	int* GetAnimationHandleHelper(EPlayerState now_state, int& out_array_size);

};

