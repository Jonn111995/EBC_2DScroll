#pragma once
#include "../StageObject.h"

class IItemEvent;

class InvincibleCan : public StageObject {

public:
	InvincibleCan();
	virtual ~InvincibleCan();

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
	/// <summary>
	/// �A�C�e���C�x���g
	/// </summary>
	IItemEvent* item_event;

	/// <summary>
	/// ���G���ʎ�������
	/// </summary>
	float invincible_time;
	/// <summary>
	/// ���G�ʂ̃O���t�B�b�N�n���h��
	/// </summary>
	int invincible_can_graphic;
	/// <summary>
	/// ���G�ʊl�����̌��ʉ�
	/// </summary>
	int get_invincible_can_sound;
};