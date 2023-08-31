#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"


#include <vector>

class InputHandler;
class PlayerAnimResourcer;

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
	/// �A�j���[�V�����n���h�����Ǘ�
	/// </summary>
	PlayerAnimResourcer* resourcer;
	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	EPlayerState player_state;

	/// <summary>
	/// �v���C���[�̃A�j���[�V�����̏��
	/// </summary>
	EPlayerAnimState player_anim_state;

	


	/// <summary>
	/// �W�����v�o���邩�ǂ���
	/// </summary>
	bool bIsCanJump = true;

	/// <summary>
	/// ������
	/// </summary>
	float velocity = 0.0f;
	/// <summary>
	/// �d�͉�����
	/// </summary>
	float gravity_accelaration = 1.0f;
	/// <summary>
	/// �W�����v�����Ƃ��̒n�ʂ�y���W
	/// </summary>
	int y_ground = 0;
	/// <summary>
	/// �A�j���[�V�����X�s�[�h
	/// </summary>
	float anim_speed = 0.0f;
	/// <summary>
	/// �A�j���[�V�����t���[���̍ŏ��l
	/// </summary>
	float min_anim_frame;
	/// <summary>
	/// �A�j���[�V�����t���[���̍ő�l
	/// </summary>
	float max_anim_frame;

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

protected:
	void ChangeAnimState(const float delta_timeconst, const  Vector2D& delta_position);

private:

/// <summary>
	/// �V������Ԃ̏���������
	/// </summary>
	void EnterState();

	/// <summary>
	/// ��Ԃ��I���Ƃ��̏I������
	/// </summary>
	void ExitState();

	/// <summary>
	/// �v���C���[�̏�Ԃ�ύX����
	/// </summary>
	/// <param name="new_state">�V�������</param>
	void ChangePlayerState(const EPlayerState new_state);

	void EnterAnimState();

	void CheckAnimFrame(const float delta_time);

	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();
};