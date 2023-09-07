#pragma once
#include "Enemy.h"

class BaseWeapon;

/// <summary>
/// �U���\�͂�L����G
/// </summary>
class AttackEnemy : public Enemy {

public:
    AttackEnemy();
    virtual~AttackEnemy();

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
    /// �������̕�����擾
    /// </summary>
    /// <returns></returns>
    BaseWeapon* GetEquipWeapon() { return equip_weapon; }

protected:

    /// <summary>
    /// �������̕���
    /// </summary>
    BaseWeapon* equip_weapon;

    /// <summary>
    /// �U���A�j���[�V����
    /// </summary>
    int attack_enemy_graphic_handle[3];


protected:
    /// <inheritdoc/>
    virtual void Move(float delta_time) override;
   
    /// <summary>
    /// �v���C���[�̏�Ԃ�ύX����
    /// </summary>
    /// <param name="new_state">�V�������</param>
    virtual void ChangeEnemyState(const EEnemyState new_state) override;

    ///<summary>
    /// �V������Ԃ̏���������
    /// </summary>
    virtual void EnterState() override;

    /// <summary>
    /// ��Ԃ��I���Ƃ��̏I������
    /// </summary>
    virtual void ExitState() override;
};