#pragma once
#include "../Character.h"
#include "../Enemy/EEnemyState.h"

class IEnemyEvent;

namespace {
    struct SerchRange {

    public:
        Vector2D serch_range_center;

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
    /// �X�e�[�g���Z�b�g����
    /// </summary>
    /// <param name="new_state"></param>
    void SetEnemyState(EEnemyState new_state) { enemy_state = new_state; }

    SerchRange GetSerchRange() { return serch_range; }


    void SetIEnemyEvent(IEnemyEvent* new_interface) { enemy_event = new_interface; }


protected:
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

    float count_time;

    SerchRange serch_range;
    IEnemyEvent* enemy_event;

protected:
    virtual void Move(float delta_time) override;
    ///<summary>
    /// �V������Ԃ̏���������
    /// </summary>
    virtual void EnterState();

    /// <summary>
    /// ��Ԃ��I���Ƃ��̏I������
    /// </summary>
    virtual void ExitState();

    /// <summary>
    /// �v���C���[�̏�Ԃ�ύX����
    /// </summary>
    /// <param name="new_state">�V�������</param>
    virtual void ChangeEnemyState(const EEnemyState new_state);
};