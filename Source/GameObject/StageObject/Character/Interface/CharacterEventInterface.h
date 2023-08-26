#pragma once

class CharacterEventInterface {

public:
	virtual bool CheckCanMove(const Vector2D& move_to_position, const BoxCollisionParams& collision) = 0;
	virtual bool CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) = 0;
};