#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include <vector>

/// <summary>
/// �n�`�I�u�W�F�N�g
/// </summary>
class BaseGround : public StageObject{

protected:
	/// <summary>
	/// �}�b�v�`�b�v�̍��W�f�[�^
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
	/// ���W�f�[�^���Z�b�g
	/// </summary>
	/// <param name="new_ground_data">���W�f�[�^</param>
	virtual void SetGroundData(std::vector<std::vector<int>> new_ground_data) { ground_data = new_ground_data; }

};