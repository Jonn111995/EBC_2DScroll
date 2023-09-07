#pragma once
#include <string>
#include "../UIComponent.h"

class IGameStateUI;

class GameStateUI : public UIComponent {

public:
	GameStateUI();
	virtual ~GameStateUI();

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;

public:
	/// <summary>
	/// UIのスコアを更新
	/// </summary>
	/// <param name="new_score">現在スコア</param>
	void SetScore(const int new_score) { display_score = new_score; }
	/// <summary>
	/// UIの残機数を更新
	/// </summary>
	/// <param name="new_respawn_remain">残りの残機数</param>
	void SetRespawn(const int new_respawn_remain) { display_respawn_remain = new_respawn_remain; };
	/// <summary>
	/// UIの残り時間を更新
	/// </summary>
	/// <param name="remain_time">残り時間</param>
	void SetTime(const int remain_time) { display_time = remain_time; }
	/// <summary>
	/// UIのステージ名を更新
	/// </summary>
	/// <param name="new_stage_name">現在のステージ名</param>
	void SetStageName(const std::string new_stage_name) { stage_name = new_stage_name; }
		
private:
	/// <summary>
	/// UIに表示する現在スコア
	/// </summary>
	int display_score;
	/// <summary>
	/// UIに表示する残機数
	/// </summary>
	int display_respawn_remain;
	/// <summary>
	/// UIに表示する残り時間
	/// </summary>
	int display_time;
	/// <summary>
	/// UIに表示するステージ名
	/// </summary>
	std::string stage_name;
};