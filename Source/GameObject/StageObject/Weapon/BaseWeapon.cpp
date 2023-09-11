#include "BaseWeapon.h"
#include "../Source/GameObject/StageObject/Character/Character.h"

BaseWeapon::BaseWeapon()
{
}

BaseWeapon::~BaseWeapon()
{
}

void BaseWeapon::Initialize() {
	body_collision.hit_object_types = kPLAYER_TYPE | kENEMY_TYPE;
	body_collision.object_type = kWEAPON_TYPE;
}

void BaseWeapon::Finalize() {
	owner = nullptr;
}

void BaseWeapon::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	//‚±‚±‚ÅƒLƒƒƒ‰‚ÌUŒ‚ˆ—‚ðŒÄ‚Ô
}

void BaseWeapon::SetAttackRange(const BoxCollisionParams& owner_collision) {
	int direct_ajust = 1;
	switch (owner->GetBodyCollision().object_type) {
	case kPLAYER_TYPE:
		if (now_direction == EWeaponDirection::kLEFT) {
			direct_ajust = -1;
		}
		break;

	case kENEMY_TYPE:
		if (now_direction == EWeaponDirection::kRIGHT) {
			direct_ajust = -1;
		}
		break;
	}
	
	float center_x = owner_collision.center_position2.x + (owner_collision.box_extent.x * 3)*direct_ajust;
	body_collision.center_position2 = Vector2D(center_x, owner_collision.center_position2.y);
	body_collision.box_extent = { (owner_collision.box_extent.x), owner_collision.box_extent.y / 2 };
}

void BaseWeapon::SetWeaponDirection() {

	if (owner->GetDirection() == kRIGHT) {

		now_direction = EWeaponDirection::kRIGHT;
	}
	else {
		now_direction = EWeaponDirection::kLEFT;
	}
}

