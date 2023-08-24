#pragma once
#include "../GameObject.h"
#include <vector>

class Character;
class StageObject;
class CSVFile;

/// <summary>
/// �}�b�v���̊Ǘ�.
/// </summary>
class Field : public GameObject {

public:
	Field();
	virtual ~Field();

	/// <summary>
	/// �}�b�v���̏�����
	/// </summary>
	/// <param name="map_file_name">�ǂݍ��ރ}�b�v�f�[�^�t�@�C��</param>
	/// <returns>true: ���������� false:�@���������s</returns>
	bool InitializeField(const char* map_file_name);

public:
	
	/// <inheritdoc />
	void Update(float DeltaTime) override;
	/// <inheritdoc />
	void Initialize() override;
	/// <inheritdoc />
	void Draw(const Vector2D& screen_offset) override;
private:

	/// <summary>
	/// �n�ʂ̃O���t�B�b�N�n���h��
	/// </summary>
	int ground_graphic_handle[8];

	/// <summary>
	/// �ǂ̃O���t�B�b�N�n���h��
	/// </summary>
	int wall_graphic_handle;

	/// <summary>
	/// �H�{�b�N�X�̃O���t�B�b�N�n���h��
	/// </summary>
	int box_graphic_handle;

	/// <summary>
	/// CSV�t�@�C���ǂݍ��݋@�\�C���X�^���X
	/// </summary>
	CSVFile* csv_file_reader;

	/// <summary>
	/// �}�b�v�f�[�^
	/// </summary>
	std::vector<std::vector<int>> map_data;
	/// <summary>
	/// �L�����N�^�[�̈ʒu�֌W
	/// </summary>
	std::vector<std::vector<Character*>> character_map;
	/// <summary>
	/// �A�C�e���̈ʒu�֌W
	/// </summary>
	std::vector<std::vector<StageObject*>> item_map;
	/// <summary>
	/// �}�b�v�ɔz�u����Ă���I�u�W�F�N�g
	/// </summary>
	std::vector<StageObject*>  StageObjectList;
	
	/// <summary>
	/// �n�ʂ̕`����s��
	/// </summary>
	void DrawGroundSet();
	/// <summary>
	/// �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(Character*);
};

