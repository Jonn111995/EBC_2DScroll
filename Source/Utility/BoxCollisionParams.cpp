#include "BoxCollisionParams.h"

bool BoxCollisionParams::IsHitCheckTarget(CollisionObjectType target) {

	return hit_object_types & target;
}

void BoxCollisionParams::SetHittdSruface(EHitSurface hitted_surface) {
	
	is_hit_surfaces[static_cast<int>(EHitSurface::kTOP)] = false;
	is_hit_surfaces[static_cast<int>(EHitSurface::kBOTTOM)] = false;
	is_hit_surfaces[static_cast<int>(EHitSurface::kRIGHT)] = false;
	is_hit_surfaces[static_cast<int>(EHitSurface::kLEFT)] = false;


	is_hit_surfaces[static_cast<int>(hitted_surface)] = true;
}

void BoxCollisionParams::SetCenterPosition(Vector2D position) {
	center_position2 = position;
}

Vector2D BoxCollisionParams::GetLeftTopPosition() {

	return Vector2D((center_position.x - box_extent.x), (center_position.y - box_extent.y));
}

Vector2D BoxCollisionParams::GetRightTopPosition() {
	return Vector2D((center_position.x + box_extent.x), (center_position.y - box_extent.y));
}

Vector2D BoxCollisionParams::GetLeftDownPosition() {
	return Vector2D((center_position.x + box_extent.x), (center_position.y + box_extent.y));
}

Vector2D BoxCollisionParams::GetRightDownPosition() {
	return Vector2D((center_position.x - box_extent.x), (center_position.y + box_extent.y));
}
