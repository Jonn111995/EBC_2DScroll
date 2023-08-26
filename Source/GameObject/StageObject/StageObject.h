#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"


/// <summary>
/// ステージ上に置かれ、管理されるオブジェクト
/// </summary>
class StageObject : public GameObject {

private:
	/// <summary>
	/// 位置
	/// </summary>
	Vector2D position;

protected:
	/// <summary>
	/// コリジョン
	/// </summary>
	BoxCollisionParams body_collision;

public:
	/// <inheritdoc/>
	virtual void Initialize() override{}
	/// <inheritdoc/>
	virtual void Finalize() override{}
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override {}
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override {}

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
	void SetBodyCollision(const BoxCollisionParams collision) { body_collision = collision; }

	/// <summary>
	/// 衝突判定が起こった場合の処理
	/// </summary>
	/// <param name="hit_object">衝突した相手のオブジェクト</param>
	/// <param name="hit_collision">衝突した相手のコリジョン</param>
	virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision);
};

