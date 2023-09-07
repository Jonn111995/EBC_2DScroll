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
    /// 攻撃アニメーション
    /// </summary>
    int attack_enemy_graphic_handle[3];

    /// <summary>
    /// 装備中の武器
    /// </summary>
    BaseWeapon* equip_weapon;

protected:
    virtual void Move(float delta_time) override;
    ///<summary>
    /// 新しい状態の初期化処理
    /// </summary>
    virtual void EnterState() override;

    /// <summary>
    /// 状態が終わるときの終了処理
    /// </summary>
    virtual void ExitState() override;

    /// <summary>
    /// プレイヤーの状態を変更する
    /// </summary>
    /// <param name="new_state">新しい状態</param>
    virtual void ChangeEnemyState(const EEnemyState new_state) override;

protected:
    void SetSerchRange();


};