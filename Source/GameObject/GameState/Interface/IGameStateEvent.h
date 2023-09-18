#pragma once
#include "../Source/GameObject/StageObject/Interface/IStageObjectInterface.h"
class IGameStateEvent : public IStageObjectInterface{
public:
	virtual void UpdateTimeUI(int remain_time) = 0;
	virtual void UpdateRespawnRemainUI(const int respawn_remain) = 0;
	virtual void UpdateScoreUI(const int new_score) = 0;
	virtual void TimeOver() = 0;
};
