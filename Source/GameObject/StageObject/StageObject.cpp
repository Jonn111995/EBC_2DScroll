#include "StageObject.h"

StageObject::StageObject()
	: position(Vector2D())
{
}

StageObject::~StageObject()
{
}

void StageObject::SetPosition(const Vector2D& new_position)
{
	position = new_position;
}
