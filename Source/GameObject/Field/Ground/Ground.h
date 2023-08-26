#pragma once
#include "BaseGround.h"

/// <summary>
/// 地面
/// </summary>
class Ground : public BaseGround {

	enum EGroundLine {

		kFirst,
		kSecond,
		kThird,
		kAfterLine
	};

private:
	/// <summary>
	/// 地面のグラフィックハンドル
	/// </summary>
	int ground_graphic_handle[8];

public:
	// <inheritdoc />
	virtual void Update(float DeltaTime) override;
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual void Draw(const Vector2D& screen_offset) override;
};