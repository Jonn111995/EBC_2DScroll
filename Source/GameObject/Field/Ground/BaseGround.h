#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include <vector>

/// <summary>
/// 地形オブジェクト
/// </summary>
class BaseGround : public StageObject{

protected:
	/// <summary>
	/// マップチップの座標データ
	/// </summary>
	std::vector<std::vector<int>> ground_data;

public:

	/// <inheritdoc />
	virtual void Update(float DeltaTime) override;
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual void Draw(const Vector2D& screen_offset) override;

	/// <summary>
	/// 座標データをセット
	/// </summary>
	/// <param name="new_ground_data">座標データ</param>
	virtual void SetGroundData(std::vector<std::vector<int>> new_ground_data) { ground_data = new_ground_data; }

};