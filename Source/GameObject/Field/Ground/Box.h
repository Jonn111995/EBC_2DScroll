#pragma once
#include "BaseGround.h"

class Box : public BaseGround {

/// <summary>
/// �{�b�N�X�^�C�v
/// </summary>
enum EBoxType {
	//�ʏ�
	kNormal,
	//�M�~�b�N����
	kGimmick,
};

private:
	/// <summary>
	/// �{�b�N�X�̃O���t�B�b�N�n���h��
	/// </summary>
	int box_graphic_handle;

	/// <summary>
	/// �M�~�b�N�̂���{�b�N�X�̃O���t�B�b�N�n���h��
	/// </summary>
	int gimmick_box_graphic_handle[7];

	/// <summary>
	/// �{�b�N�X�̃^�C�v
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