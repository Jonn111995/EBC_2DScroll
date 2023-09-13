#pragma once

class IPlayerEvent {
public:
	virtual bool ExecuteRespawn() = 0;
};