#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"
#include <vector>

class InputHandler;
class PlayerAnimResourcer;
class BaseWeapon;
class IPlayerEvent;

namespace {
	const float AIR_RESISTANCE = 0.8f;
	const float RESET_INITIAL_VELOCITY = 0.0f;
	const float DEFAULT_INVINCIBLE_TIME = 1.5f;
}

/// <summary>
/// �v���C���[
/// </summary>
class Player : public Character {

public:
	Player();
	virtual ~Player();

public:
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

public:
	/// <summary>
	/// �v���C���[�C�x���g���Z�b�g
	/// </summary>
	void SetIPlayerEvent(IPlayerEvent* player_event) { this->player_event = player_event; }
	/// <summary>
	/// ���G���Ԃ��Z�b�g
	/// </summary>
	/// <param name="time">���t���[������</param>
	void SetInvincibleTime(float time) { invincible_time = time; };
	/// <summary>
	/// �A�C�e�����g�p�����H
	/// </summary>
	/// <param name="is_use">�g�p���Ă��邩�ǂ���?</param>
	void SetIsUseItem(bool is_use) { is_use_item = is_use; }
	/// <summary>
	/// ���G�X�e�[�g�ɕύX
	/// </summary>
	void SetInvincibleState();
	/// <summary>
	/// ���S�X�e�[�g�ɕύX
	/// </summary>
	void SetDeadState() override;

protected:
	/// <summary>
	/// �v���C���[�C�x���g
	/// </summary>
	IPlayerEvent* player_event;
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
	/// �������̕���
	/// </summary>
	BaseWeapon* equip_weapon;

	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	EPlayerState player_state;

	/// <summary>
	/// �v���C���[�̃A�j���[�V�����̏��
	/// </summary>
	EPlayerAnimState player_anim_state;

	/// <summary>
	/// ���G����
	/// </summary>
	float invincible_time;

	/// <summary>
	/// �W�����v�o���邩�ǂ���
	/// </summary>
	bool bIsCanJump;

	

	/// <summary>
	/// �A�C�e�����g�p���Ă��邩�H
	/// </summary>
	bool is_use_item;

	/// <summary>
	/// ���͂��󂯕t���邩�ǂ���
	/// </summary>
	bool is_reject_input;

protected:
	/// <summary>
	/// �v���C���[�̏�Ԃ�ύX����
	/// </summary>
	/// <param name="new_state">�V�������</param>
	void ChangePlayerState(const EPlayerState new_state);
	/// <summary>
	/// �A�j���[�V������ύX����
	/// </summary>
	/// <param name="delta_time">���t���[������</param>
	/// <param name="delta_move_amount">�X�V�O�ƌ�̈ړ��ʂ̍�</param>
	void ChangeAnimState(const float delta_time, const Vector2D& delta_move_amount);

	/// <summary>
	/// �U�����J�n
	/// </summary>
	virtual void Attack();

	/// <summary>
	/// �U�����~�߂�
	/// </summary>
	virtual void StopAttack();

	virtual bool DeadMove(const float delta_time) override;
	virtual void CallDestroy() override;

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