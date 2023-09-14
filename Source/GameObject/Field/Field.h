#pragma once
#include "../GameObject.h"
#include <vector>
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"
#include "EMapChipType.h"

class Character;
class StageObject;
class CSVFile;
class RespawnManager;

/// <summary>
/// �}�b�v���̊Ǘ�
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

	/// <summary>
	/// �L�����N�^�[�̏����ʒu���������A�Z�b�g����
	/// </summary>
	/// <returns></returns>
	bool InitializeStageObjectPosition();

	/// <summary>
	/// X�����ֈړ��o���邩�m�F
	/// </summary>
	/// <param name="now_position">���݂̍��W</param>
	/// <param name="move_amount">�ړ��\���</param>
	/// <param name="collision">�R���W����</param>
	/// <returns>true: �ړ��\ false: �ړ��s��</returns>
	bool CheckMoveToX(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision);

	/// <summary>
	/// Y�����ֈړ��o���邩�m�F
	/// </summary>
	/// <param name="now_position">���݂̍��W</param>
	/// <param name="move_amount">�ړ��\���</param>
	/// <param name="collision">�R���W����</param>
	/// <returns></returns>
	bool CheckMoveToY(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision);

	/// <summary>
	/// �n�`�}�b�v�`�b�v�ƏՓ˂��Ă��邩�m�F
	/// </summary>
	/// <param name="opponent_check_position">�Փˑ���</param>
	/// <param name="oppnent_center"></param>
	/// <param name="collision"></param>
	/// <returns></returns>
	bool CheckHitGround(Vector2D& opponent_check_position, const Vector2D& oppnent_center, const BoxCollisionParams& collision);

	/// <summary>
	/// �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(StageObject& stage_object);
	/// <summary>
	/// �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g���폜
	/// </summary>
	/// <param name="stage_object"></param>
	void DeleteStageObject(StageObject* stage_object);

	/// <summary>
	/// �X�e�[�W�ɑ��݂���I�u�W�F�N�g���X�g���擾
	/// </summary>
	/// <returns>�X�e�[�W�I�u�W�F�N�g���X�g</returns>
	std::vector<StageObject*> GetStageObjectList() { return stage_object_list; }

	/// <summary>
	/// �`�F�b�N�|�C���g�̃��X�g���擾
	/// </summary>
	/// <returns>�`�F�b�N�|�C���g���X�g</returns>
	std::vector<Vector2D> GetCheckPointList();

public:
	
	/// <inheritdoc />
	void Update(float DeltaTime) override;
	/// <inheritdoc />
	void Initialize() override;
	/// <inheritdoc />
	virtual void Finalize();
	/// <inheritdoc />
	void Draw(const Vector2D& screen_offset) override;

private:

	/// <summary>
	/// �n�ʂ̍ŏ�w�̃O���t�B�b�N�n���h��
	/// </summary>
	int ground_graphic_handle_upper[3];
	/// <summary>
	/// �n�ʂ̒��ԑw�̃O���t�B�b�N�n���h��
	/// </summary>
	int ground_graphic_handle_middle[3];
	/// <summary>
	/// �n�ʂ̍ŉ��w�̃O���t�B�b�N�n���h��
	/// </summary>
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
	/// �}�b�v�ɔz�u����Ă���I�u�W�F�N�g
	/// </summary>
	std::vector<StageObject*>  stage_object_list;

	/// <summary>
	/// �L�����N�^�[�̃��X�g
	/// </summary>
	std::vector<std::vector<Character*>> character_map;

	/// <summary>
	/// �A�C�e���̈ʒu�֌W
	/// </summary>
	std::vector<std::vector<StageObject*>> item_map;

private:
	/// <summary>
	/// �}�b�v��`�悷��
	/// </summary>
	void DrawMap(const Vector2D& screen_offset);

	/// <summary>
	/// �n�ʂ̃O���t�B�b�N���擾�B
	/// </summary>
	int GetGroundGraphic(const int x, const int y);

	/// <summary>
	/// �����ʒu���Z�b�g����
	/// </summary>
	/// <param name="stage_obj"></param>
	/// <param name="chip_type"></param>
	void SetInitialPosition(StageObject& stage_obj, const MapChipType chip_type);
};

