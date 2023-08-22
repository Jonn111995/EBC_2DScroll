#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"

class Character :public StageObject {

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

    CharacterDirection direction;

public:
    /// <inheritdoc/>
    virtual void Initialize() override {}
    /// <inheritdoc/>
    virtual void Finalize() override {}
    virtual void Update(float delta_time) override {};
    virtual void Draw(const Vector2D& screen_offset) override {};
    virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override {};

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

    void SetDirection(CharacterDirection new_direction) { direction = new_direction; }
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

