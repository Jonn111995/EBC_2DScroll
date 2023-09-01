#pragma once
#include "../Character.h"

/// <summary>
/// 敵
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
    virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override;

private:
    /// <summary>
    /// 敵のグラフィックハンドル
    /// </summary>
    int wait_enemy_graphic_handle;
};