#pragma once
#include "../Source/Utility/Vector2D.h"

/// <summary>
/// �J����
/// �X�N���[�������ɕK�v�ȃI�t�Z�b�g���Ǘ�����
/// </summary>
class Camera {
public :
	Camera();
	virtual ~Camera();
public:
	/// <summary>
	/// �I�t�Z�b�g�̍X�V
	/// </summary>
	/// <param name="chase_target_position">��ʂ̒��S�ɑ�����I�u�W�F�N�g</param>
	void UpdateCamera(const Vector2D& chase_target_position);

	/// <summary>
	/// �J�����̍��W���擾
	/// </summary>
	/// <returns>�J�������W</returns>
	Vector2D GetCameraPosition() const { return camera_position; }

	/// <summary>
	/// �I�t�Z�b�g���擾
	/// �`�悷��͈͂̍��㌴�_�B
	/// �J���������ʃT�C�Y�̔������������Ƃŋ��߂�
	/// </summary>
	/// <returns>�I�t�Z�b�g</returns>
	Vector2D GetScreenOffset() const;

	/// <summary>
	/// ���[���h���W��XY���̑傫�����Z�b�g
	/// </summary>
	/// <param name="size">���[���h���W�̃T�C�Y</param>
	void SetOverallMapWidth(const Vector2D size) { overall_map_size = size; }

private:
	/// <summary>
	/// �J�������W
	/// </summary>
	Vector2D camera_position;

	/// <summary>
	/// ���[���h���W�̃T�C�Y
	/// </summary>
	Vector2D overall_map_size;
};