#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"
#include <vector>

class InputHandler;
class PlayerAnimResourcer;
class BaseWeapon;

namespace {
	/// <summary>
	/// 重力加速力
	/// </summary>
	const float GRAVITY_ACCELARATION = 1.0f;
}

/// <summary>
/// プレイヤー
/// </summary>
class Player : public Character {

private:
	/// <summary>
	/// 入力チェック機能
	/// </summary>
	InputHandler* input_handler;

	/// <summary>
	/// アニメーションハンドルを管理
	/// </summary>
	PlayerAnimResourcer* resourcer;

	BaseWeapon* now_weapon;
	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	EPlayerState player_state;

	/// <summary>
	/// プレイヤーのアニメーションの状態
	/// </summary>
	EPlayerAnimState player_anim_state;

	/// <summary>
	/// ジャンプ出来るかどうか
	/// </summary>
	bool bIsCanJump;

	/// <summary>
	/// 初速度
	/// </summary>
	float initial_velocity;

	/// <summary>
	/// 毎フレーム時間の計測時間
	/// </summary>
	float count_time;

	/// <summary>
	/// ダメージを受けないか？
	/// </summary>
	bool bIsNoDamage;

	/// <summary>
	/// 入力を受け付けるかどうか
	/// </summary>
	bool is_reject_input;

	float invincible_time;

public:
	Player();
	virtual ~Player();

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
	/// アニメーションを変更する
	/// </summary>
	/// <param name="delta_time">毎フレーム時間</param>
	/// <param name="delta_move_amount">更新前と後の移動量の差</param>
	void ChangeAnimState(const float delta_time, const Vector2D& delta_move_amount);

	virtual void GetDamageRecoil(const float delta_time, const Vector2D& recoil_velocity) override;
	virtual void Attack();
	virtual void StopAttack();

private:

	///<summary>
	/// 新しい状態の初期化処理
	/// </summary>
	void EnterState();

	/// <summary>
	/// 状態が終わるときの終了処理
	/// </summary>
	void ExitState();

	/// <summary>
	/// プレイヤーの状態を変更する
	/// </summary>
	/// <param name="new_state">新しい状態</param>
	void ChangePlayerState(const EPlayerState new_state);

	/// <summary>
	/// アニメーションステートが変更されたときの開始処理
	/// </summary>
	void EnterAnimState();

	/// <summary>
	/// アニメフレームが現在のアニメーションの範囲を超えていないか確認
	/// </summary>
	/// <param name="delta_time">毎フレーム時間</param>
	void UpdateAnimFrame(const float delta_time);

	/// <summary>
	/// ジャンプを開始する
	/// </summary>
	void StartJump();

	/// <summary>
	/// ジャンプ中の移動処理
	/// </summary>
	/// <param name="delta_time">毎フレーム時間</param>
	void JumpMove(const float delta_time);
};