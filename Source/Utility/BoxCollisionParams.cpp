#include "BoxCollisionParams.h"

bool BoxCollisionParams::IsHitCheckTarget(CollisionObjectType target) {
	return false;
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
