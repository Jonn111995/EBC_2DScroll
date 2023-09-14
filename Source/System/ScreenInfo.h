#pragma once
#include "../Utility/Vector2D.h"

/// <summary>
/// �X�N���[������ێ�����V���O���g��.
/// </summary>
class ScreenInfo {

private:

	/// <summary>
	/// X�̉𑜓x
	/// </summary>
	int resolution_x;

	/// <summary>
	/// Y�̉𑜓x
	/// </summary>
	int resolution_y;

	/// <summary>
	/// ��ʂ̒��S��X���W
	/// </summary>
	int display_center_x;

	/// <summary>
	/// ��ʂ̒��S��Y���W
	/// </summary>
	int display_center_y;

	/// <summary>
	/// �}�b�v��X�T�C�Y
	/// </summary>
	int map_x_size;

	/// <summary>
	/// �}�b�v��Y�T�C�Y
	/// </summary>
	int map_y_size;

	/// <summary>
	/// �}�b�v�̍����X���W
	/// </summary>
	float map_left_x;

	/// <summary>
	/// �}�b�v�̍���Y���W
	/// </summary>
	float map_left_y;

private:
	ScreenInfo();

public:
	/// <summary>
	/// �V���O���g���C���X�^���X
	/// </summary>
	static ScreenInfo* screen_info;

	~ScreenInfo();

	/// <summary>
	/// �C���X�^���X���쐬����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X���擾����
	/// </summary>
	/// <returns></returns>
	static ScreenInfo* GetInstance();

	/// <summary>
	/// �C���X�^���X���폜����
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	//X�̉𑜓x���擾����
	int GetResolutionX();

	//Y�̉𑜓x���擾����B
	int GetResolutionY();

	//X�̒��S���W���擾����B
	int GetCenterX();

	//Y�̒��S���W���擾����B
	int GetCenterY();

	//�}�b�v�T�C�Y��ݒ肷��B
	void SetMapSize(int x, int y);
	Vector2D GetMapSize() const;

	//����X���W���擾����B
	float GetLeftX();

	//����Y���W���擾����B
	float GetLeftY();
};