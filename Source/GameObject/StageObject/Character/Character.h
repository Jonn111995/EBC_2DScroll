#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"
#include <vector>

class CharacterEventInterface;
class HpUI;

namespace {
    /// <summary>
    /// 移動スピード
    /// </summary>
    const float MOVEMENT_SPEED = 300.f;
}

class Character :public StageObject {

public:
    Character();
    virtual ~Character();
private:
    /// <summary>
    /// HP
    /// </summary>
    int hp;

    /// <summary>
    /// 攻撃力
    /// </summary>
    int attack;

    /// <summary>
    /// 防御力
    /// </summary>
    int deffence;

    /// <summary>
    /// 移動スピード
    /// </summary>
    float move_speed;

    /// <summary>
    /// 動いているかどうか
    /// </summary>
    bool bIsMove;

    /// <summary>
    /// 移動方向
    /// </summary>
    CharacterDirection direction;

protected:
    /// <summary>
    /// キャラクターイベントインターフェース
    /// </summary>
    CharacterEventInterface* character_event;

    /// <summary>
    /// 移動ベクトル
    /// </summary>
    Vector2D input_direction;

    /// <summary>
    /// 現在のアニメーション
    /// </summary>
    std::vector<int> now_animations;

    /// <summary>
    /// アニメーションを変化させる値
    /// </summary>
    float animation_frame;

    /// <summary>
    /// アニメーションスピード
    /// </summary>
    float anim_speed;

    /// <summary>
    /// アニメーションフレームの最小値
    /// </summary>
    float min_anim_frame;

    /// <summary>
    /// アニメーションフレームの最大値
    /// </summary>
    float max_anim_frame;

    bool is_get_damaged;
    HpUI* hp_ui;
protected:
    /// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="delta_time">毎フレーム時間</param>
    virtual void Move(float delta_time);

    /// <summary>
    /// ノックバックする
    /// </summary>
    /// <param name="delta_time">毎フレーム時間</param>
    /// <param name="knock_back_dir">ノックバックする方向</param>
    virtual void KnockBack(const float delta_time, const Vector2D& knock_back_dir);

    /// <summary>
    /// キャラの向きを反対に変更。
    /// </summary>
    void ReverseDirection();

    virtual void CallDeadEvent();

protected:
    /// <summary>
    /// ノックバックのベクトル
    /// </summary>
    Vector2D knock_back_dir;

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

    /// <summary>
    /// キャラクターイベントインターフェースを設定
    /// </summary>
    void SetICharacterEvent(CharacterEventInterface* character_interface) { character_event = character_interface; };
    void SetHpUi(HpUI& hp_ui);

public:
    const int MAX_HP;
    void SetHp(const int new_hp) { hp = new_hp; }
    /// <summary>
    /// HPを取得
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }

    void SetAttack(const int attack) { this->attack = attack; }
    /// <summary>
    /// 攻撃力を取得
    /// </summary>
    /// <returns>攻撃力</returns>
    int GetAttack() const { return attack; }

    /// <summary>
    /// 防御力を取得
    /// </summary>
    /// <returns>防御力</returns>
    int GetDeffence() const { return deffence; }

    /// <summary>
    /// 移動スピードを取得
    /// </summary>
    /// <returns>移動スピード</returns>
    float GetSpeed() const { return move_speed; }

    /// <summary>
    /// 移動スピードをセット
    /// </summary>
    /// <param name="speed">移動スピード</param>
    void SetSpeed(const float speed) { move_speed = speed; };

    /// <summary>
    /// 移動しているかどうかのフラグをセット
    /// </summary>
    /// <param name="bIs_move">
    ///   true:移動している
    ///   false:移動していない
    /// </param>
    void SetbIsMove(const bool bIs_move) { bIsMove = bIs_move; }

    /// <summary>
    /// 移動しているかどうかを取得
    /// </summary>
    bool GetbIsMove() const { return bIsMove; }

    /// <summary>
    /// キャラの移動方向を設定
    /// </summary>
    /// <param name="new_direction">移動方向</param>
    void SetDirection(CharacterDirection new_direction) { direction = new_direction;}

    /// <summary>
    /// キャラの移動方向を取得
    /// </summary>
    /// <returns>移動方向</returns>
    CharacterDirection GetDirection() { return direction; }

    /// <summary>
    /// ダメージを与える
    /// </summary>
    /// <param name="target">ダメージを与えるキャラ</param>
    void GiveDamage(Character& target, int damage);

    /// <summary>
    /// ダメージを受ける
    /// </summary>
    /// <param name="opponent">攻撃してきたキャラ</param>
    /// <param name="damage">ダメージ</param>
    void GetDamage(Character& opponent, const int damage);

    void CallGiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage);

    bool GetIsGetDmaged() { return is_get_damaged; }

    void UpdateHpUI(const int new_hp);
};

