#pragma once
#include "EButton.h"
#include <vector>

/// <summary>
/// 入力チェック機能.
/// </summary>
class InputHandler{

private:
	/// <summary>
	/// キーの押下持続状態
	/// </summary>
	bool check_key_status[10] = { false };
	/// <summary>
	/// キーの押下状態
	/// 各キーの処理を実行するか否かを表す.
	/// </summary>
	bool return_key_status[10] = { false };
	/// <summary>
	/// キーの押下秒数
	/// </summary>
	float  push_time[10] = { 0.0f };
public:
	/// <summary>
	/// キーの種類
	/// </summary>
	EButton button_type[4] = { kLEFT_B, kRIGHT_B, kJUMP_B, kATTACK_B };

public:
	InputHandler();
	virtual ~InputHandler();

	/// <summary>
	/// キー押下の確認をする
	/// </summary>
	/// <param name="delta_time">毎フレーム秒</param>
	/// <returns>各キーの押下状態</returns>
	std::vector<bool> CheckInput(float delta_time);

private:
	/// <summary>
	/// キーが押され続けているかどうかをチェック
	/// </summary>
	/// <param name="key">確認するキー</param>
	/// <param name="status">キーの押下状態</param>
	/// <param name="time">毎フレーム秒</param>
	/// <param name="push_time">キーを押している秒数</param>
	/// <returns>true: 押され続けている　false: 押され続けていない</returns>
	bool CheckKeyKeepingPush(int key, bool& status, float delta_time, float& push_time);
	bool CheckMouseKeepingClick(int key, bool& status, float delta_time, float& push_time);

	/// <summary>
	/// 左移動ボタンのチェック
	/// </summary>
	/// <param name="time">毎フレーム秒</param>
	/// <returns>true:押されている false:押されていない</returns>
	bool CheckLeftButton(float time);
	/// <summary>
	/// 右移動ボタンのチェック
	/// </summary>
	/// <param name="time">毎フレーム秒</param>
	/// <returns>true:押されている false:押されていない</returns>
	bool CheckRightButton(float time);
	/// <summary>
	/// ジャンプボタンのチェック
	/// </summary>
	/// <param name="time">毎フレーム秒</param>
	/// <returns>true:処理を実行 false:実行しない </returns>
	bool CheckJumpButton(float time);
	/// <summary>
	/// 攻撃ボタンのチェック
	/// </summary>
	/// <param name="time">毎フレーム秒</param>
	/// <returns>true:押された false:押されていない</returns>
	bool CheckAttackButton(float time);

};

