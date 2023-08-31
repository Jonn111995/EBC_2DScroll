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

	/// <summary>
	/// �ړ��悪�ړ��\���m�F
	/// </summary>
	/// <param name="move_to_position">�ړ���</param>
	/// <param name="collision">�ړ�����I�u�W�F�N�g�̃R���W����</param>
	/// <returns>true: �ړ��\ false: �ړ��s��</returns>
	bool CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision);

	/// <summary>
	/// �ړ��悪���Ă邩�m�F
	/// </summary>
	/// <param name="move_to_position">�ړ���</param>
	/// <param name="collision">�ړ�����I�u�W�F�N�g�̃R���W����</param>
	/// <returns>true: ���Ă� false: ���ĂȂ�</returns>
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
	/// �n�ʂ̃O���t�B�b�N�n���h��
	/// </summary>
	int ground_graphic_handle[8];
	int ground_graphic_handle_upper[3];
	int ground_graphic_handle_middle[3];
	int ground_graphic_handle_bottom[3];



	/// <summary>
	/// �ǂ̃O���t�B�b�N�n���h��
	/// </summary>
	int wall_graphic_handle[3];

	/// <summary>
	/// �{�b�N�X�̃O���t�B�b�N�n���h��
	/// </summary>
	int box_graphic_handle;

	/// <summary>
	/// �M�~�b�N�̂���{�b�N�X�̃O���t�B�b�N�n���h��
	/// </summary>
	int gimmick_box_graphic_handle[7];

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
private:
	/// <summary>
	/// �}�b�v��`�悷��
	/// </summary>
	void DrawMap();

	/// <summary>
	/// �n�ʂ̃O���t�B�b�N���擾�B
	/// </summary>
	int GetGroundGraphic(const int x, const int y);
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
	/// �ǃf�[�^����I�u�W�F�N�g���쐬����
	/// </summary>
	/// <param name="left_pos_ground_data">�쐬����ǃI�u�W�F�N�g�̍�����W</param>
	/// <returns></returns>
	void CreateWall(std::vector<GroundObjectInfo>& left_pos_wall_data);
	/// <summary>
	/// Box�I�u�W�F�N�g���쐬����
	/// </summary>
	void CreateBox();
	
	/// <summary>
	/// �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(Character*);
};

