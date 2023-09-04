#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"


/// <summary>
/// ステージ上に置かれ、管理されるオブジェクト
/// </summary>
class StageObject : public GameObject {

public:
	StageObject();
	virtual ~StageObject();

	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;
	/// <summary>
	/// 衝突判定が起こった場合の処理
	/// </summary>
	/// <param name="hit_object">衝突した相手のオブジェクト</param>
	/// <param name="hit_collision">衝突した相手のコリジョン</param>
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision);

public:	
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>現在の座標</returns>
	Vector2D GetPosition() const { return position; }

	/// <summary>
	/// 座標をセット
	/// </summary>
	/// <param name="new_position">更新された座標</param>
	void SetPosition(const Vector2D& new_position);

	/// <summary>
	/// このオブジェクトのコリジョンを返す
	/// </summary>
	/// <returns>コリジョン</returns>
	BoxCollisionParams GetBodyCollision() const { return body_collision; }
	
	/// <summary>
	/// コリジョンをセットする
	/// </summary>
	/// <param name="collision"></param>
	void SetBodyCollision(const BoxCollisionParams collision) { body_collision = collision; }

	/// <summary>
	/// 中心座標をBoxCollisionParamsにセットする
	/// </summary>
	/// <param name="new_position"></param>
	void SetCenterPosition(const Vector2D& new_position);

protected:
	/// <summary>
	/// コリジョン
	/// </summary>
	BoxCollisionParams body_collision;

private:
	/// <summary>
	/// 位置
	/// </summary>
	Vector2D position;
};

