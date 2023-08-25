#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"
#include "EPlayerAnimState.h"


#include <vector>

class InputHandler;
class PlayerAnimResourcer;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public Character {

private:
	int xxx;
	int yyy;
	/// <summary>
	/// 入力チェック機能
	/// </summary>
	InputHandler* input_handler;

	/// <summary>
	/// アニメーションハンドルを管理
	/// </summary>
	PlayerAnimResourcer* resourcer;
	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	EPlayerState player_state;

	/// <summary>
	/// プレイヤーのアニメーションの状態
	/// </summary>
	EPlayerAnimState player_anim_state;

	/// <summary>
	/// 現在のアニメーション
	/// </summary>
	std::vector<int> now_animations;

	/// <summary>
	/// アニメーションを変化させる値
	/// </summary>
	float animation_frame;

	/// <summary>
	/// ジャンプ出来るかどうか
	/// </summary>
	bool bIsCanJump = true;

	/// <summary>
	/// 加速力
	/// </summary>
	int velocity = 0;
	/// <summary>
	/// 重力加速力
	/// </summary>
	int gravity_accelaration = 1;
	/// <summary>
	/// ジャンプしたときの地面のy座標
	/// </summary>
	int y_ground = 0;
	/// <summary>
	/// アニメーションスピード
	/// </summary>
	float anim_speed = 0.0f;
	/// <summary>
	/// アニメーションフレームの最小値
	/// </summary>
	float min_anim_frame;
	/// <summary>
	/// アニメーションフレームの最大値
	/// </summary>
	float max_anim_frame;

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
	virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override;

private:
	/// <summary>
	/// プレイヤーの状態を変更する
	/// </summary>
	/// <param name="new_state">新しい状態</param>
	void ChangePlayerState(const EPlayerState new_state);
	/// <summary>
	/// 新しい状態の初期化処理
	/// </summary>
	void EnterState();
	/// <summary>
	/// 状態が終わるときの終了処理
	/// </summary>
	void ExitState();

	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();
};