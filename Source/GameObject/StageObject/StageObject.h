#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"

/// <summary>
/// �X�e�[�W��ɒu����A�Ǘ������I�u�W�F�N�g
/// </summary>
class StageObject : public GameObject {

private:
	// �ʒu
	Vector2D position;

public:
	virtual void Update(float delta_seconds) {}
	virtual void Draw(const Vector2D& screen_offset) {}

public:
	StageObject();
	virtual ~StageObject();
	/**
	 * Position�̎擾
	 * @return	position
	 */
	Vector2D GetPosition() const { return position; }

	/**
	 * Position�̃Z�b�g
	 * @param	new_position	�Z�b�g����Position
	 */
	void SetPosition(const Vector2D& new_position);
};

