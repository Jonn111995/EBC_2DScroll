#pragma once
#include "BaseWeapon.h"

class Hand : public BaseWeapon {

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;
	///  <inheritdoc/>
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override;
	virtual void SetAttackRange(const BoxCollisionParams& owner_collision);

public:
	
};