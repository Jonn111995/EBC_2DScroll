#pragma once
#include "../Character.h"
#include "../Enemy/EEnemyState.h"

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
    virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override;

public:
    /// <summary>
    /// ステートをセットする
    /// </summary>
    /// <param name="new_state"></param>
    void SetEnemyState(EEnemyState new_state) { enemy_state = new_state; }

protected:
    /// <summary>
    /// 待機アニメーションハンドル
    /// </summary>
    int wait_enemy_graphic_handle;

    /// <summary>
    /// 移動アニメーションハンドル
    /// </summary>
    int walk_enemy_graphic_handle[4];

    /// <summary>
    /// ダメージアニメーション
    /// </summary>
    int damage_enemy_graphic_handle;

    /// <summary>
    /// 移動範囲
    /// </summary>
    float range_move;

    /// <summary>
    /// 移動量
    /// </summary>
    float move_amount;

    /// <summary>
    /// 敵のステート
    /// </summary>
    EEnemyState enemy_state;
    float count_time;
};