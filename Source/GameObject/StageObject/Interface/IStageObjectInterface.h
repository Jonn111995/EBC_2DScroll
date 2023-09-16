#pragma once
class StageObject;

class IStageObjectInterface {
public:
	virtual void DeadEvent(StageObject* dead_object) = 0;
};