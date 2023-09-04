#pragma once
#include "../Source/GameObject/GameObject.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"


/// <summary>
/// �X�e�[�W��ɒu����A�Ǘ������I�u�W�F�N�g
/// </summary>
class StageObject : public GameObject {

public:
	StageObject();
	virtual ~StageObject();

	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;
	/// <summary>
	/// �Փ˔��肪�N�������ꍇ�̏���
	/// </summary>
	/// <param name="hit_object">�Փ˂�������̃I�u�W�F�N�g</param>
	/// <param name="hit_collision">�Փ˂�������̃R���W����</param>
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision);

public:	
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���݂̍��W</returns>
	Vector2D GetPosition() const { return position; }

	/// <summary>
	/// ���W���Z�b�g
	/// </summary>
	/// <param name="new_position">�X�V���ꂽ���W</param>
	void SetPosition(const Vector2D& new_position);

	/// <summary>
	/// ���̃I�u�W�F�N�g�̃R���W������Ԃ�
	/// </summary>
	/// <returns>�R���W����</returns>
	BoxCollisionParams GetBodyCollision() const { return body_collision; }
	
	/// <summary>
	/// �R���W�������Z�b�g����
	/// </summary>
	/// <param name="collision"></param>
	void SetBodyCollision(const BoxCollisionParams collision) { body_collision = collision; }

	/// <summary>
	/// ���S���W��BoxCollisionParams�ɃZ�b�g����
	/// </summary>
	/// <param name="new_position"></param>
	void SetCenterPosition(const Vector2D& new_position);

protected:
	/// <summary>
	/// �R���W����
	/// </summary>
	BoxCollisionParams body_collision;

private:
	/// <summary>
	/// �ʒu
	/// </summary>
	Vector2D position;
};

