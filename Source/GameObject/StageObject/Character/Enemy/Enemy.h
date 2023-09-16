#pragma once
#include "../Character.h"
#include "../Enemy/EEnemyState.h"

class IEnemyEvent;

namespace {
    /// <summary>
    /// ���G�͈͍\����
    /// </summary>
    struct SerchRange {

    public:
        /// <summary>
        /// ���G�͈͂̒��S���W
        /// </summary>
        Vector2D serch_range_center;

        /// <summary>
        /// ���S���W����̍��G�͈�
        /// </summary>
        Vector2D serch_range_extent;
    };
}

/// <summary>
/// �G
/// </summary>
class Enemy : public Character {

public:
    Enemy();
    virtual~Enemy();
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
    /// <inheritdoc/>
    virtual void SetDeadState() override;

public:
    /// <summary>
    /// �X�e�[�g���Z�b�g����
    /// </summary>
    /// <param name="new_state">�V�����X�e�[�g</param>
    void SetEnemyState(EEnemyState new_state) { enemy_state = new_state; }

    /// <summary>
    /// ���G�͈͂��擾
    /// </summary>
    /// <returns>���G�͈͍\����</returns>
    SerchRange GetSerchRange() { return serch_range; }

    /// <summary>
    /// �G�L�����C�x���g�C���^�[�t�F�[�X���Z�b�g
    /// </summary>
    /// <param name="new_interface">�C���^�[�t�F�[�X</param>
    void SetIEnemyEvent(IEnemyEvent* new_interface) { enemy_event = new_interface; }

protected:
    /// <summary>
    /// �G�L�����C�x���g
    /// </summary>
    IEnemyEvent* enemy_event;

    /// <summary>
    /// �ҋ@�A�j���[�V�����n���h��
    /// </summary>
    int wait_enemy_graphic_handle;

    /// <summary>
    /// �ړ��A�j���[�V�����n���h��
    /// </summary>
    int walk_enemy_graphic_handle[4];

    /// <summary>
    /// �_���[�W�A�j���[�V����
    /// </summary>
    int damage_enemy_graphic_handle;

    /// <summary>
    /// �ړ��͈�
    /// </summary>
    float range_move;

    /// <summary>
    /// �ړ���
    /// </summary>
    float move_amount;

    /// <summary>
    /// �G�̃X�e�[�g
    /// </summary>
    EEnemyState enemy_state;

    /// <summary>
    /// ���G�͈�
    /// </summary>
    SerchRange serch_range;

protected:
    /// <inheritdoc />
    virtual void Move(float delta_time) override;
    /// <summary>
    /// ���S���̃��[�V����
    /// </summary>
    /// <param name="delta_time">���t���[������</param>
    /// <returns>true: ���[�V�������� false: ������</returns>
    virtual bool DeadMove(const float delta_time) override;
    /// <summary>
    /// ���g���폜
    /// </summary>
    virtual void CallDestroy() override;

protected:
    /// <summary>
    /// ���G�͈͂��Z�b�g
    /// </summary>
    virtual void SetSerchRange();

    /// <summary>
    /// �v���C���[�̏�Ԃ�ύX����
    /// </summary>
    /// <param name="new_state">�V�������</param>
    virtual void ChangeEnemyState(const EEnemyState new_state);

    ///<summary>
    /// �V������Ԃ̏���������
    /// </summary>
    virtual void EnterState();

    /// <summary>
    /// ��Ԃ��I���Ƃ��̏I������
    /// </summary>
    virtual void ExitState();
};