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
    /// <summary>
    /// 重力加速力
    /// </summary>
    const float GRAVITY_ACCELARATION = 1.0f;
    /// <summary>
    /// ジャンプの際の上方への初速度
    /// </summary>
    const int INITIAL_JUMP_VELOCITY = -25;
    /// <summary>
    /// 死亡時のモーションの秒数
    /// </summary>
    const float DEAD_MOVE_TIME = 1.5f;
}

class Character :public StageObject {

public:
    Character();
    virtual ~Character();

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
    /// HPをセットする
    /// </summary>
    /// <param name="new_hp"></param>
    void SetHp(const int new_hp) { hp = new_hp; }
    /// <summary>
    /// HPを取得
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }
    int GetMaxHp() const { return MAX_HP; }

    /// <summary>
    /// 攻撃力をセットする
    /// </summary>
    /// <param name="attack"></param>
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
    void SetIsMove(const bool is_move) { this->is_move = is_move; }

    /// <summary>
    /// 移動しているかどうかを取得
    /// </summary>
    bool GetIsMove() const { return is_move; }

    /// <summary>
    /// キャラの移動方向を設定
    /// </summary>
    /// <param name="new_direction">移動方向</param>
    void SetDirection(CharacterDirection new_direction) { direction = new_direction; }

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

    /// <summary>
    /// ダメージを与えるイベントを呼ぶ
    /// </summary>
    /// <param name="give_gamage_chara"></param>
    /// <param name="opponent_chara"></param>
    /// <param name="damage"></param>
    void CallGiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage);

    /// <summary>
    /// HPUIを更新する
    /// </summary>
    /// <param name="new_hp">新しいHP</param>
    void UpdateHpUI(const int new_hp);

    /// <summary>
   /// キャラクターイベントインターフェースを設定
   /// </summary>
    void SetICharacterEvent(CharacterEventInterface* character_interface) { character_event = character_interface; };

    /// <summary>
    /// HPUIをセットする
    /// </summary>
    /// <param name="hp_ui"></param>
    void SetHpUi(HpUI& hp_ui);

    bool GetIsNoDamage() const { return is_no_damage; }

protected:
   
    /// <summary>
    /// キャラクターイベントインターフェース
    /// </summary>
    CharacterEventInterface* character_event;

    /// <summary>
    /// HPUI
    /// </summary>
    HpUI* hp_ui;

    /// <summary>
    /// ダメージを受けないか？
    /// </summary>
    bool is_no_damage;
    /// <summary>
    /// 移動ベクトル
    /// </summary>
    Vector2D input_direction;

    /// <summary>
    /// 初速度
    /// </summary>
    float initial_velocity;

    /// <summary>
    /// 毎フレーム時間の計測時間
    /// </summary>
    float count_time;

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

    /// <summary>
    /// ノックバックのベクトル
    /// </summary>
    Vector2D knock_back_dir;

    int get_damage_sound;

protected:
    /// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="delta_time">毎フレーム時間</param>
    virtual void Move(float delta_time);

    virtual float UpdateXPosition(const bool is_can_move_to_x, const float update_x_amount);
    virtual float UpdateYPosition(const bool is_can_move_to_y, const float update_y_amount);

    /// <summary>
    /// キャラの向きを反対に変更。
    /// </summary>
    void ReverseDirection();

    /// <summary>
    /// 死亡状態に変更する。オーバーライド前提
    /// </summary>
    virtual void SetDeadState();

    /// <summary>
    /// 死亡時の移動モーション
    /// </summary>
    /// <param name="delta_time">毎フレーム時間</param>
    /// <returns>true: モーション完了 false: 未完了</returns>
    virtual bool DeadMove(const float delta_time);

    /// <summary>
    /// 自身を削除
    /// </summary>
    virtual void CallDestroy();

private:
    /// <summary>
    /// HP
    /// </summary>
    int hp;

    /// <summary>
    /// 最大HP
    /// </summary>
    const int MAX_HP;

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
    bool is_move;

    /// <summary>
    /// 移動方向
    /// </summary>
    CharacterDirection direction;
};

