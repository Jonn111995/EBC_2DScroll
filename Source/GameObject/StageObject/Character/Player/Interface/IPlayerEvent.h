#pragma once

class IPlayerEvent {
public:
	virtual bool ExecuteRespawn() = 0;
	virtual void FinishInvincibleState() = 0;
};