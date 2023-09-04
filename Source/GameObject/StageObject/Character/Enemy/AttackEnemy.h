#pragma once
#include "Enemy.h"

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

protected:
    /// <summary>
    /// 攻撃アニメーション
    /// </summary>
    int attack_enemy_graphic_handle[3];

};