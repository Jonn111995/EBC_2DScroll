#pragma once
#include "../StageObject.h"

class Character;

class BaseWeapon : public StageObject {
public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override {};
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override {};
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override {};
	///  <inheritdoc/>
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override {};
public:
	virtual void SetAttackRange(const BoxCollisionParams& owner_collision);

	void SetOwner(Character* owner) { this->owner = owner; }
protected:
	Character* owner;
};