#include "BaseWeapon.h"
#include "../Source/GameObject/StageObject/Character/Character.h"

void BaseWeapon::Initialize() {
	body_collision.object_type = kWEAPON_TYPE;
}

void BaseWeapon::SetAttackRange(const BoxCollisionParams& owner_collision) {
	int direct_ajust = 0;
	if ((owner->GetDirection() == kRIGHT)) {
		direct_ajust = 1;
	}
	else {
		direct_ajust = -1;
	}

	float center_x = owner_collision.center_position2.x + (owner_collision.box_extent.x * 2)*direct_ajust;
	body_collision.center_position2 = Vector2D(center_x, owner_collision.center_position2.y);
	body_collision.box_extent = { (owner_collision.box_extent.x / 2) * direct_ajust, owner_collision.box_extent.y / 2 };
}
