#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"
#include <vector>

class InputHandler;
class PlayerAnimResourcer;
class BaseWeapon;

namespace {
	/// <summary>
	/// �d�͉�����
	/// </summary>
	const float GRAVITY_ACCELARATION = 1.0f;
}

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

	BaseWeapon* now_weapon;
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
	bool bIsCanJump;

	/// <summary>
	/// �����x
	/// </summary>
	float initial_velocity;

	/// <summary>
	/// ���t���[�����Ԃ̌v������
	/// </summary>
	float count_time;

	/// <summary>
	/// �_���[�W���󂯂Ȃ����H
	/// </summary>
	bool bIsNoDamage;

	/// <summary>
	/// ���͂��󂯕t���邩�ǂ���
	/// </summary>
	bool is_reject_input;

	float invincible_time;

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
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override;

protected:
	/// <summary>
	/// �A�j���[�V������ύX����
	/// </summary>
	/// <param name="delta_time">���t���[������</param>
	/// <param name="delta_move_amount">�X�V�O�ƌ�̈ړ��ʂ̍�</param>
	void ChangeAnimState(const float delta_time, const Vector2D& delta_move_amount);

	virtual void GetDamageRecoil(const float delta_time, const Vector2D& recoil_velocity) override;
	virtual void Attack();
	virtual void StopAttack();

private:

	///<summary>
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

	/// <summary>
	/// �A�j���[�V�����X�e�[�g���ύX���ꂽ�Ƃ��̊J�n����
	/// </summary>
	void EnterAnimState();

	/// <summary>
	/// �A�j���t���[�������݂̃A�j���[�V�����͈̔͂𒴂��Ă��Ȃ����m�F
	/// </summary>
	/// <param name="delta_time">���t���[������</param>
	void UpdateAnimFrame(const float delta_time);

	/// <summary>
	/// �W�����v���J�n����
	/// </summary>
	void StartJump();

	/// <summary>
	/// �W�����v���̈ړ�����
	/// </summary>
	/// <param name="delta_time">���t���[������</param>
	void JumpMove(const float delta_time);
};