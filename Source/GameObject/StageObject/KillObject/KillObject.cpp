#include "KillObject.h"
#include "../Source/System/SoundManager.h"
#include "../Interface/IStageObjectInterface.h"
#include "Interface/IKillEvent.h"

KillObject::KillObject()
{
}

KillObject::~KillObject()
{
}

void KillObject::Initialize() {
	game_object_state = EGameObjectState::kPLAYING;
	body_collision.box_extent = Vector2D(16.f, 16.f);
	body_collision.object_type = kKILL_TYPE;
	body_collision.hit_object_types = kPLAYER_TYPE | kENEMY_TYPE;
	
}

void KillObject::Finalize()
{
}

void KillObject::Update(float delta_seconds)
{
}

void KillObject::Draw(const Vector2D& screen_offset)
{
}

void KillObject::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	kill_event->KillEvent(hit_object);
}
