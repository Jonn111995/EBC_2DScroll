#pragma once
#include "../Character.h"
#include "../Enemy/EEnemyState.h"

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
};