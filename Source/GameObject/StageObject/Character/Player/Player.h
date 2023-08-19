#pragma once
#include "../Source/GameObject/StageObject/Character/Character.h"
#include "EPlayerState.h"

class InputHandler;

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
	/// プレイヤーの状態
	/// </summary>
	EPlayerState player_state;

	int loaded_sprits[4];

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
};