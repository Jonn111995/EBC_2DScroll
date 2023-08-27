#pragma once
#include "BaseGround.h"
#include <vector>

class Wall : public BaseGround {

private:
	/// <summary>
	/// �ǂ̃O���t�B�b�N�n���h��
	/// </summary>
	int wall_graphic_handle[3];

	std::vector<Wall*> broken_wall;

public:
	/// <inheritdoc />
	virtual void Update(float DeltaTime) override;
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual void Draw(const Vector2D& screen_offset) override;
};