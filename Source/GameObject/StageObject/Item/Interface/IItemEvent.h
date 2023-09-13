#pragma once

class StageObject;

class IItemEvent {
public:
	virtual void ScoreUp() = 0;
	virtual void ChangeInvincible() = 0;
	virtual void DestroyItem(StageObject& delete_object) = 0;
};