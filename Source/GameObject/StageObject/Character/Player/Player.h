#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"

class InputHandler;

/// <summary>
/// �v���C���[
/// </summary>
class Player : public Character {

private:

	/// <summary>
	/// ���̓`�F�b�N�@�\
	/// </summary>
	InputHandler* input_handler;
	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	EPlayerState player_state;

	int loaded_sprits[4];

public:
	Player();
	virtual ~Player();

	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_time) override;
	/// <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;
	/// <inheritdoc/>
	virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override;

private:
	/// <summary>
	/// �v���C���[�̏�Ԃ�ύX����
	/// </summary>
	/// <param name="new_state">�V�������</param>
	void ChangePlayerState(const EPlayerState new_state);
	/// <summary>
	/// �V������Ԃ̏���������
	/// </summary>
	void EnterState();
	/// <summary>
	/// ��Ԃ��I���Ƃ��̏I������
	/// </summary>
	void ExitState();
};