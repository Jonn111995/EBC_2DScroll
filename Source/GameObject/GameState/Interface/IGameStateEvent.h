#pragma once

class IGameStateEvent {
public:
	virtual void UpdateTimeUI(int remain_time) = 0;
	virtual void UpdateRespawnRemain(const int respawn_remain) = 0;
	virtual void TimeOver() = 0;
};
