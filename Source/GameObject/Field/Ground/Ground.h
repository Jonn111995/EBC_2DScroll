#pragma once
#include "BaseGround.h"

/// <summary>
/// �n��
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
	/// �n�ʂ̃O���t�B�b�N�n���h��
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