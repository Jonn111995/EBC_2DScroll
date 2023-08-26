#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"


/// <summary>
/// �X�e�[�W��ɒu����A�Ǘ������I�u�W�F�N�g
/// </summary>
class StageObject : public GameObject {

private:
	/// <summary>
	/// �ʒu
	/// </summary>
	Vector2D position;

protected:
	/// <summary>
	/// �R���W����
	/// </summary>
	BoxCollisionParams body_collision;

public:
	/// <inheritdoc/>
	virtual void Initialize() override{}
	/// <inheritdoc/>
	virtual void Finalize() override{}
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override {}
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override {}

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

	/// <summary>
	/// ���̃I�u�W�F�N�g�̃R���W������Ԃ�
	/// </summary>
	/// <returns>�R���W����</returns>
	BoxCollisionParams GetBodyCollision() const { return body_collision; }
	void SetBodyCollision(const BoxCollisionParams collision) { body_collision = collision; }

	/// <summary>
	/// �Փ˔��肪�N�������ꍇ�̏���
	/// </summary>
	/// <param name="hit_object">�Փ˂�������̃I�u�W�F�N�g</param>
	/// <param name="hit_collision">�Փ˂�������̃R���W����</param>
	virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision);
};

