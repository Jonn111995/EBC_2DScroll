#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"


/// <summary>
/// ステージ上に置かれ、管理されるオブジェクト
/// </summary>
class StageObject : public GameObject {

private:
	// 位置
	Vector2D position;

	/// <summary>
	/// コリジョン
	/// </summary>
	BoxCollisionParams body_collision;

public:
	virtual void Update(float delta_seconds) {}
	virtual void Draw(const Vector2D& screen_offset) {}

public:
	StageObject();
	virtual ~StageObject();
	/**
	 * Positionの取得
	 * @return	position
	 */
	Vector2D GetPosition() const { return position; }

	/**
	 * Positionのセット
	 * @param	new_position	セットするPosition
	 */
	void SetPosition(const Vector2D& new_position);

	/// <summary>
	/// このオブジェクトのコリジョンを返す
	/// </summary>
	/// <returns>コリジョン</returns>
	BoxCollisionParams GetBodyCollision() const { return body_collision; }

	/// <summary>
	/// 衝突判定が起こった場合の処理
	/// </summary>
	/// <param name="hit_object">衝突した相手のオブジェクト</param>
	/// <param name="hit_collision">衝突した相手のコリジョン</param>
	virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision);
};

