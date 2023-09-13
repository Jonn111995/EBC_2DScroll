#pragma once

class IGameStateEvent {
public:
	virtual void UpdateTimeUI(int remain_time) = 0;
	virtual void UpdateRespawnRemainUI(const int respawn_remain) = 0;
	virtual void UpdateScoreUI(const int new_score) = 0;
	virtual void TimeOver() = 0;
	virtual void GetDrawInformPositon(Vector2D& draw_postion) = 0;
};
