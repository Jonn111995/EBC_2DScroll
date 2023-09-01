#include "StageObject.h"

StageObject::StageObject()
	: position(Vector2D())
{
}

StageObject::~StageObject()
{
}

void StageObject::Initialize() {
	__super::Initialize();
}

void StageObject::Finalize() {
	__super::Finalize();
}

void StageObject::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void StageObject::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}

void StageObject::SetPosition(const Vector2D& new_position) {
	position = new_position;
}

void StageObject::OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) {

}
