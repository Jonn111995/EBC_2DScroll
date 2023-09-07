#pragma once
#include "Enemy.h"


class BaseWeapon;

class AttackEnemy : public Enemy {

public:
    AttackEnemy();
    virtual~AttackEnemy();
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
    BaseWeapon* GetEquipWeapon() { return equip_weapon; }

protected:

    /// <summary>
    /// �U���A�j���[�V����
    /// </summary>
    int attack_enemy_graphic_handle[3];

    /// <summary>
    /// �������̕���
    /// </summary>
    BaseWeapon* equip_weapon;

protected:
    virtual void Move(float delta_time) override;
    ///<summary>
    /// �V������Ԃ̏���������
    /// </summary>
    virtual void EnterState() override;

    /// <summary>
    /// ��Ԃ��I���Ƃ��̏I������
    /// </summary>
    virtual void ExitState() override;

    /// <summary>
    /// �v���C���[�̏�Ԃ�ύX����
    /// </summary>
    /// <param name="new_state">�V�������</param>
    virtual void ChangeEnemyState(const EEnemyState new_state) override;

protected:
    void SetSerchRange();


};