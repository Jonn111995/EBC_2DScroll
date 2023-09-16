#pragma once
#include "../Character.h"
#include "../Enemy/EEnemyState.h"

class IEnemyEvent;

namespace {
    /// <summary>
    /// 索敵範囲構造体
    /// </summary>
    struct SerchRange {

    public:
        /// <summary>
        /// 索敵範囲の中心座標
        /// </summary>
        Vector2D serch_range_center;

        /// <summary>
        /// 中心座標からの索敵範囲
        /// </summary>
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
    /// <inheritdoc/>
    virtual void SetDeadState() override;

public:
    /// <summary>
    /// ステートをセットする
    /// </summary>
    /// <param name="new_state">新しいステート</param>
    void SetEnemyState(EEnemyState new_state) { enemy_state = new_state; }

    /// <summary>
    /// 索敵範囲を取得
    /// </summary>
    /// <returns>索敵範囲構造体</returns>
    SerchRange GetSerchRange() { return serch_range; }

    /// <summary>
    /// 敵キャライベントインターフェースをセット
    /// </summary>
    /// <param name="new_interface">インターフェース</param>
    void SetIEnemyEvent(IEnemyEvent* new_interface) { enemy_event = new_interface; }

protected:
    /// <summary>
    /// 敵キャライベント
    /// </summary>
    IEnemyEvent* enemy_event;

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

    /// <summary>
    /// 索敵範囲
    /// </summary>
    SerchRange serch_range;

protected:
    /// <inheritdoc />
    virtual void Move(float delta_time) override;
    /// <summary>
    /// 死亡時のモーション
    /// </summary>
    /// <param name="delta_time">毎フレーム時間</param>
    /// <returns>true: モーション完了 false: 未完了</returns>
    virtual bool DeadMove(const float delta_time) override;
    /// <summary>
    /// 自身を削除
    /// </summary>
    virtual void CallDestroy() override;

protected:
    /// <summary>
    /// 索敵範囲をセット
    /// </summary>
    virtual void SetSerchRange();

    /// <summary>
    /// プレイヤーの状態を変更する
    /// </summary>
    /// <param name="new_state">新しい状態</param>
    virtual void ChangeEnemyState(const EEnemyState new_state);

    ///<summary>
    /// 新しい状態の初期化処理
    /// </summary>
    virtual void EnterState();

    /// <summary>
    /// 状態が終わるときの終了処理
    /// </summary>
    virtual void ExitState();
};