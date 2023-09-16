#pragma once
#include "../StageObject.h"

class IGoalEvent;

/// <summary>
/// �S�[��
/// </summary>
class Goal :public StageObject {
public:
	Goal();
	virtual ~Goal();
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
public:
	/// <summary>
	/// �S�[���C�x���g���Z�b�g
	/// </summary>
	/// <param name="goal_event">�S�[���C�x���g�C���^�[�t�F�[�X</param>
	void SetIGoalEvent(IGoalEvent* goal_event) { this->goal_event = goal_event; }
private:
	/// <summary>
	/// �S�[���C�x���g
	/// </summary>
	IGoalEvent* goal_event;

	/// <summary>
	/// �S�[���̃O���t�B�b�N�n���h��
	/// </summary>
	int goal_graphic_handle;

};