#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"
#include <vector>

class CharacterEventInterface;

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
    float speed;

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
    CharacterEventInterface* ICharacterEvent;

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
protected:

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
    virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override {};

    /// <summary>
    /// キャラクターイベントインターフェースを設定
    /// </summary>
    void SetICharacterEvent(CharacterEventInterface* interface) { ICharacterEvent = interface; };

public:
    /// <summary>
    /// HPを取得
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }

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
    float GetSpeed() const { return speed; }

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
    void GiveDamage(Character& target);

    /// <summary>
    /// ダメージを受ける
    /// </summary>
    /// <param name="opponent">攻撃してきたキャラ</param>
    /// <param name="damage">ダメージ</param>
    void GetDamage(Character& opponent, const int damage);
};

