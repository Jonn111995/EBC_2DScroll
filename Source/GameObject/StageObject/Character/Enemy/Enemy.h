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

    SerchRange GetSerchRange() { return serch_range; }


    void SetIEnemyEvent(IEnemyEvent* new_interface) { enemy_event = new_interface; }


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

    SerchRange serch_range;
    IEnemyEvent* enemy_event;

protected:
    virtual void Move(float delta_time) override;
    ///<summary>
    /// 新しい状態の初期化処理
    /// </summary>
    virtual void EnterState();

    /// <summary>
    /// 状態が終わるときの終了処理
    /// </summary>
    virtual void ExitState();

    /// <summary>
    /// プレイヤーの状態を変更する
    /// </summary>
    /// <param name="new_state">新しい状態</param>
    virtual void ChangeEnemyState(const EEnemyState new_state);
};