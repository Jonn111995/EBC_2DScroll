#include "Hand.h"
#include "DxLib.h"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::Initialize() {
	__super::Initialize();
}

void Hand::Finalize()
{
}

void Hand::Update(float delta_seconds)
{
}

void Hand::Draw(const Vector2D& screen_offset)
{
	//デバック用
	unsigned int color = GetColor(255, 0, 0);
	int x2 = body_collision.center_position2.x - body_collision.box_extent.x;
	int y2 = body_collision.center_position2.y - body_collision.box_extent.y;
	DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);
}

void Hand::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {

}

void Hand::SetAttackRange(const BoxCollisionParams& owner_collision) {
	__super::SetAttackRange(owner_collision);
}
