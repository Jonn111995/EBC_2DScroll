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
public:
	/// <summary>
	/// �A�C�e���C�x���g���Z�b�g
	/// </summary>
	/// <param name="item_event">�A�C�e���C�x���g�C���^�[�t�F�[�X</param>
	void SetIItemEvent(IItemEvent* item_event) { this->item_event = item_event; }

private:
	/// <summary>
	/// �A�C�e���C�x���g�C���^�[�t�F�[�X
	/// </summary>
	IItemEvent* item_event;
	/// <summary>
	/// �R�C���̃O���t�B�b�N�n���h��
	/// </summary>
	int coin_graphic_handle;
	/// <summary>
	/// �R�C���l���̌��ʉ��n���h��
	/// </summary>
	int get_coin_sound;
};