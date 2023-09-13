#pragma once
#include "../StageObject.h"

class IItemEvent;

class Coin : public StageObject {
public:
	Coin();
	virtual ~Coin();

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
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision);
	void SetIItemEvent(IItemEvent* item_event) { this->item_event = item_event; }

private:
	IItemEvent* item_event;
	int coin_graphic_handle;
};