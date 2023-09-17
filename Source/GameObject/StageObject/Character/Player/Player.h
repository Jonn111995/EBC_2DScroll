#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"
#include <vector>

class InputHandler;
class PlayerAnimResourcer;
class BaseWeapon;
class IPlayerEvent;

namespace {
	const float AIR_RESISTANCE = 0.8f;
	const float RESET_INITIAL_VELOCITY = 0.0f;
	const float DEFAULT_INVINCIBLE_TIME = 1.5f;
}

/// <summary>
/// プレイヤー
/// </summary>
class Player : public Character {

public:
	Player();
	virtual ~Player();

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
	/// プレイヤーイベントをセット
	/// </summary>
	void SetIPlayerEvent(IPlayerEvent* player_event) { this->player_event = player_event; }
	/// <summary>
	/// 無敵時間をセット
	/// </summary>
	/// <param name="time">毎フレーム時間</param>
	void SetInvincibleTime(float time) { invincible_time = time; };
	/// <summary>
	/// アイテムを使用中か？
	/// </summary>
	/// <param name="is_use">使用しているかどうか?</param>
	void SetIsUseItem(bool is_use) { is_use_item = is_use; }
	/// <summary>
	/// 無敵ステートに変更
	/// </summary>
	void SetInvincibleState();
	/// <summary>
	/// 死亡ステートに変更
	/// </summary>
	void SetDeadState() override;

protected:
	/// <summary>
	/// プレイヤーイベント
	/// </summary>
	IPlayerEvent* player_event;
private:
	/// <summary>
	/// 入力チェック機能
	/// </summary>
	InputHandler* input_handler;

	/// <summary>
	/// アニメーションハンドルを管理
	/// </summary>
	PlayerAnimResourcer* resourcer;

	/// <summary>
	/// 装備中の武器
	/// </summary>
	BaseWeapon* equip_weapon;

	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	EPlayerState player_state;

	/// <summary>
	/// プレイヤーのアニメーションの状態
	/// </summary>
	EPlayerAnimState player_anim_state;

	/// <summary>
	/// 無敵時間
	/// </summary>
	float invincible_time;

	/// <summary>
	/// ジャンプ出来るかどうか
	/// </summary>
	bool bIsCanJump;

	

	/// <summary>
	/// アイテムを使用しているか？
	/// </summary>
	bool is_use_item;

	/// <summary>
	/// 入力を受け付けるかどうか
	/// </summary>
	bool is_reject_input;

protected:
	/// <summary>
	/// プレイヤーの状態を変更する
	/// </summary>
	/// <param name="new_state">新しい状態</param>
	void ChangePlayerState(const EPlayerState new_state);
	/// <summary>
	/// アニメーションを変更する
	/// </summary>
	/// <param name="delta_time">毎フレーム時間</param>
	/// <param name="delta_move_amount">更新前と後の移動量の差</param>
	void ChangeAnimState(const float delta_time, const Vector2D& delta_move_amount);

	/// <summary>
	/// 攻撃を開始
	/// </summary>
	virtual void Attack();

	/// <summary>
	/// 攻撃を止める
	/// </summary>
	virtual void StopAttack();

	virtual bool DeadMove(const float delta_time) override;
	virtual void CallDestroy() override;

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