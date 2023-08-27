#pragma once
#include "../GameObject.h"
#include <vector>
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"

class Character;
class StageObject;
class CSVFile;

/// <summary>
/// �}�b�v���̊Ǘ�
/// </summary>
class Field : public GameObject {

private:
struct GroundObjectInfo{

	Vector2D left_up_pos;
	BoxCollisionParams collision;

};

public:
	Field();
	virtual ~Field();

	/// <summary>
	/// �}�b�v���̏�����
	/// </summary>
	/// <param name="map_file_name">�ǂݍ��ރ}�b�v�f�[�^�t�@�C��</param>
	/// <returns>true: ���������� false:�@���������s</returns>
	bool InitializeField(const char* map_file_name);

	bool CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision);
	bool CheckStande(Vector2D& move_to_position, const BoxCollisionParams& collision);

public:
	
	/// <inheritdoc />
	void Update(float DeltaTime) override;
	/// <inheritdoc />
	void Initialize() override;
	/// <inheritdoc />
	void Draw(const Vector2D& screen_offset) override;
private:

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
	/// �n�ʃf�[�^��ǂݍ���
	/// </summary>
	/// <returns>�쐬����n�ʂ̍��W</returns>
	std::vector<Vector2D> ReadGroundData();
	
	/// <summary>
	/// �n�ʃf�[�^����I�u�W�F�N�g���쐬����B
	/// </summary>
	/// <param name="left_pos_ground_data">�쐬����n�ʃI�u�W�F�N�g�̍�����W</param>
	/// <returns></returns>
	void CreateGround(std::vector<Vector2D>& left_pos_ground_data);

	/// <summary>
	/// �ǃf�[�^��ǂݍ���
	/// </summary>
	/// <returns>�쐬����n�ʂ̍��W</returns>
	std::vector<GroundObjectInfo> ReadWallData();

	/// <summary>
	/// �ǃf�[�^����I�u�W�F�N�g���쐬����B
	/// </summary>
	/// <param name="left_pos_ground_data">�쐬����ǃI�u�W�F�N�g�̍�����W</param>
	/// <returns></returns>
	void CreateWall(std::vector<GroundObjectInfo>& left_pos_wall_data);
	void CreateBox();
	
	/// <summary>
	/// �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(Character*);
};

