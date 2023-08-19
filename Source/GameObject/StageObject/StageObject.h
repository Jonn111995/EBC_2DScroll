#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"

/// <summary>
/// ステージ上に置かれ、管理されるオブジェクト
/// </summary>
class StageObject : public GameObject {

private:
	// 位置
	Vector2D position;

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
};

