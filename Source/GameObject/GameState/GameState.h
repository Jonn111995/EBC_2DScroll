#pragma once
#include <string>
#include "../GameObject.h"

class IGameStateEvent;

/// <summary>
/// ゲーム全体の状態を管理
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
	/// <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;

public:
	/// <summary>
	/// スコアをセット
	/// </summary>
	/// <param name="now_score">現在のスコア</param>
	void SetScore(const int now_score);
	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns>現在スコア</returns>
	int GetScore() const;
	void IncreaseScore();
	/// <summary>
	/// リスポーン残り回数をセット
	/// </summary>
	/// <param name="respawn_remain">残りリスポーン回数</param>
	void SetRespawnRemain(const int respawn_remain);
	/// <summary>
	/// 残りリスポーン回数を取得
	/// </summary>
	/// <returns>残りリスポーン回数</returns>
	int GetRespawnRemain();
	void IncreseRespawnRemain();
	void ReduceRespawnRemain();
	/// <summary>
	/// 残り時間を取得
	/// </summary>
	/// <returns>残り時間</returns>
	int GetRemainTime() const;
	/// <summary>
	/// 現在のステージ名を取得
	/// </summary>
	/// <param name="new_stage_name">新しいステージ名</param>
	void SetStageName(const std::string new_stage_name);
	/// <summary>
	/// ステージ名を取得
	/// </summary>
	/// <returns>ステージ名</returns>
	std::string GetStageName() const;
	/// <summary>
	/// クリアしたかどうか？をセット
	/// </summary>
	/// <param name="is_clear">クリアしたかどうか</param>
	void SetbIsClear(const bool is_clear) ;
	/// <summary>
	/// クリアしたかどうかを取得
	/// </summary>
	/// <returns>クリアしたかどうか</returns>
	bool GetbIsClear() const;

	void SetIGameStateEvent(IGameStateEvent* game_state_event_interface) { game_state_event = game_state_event_interface; }

private:
	/// <summary>
	/// ゲームステートのイベントインターフェース
	/// </summary>
	IGameStateEvent* game_state_event;

	/// <summary>
	/// 残機UPの効果音
	/// </summary>
	int up_respawnremain__sound;

	/// <summary>
	/// スコア
	/// </summary>
	int score;

	/// <summary>
	/// リスポーン回数
	/// </summary>
	int respawn_remain;

	/// <summary>
	/// 開始時間
	/// </summary>
	float start_time;

	/// <summary>
	/// 毎フレーム合計時間
	/// </summary>
	float count_time;

	/// <summary>
	/// 残り時間
	/// </summary>
	int remain_time;

	/// <summary>
	/// ステージ名
	/// </summary>
	std::string stage_name;

	/// <summary>
	/// クリアしたかどうか？
	/// </summary>
	bool is_clear;

	/// <summary>
	/// 残機UPを通知中か?
	/// </summary>
	bool is_inform_respawn_remain_up;

	//TODO:: ResapwnManagerと同じ変数なので、後でUtility化出来ないか検討
	/// <summary>
	/// 通知カウント時間
	/// </summary>
	float inform_count_time;
	float inform_movement;
	float initial_velocity = -30;
	float plus = 1.f;
};