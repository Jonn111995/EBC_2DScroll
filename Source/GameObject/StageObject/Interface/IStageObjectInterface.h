#pragma once
class StageObject;

class IStageObjectInterface {
public:
	virtual void GetDrawInformPositon(Vector2D& draw_postion) = 0;
};