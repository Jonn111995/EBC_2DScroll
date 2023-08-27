#pragma once
#include "Vector2D.h"
#include "ColliiosnObjectType.h"
#include "CollisionType.h"

/// <summary>
/// �R���W����
/// </summary>
struct BoxCollisionParams {

public:
	/// <summary>
	/// �R���W�����̒��S���W
	/// </summary>
	Vector2D center_position;

	/// <summary>
	/// �R���W�����̍�����W
	/// </summary>
	Vector2D left_up_position;

	/// <summary>
	/// �I�u�W�F�N�g�^�C�v
	/// </summary>
	CollisionObjectType object_type;

	/// <summary>
	/// �q�b�g�����I�u�W�F�N�g�̃^�C�v
	/// </summary>
	unsigned int hit_object_types;

	/// <summary>
	/// �R���W�����̃Z���^�[����͈̔́H
	/// </summary>
	Vector2D box_extent;

	/// <summary>
	/// �R���W�����̃^�C�v
	/// </summary>
	CollisionType collision_type;

public:
	/// <summary>
	/// �q�b�g�����I�u�W�F�N�g�Ƃ̃R���W�����`�F�b�N
	/// </summary>
	/// <param name="target">�q�b�g�����I�u�W�F�N�g�̃I�u�W�F�N�g�^�C�v</param>
	/// <returns></returns>
	bool IsHitCheckTarget(CollisionObjectType target);
};

