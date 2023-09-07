#pragma once
#include "Enemy.h"

class BaseWeapon;

/// <summary>
/// 攻撃能力を有する敵
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
    /// 装備中の武器を取得
    /// </summary>
    /// <returns></returns>
    BaseWeapon* GetEquipWeapon() { return equip_weapon; }

protected:

    /// <summary>
    /// 装備中の武器
    /// </summary>
    BaseWeapon* equip_weapon;

    /// <summary>
    /// 攻撃アニメーション
    /// </summary>
    int attack_enemy_graphic_handle[3];


protected:
    /// <inheritdoc/>
    virtual void Move(float delta_time) override;
   
    /// <summary>
    /// プレイヤーの状態を変更する
    /// </summary>
    /// <param name="new_state">新しい状態</param>
    virtual void ChangeEnemyState(const EEnemyState new_state) override;

    ///<summary>
    /// 新しい状態の初期化処理
    /// </summary>
    virtual void EnterState() override;

    /// <summary>
    /// 状態が終わるときの終了処理
    /// </summary>
    virtual void ExitState() override;
};