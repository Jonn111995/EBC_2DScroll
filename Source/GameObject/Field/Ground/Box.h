#pragma once
#include "BaseGround.h"

class Box : public BaseGround {

/// <summary>
/// ボックスタイプ
/// </summary>
enum EBoxType {
	//通常
	kNormal,
	//ギミックあり
	kGimmick,
};

private:
	/// <summary>
	/// ボックスのグラフィックハンドル
	/// </summary>
	int box_graphic_handle;

	/// <summary>
	/// ギミックのあるボックスのグラフィックハンドル
	/// </summary>
	int gimmick_box_graphic_handle[7];

	/// <summary>
	/// ボックスのタイプ
	/// </summary>
	EBoxType box_type;

public:
	/// <inheritdoc />
	virtual void Update(float DeltaTime) override;
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual void Draw(const Vector2D& screen_offset) override;

	void SetBoxType(EBoxType type) { box_type = type; }
};