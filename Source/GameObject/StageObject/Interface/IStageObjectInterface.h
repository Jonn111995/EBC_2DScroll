#pragma once
class StageObject;

class IStageObjectInterface {
public:
	virtual void DeadEvent(const StageObject* dead_object) = 0;
};