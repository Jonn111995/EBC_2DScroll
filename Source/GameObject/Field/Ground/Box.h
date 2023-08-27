#pragma once
#include "BaseGround.h"

class Box : public BaseGround {

enum EBoxType {

	kNormal,
	kGimmick,
};

private:
	/// <summary>
	/// ボックスのグラフィックハンドル
	/// </summary>
	int box_graphic_handle;

	int gimmick_box_graphic_handle[7];

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