#pragma once

class StageObject;

class IKillEvent {
public:
	virtual void KillEvent(const StageObject* kill_target) = 0;
};