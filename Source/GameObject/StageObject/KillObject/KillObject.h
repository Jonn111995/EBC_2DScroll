#pragma once
#include "../StageObject.h"

class IStageObjectInterface;
class IKillEvent;

class KillObject : public StageObject {
public:
	KillObject();
	virtual ~KillObject();

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
	void SetIStageObjectEvent(IStageObjectInterface* stage_object_event) { this->stage_object_event = stage_object_event; }
	void SetIKillEvent(IKillEvent* kill_event) { this->kill_event = kill_event; }
private:
	IKillEvent* kill_event;
	IStageObjectInterface* stage_object_event;
};