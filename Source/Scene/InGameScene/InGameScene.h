#pragma once

#include "../SceneBase.h"
#include "../InGameScene/Interface/IInGameScene.h"

class Field;
class Player;
class GameState;
class GameStateUI;
class HpUI;
class StartUI;
class FinishUI;
class RespawnManager;


enum class EPlaySceneState : unsigned short {

	kPRE_START,			//������
	kSTART_UI,			//�X�^�[�gUI�\���t�F�[�Y
	kWAIT_END_START_UI,	//UI�\���I���ҋ@�t�F�[�Y
	kPLAYING,			//�v���C��
	kFINISH_UI,			//�t�B�j�b�V��UI�\��
	kWAIT_END_FINISH_UI,//�t�B�j�b�V��UI�\���I���ҋ@�t�F�[�Y
	kPAUSE,				//�|�[�Y�t�F�[�Y
	kFINISH,			//�I���t�F�[�Y
	kChangeLevel,		//���x���؂�ւ��t�F�[�Y
	kFinished,			//�I���ς݃t�F�[�Y
};

/// <summary>
///	�Q�[���v���C���
/// </summary>
class InGameScene : public SceneBase, public IInGameScene {
public:
	InGameScene();
	virtual ~InGameScene();

public:
	//~ Begin SceneBase interface
	/// <inheritdoc />
	virtual void Initialize() override;
	/// <inheritdoc />
	virtual void Finalize() override;
	/// <inheritdoc />
	virtual SceneType Update(const float delta_time) override;
	/// <inheritdoc />
	virtual void Draw() override;
	/// <inheritdoc />
	virtual SceneType GetSceneType() const override { return SceneType::IN_GAME_SCENE; }
	//~ End SceneBase interface

	/// <summary>
	/// X�����ɏՓ˂����邩�`�F�b�N
	/// </summary>
	/// <param name="now_position">���݂̍��W</param>
	/// <param name="move_amount">�ړ���</param>
	/// <param name="collision">�Փ˔�����s���I�u�W�F�N�g�̃R���W����</param>
	/// <returns>true: �Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�</returns>
	virtual bool CheckCanMoveToX(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;

	/// <summary>
	/// Y�����ɏՓ˂����邩�`�F�b�N
	/// </summary>
	/// <param name="now_position">���݂̍��W</param>
	/// <param name="move_amount">�ړ���</param>
	/// <param name="collision">�Փ˔�����s���I�u�W�F�N�g�̃R���W����</param>
	/// <returns>true: �Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�</returns>
	virtual bool CheckCanMoveToY(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;

	/// <summary>
	/// ����I�u�W�F�N�g�𓖂��蔻��`�F�b�N�z��ɒǉ�����
	/// </summary>
	/// <param name="weapon">�g�p��������</param>
	virtual void AddWeapon(BaseWeapon& weapon) override;

	/// <summary>
	/// ����I�u�W�F�N�g�𓖂��蔻��z�񂩂�폜����
	/// </summary>
	/// <param name="weapon">�g�p��������</param>
	virtual void RemoveWeapon(BaseWeapon* weapon) override;

	/// <summary>
	/// �_���[�W��^����C�x���g
	/// �Փ˔��肪true�ɂȂ�ƁA�G�═�킩��Ă΂��
	/// </summary>
	/// <param name="give_gamage_chara">�_���[�W��^����I�u�W�F�N�g</param>
	/// <param name="opponent_chara">�_���[�W���󂯂�I�u�W�F�N�g</param>
	/// <param name="damage">�_���[�W��</param>
	virtual void GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) override;

	/// <summary>
	/// HPUI�̒l���X�V����
	/// </summary>
	/// <param name="now_hp">�V����HP</param>
	virtual void UpdateHpUI(const int now_hp) override;

	/// <summary>
	/// �c�@�����X�V����
	/// </summary>
	/// <param name="respawn_remain">�V�����c�@��</param>
	virtual void UpdateRespawnRemainUI(const int respawn_remain) override;

	/// <summary>
	/// �X�R�A���X�V����
	/// </summary>
	/// <param name="new_score">�V�����X�R�A��</param>
	virtual void UpdateScoreUI(const int new_score) override;

	/// <summary>
	/// �L�����̎��S�C�x���g
	/// </summary>
	/// <param name="dead_object">���S�����I�u�W�F�N�g</param>
	virtual void DeadEvent(StageObject* dead_object) override;

	/// <summary>
	/// �v���C���[�����S��Ԃɕς���
	/// </summary>
	/// <param name="kill_target">Kill����I�u�W�F�N�g</param>
	virtual void KillEvent(const StageObject* kill_target) override;

	/// <summary>
	/// ���X�|�[�����������s
	/// </summary>
	/// <returns>true: ���X�|�[������ false: ���X�|�[���s��</returns>
	virtual bool ExecuteRespawn() override;

	/// <summary>
	/// UI�\�����I��点�ėǂ����m�F
	/// </summary>
	/// <returns></returns>
	virtual bool CheckCanFinishUI() override;

	/// <summary>
	/// UI�̕\���I�����C�x���g
	/// </summary>
	/// <param name="ui_component">�C�x���g���Ăяo����UI</param>
	virtual void FInishUI(UIComponent* ui_component) override;

	/// <summary>
	/// �Q�[���N���A���������s
	/// </summary>
	virtual void GameClear() override;

	//~ Begin Item Interface
	/// <summary>
	/// GameState��Score�𑝉�
	/// </summary>
	virtual void ScoreUp() override;

	/// <summary>
	/// �v���C���[�𖳓G��ԂɕύX
	/// </summary>
	virtual void ChangeInvincible(const float invincible_time) override;

	/// <summary>
	/// �A�C�e�����폜
	/// </summary>
	/// <param name="delete_object">�폜����A�C�e��</param>
	virtual void DestroyItem(StageObject& delete_object) override;
	//~ End Item Interface

	/// <summary>
	/// �ʒm��\������ꏊ���擾
	/// </summary>
	/// <param name="draw_postion"></param>
	virtual void GetDrawInformPositon(Vector2D& draw_postion) override;

	/// <summary>
	/// �v���C���[��G�����G����
	/// </summary>
	/// <param name="enemy">���G����G</param>
	/// <returns> true: �������� false: �����o���Ȃ�����</returns>
	virtual bool SerchPlayer(Enemy* enemy) override;

	/// <summary>
	/// ����UI���X�V����
	/// </summary>
	/// <param name="remain_time">�c�莞��</param>
	virtual void UpdateTimeUI(int remain_time) override;

	/// <summary>
	/// �������ԃI�[�o�[�̃C�x���g
	/// </summary>
	virtual void TimeOver() override;

	/// <summary>
	/// ���G��Ԃ��I��������Ƃ�Scene�ɒʒm����
	/// </summary>
	virtual void FinishInvincibleState() override;

private:
	/// <summary>
	/// �Q�[���X�e�[�g�𐶐��A������
	/// </summary>
	/// <returns></returns>
	bool CreateGameState();

	/// <summary>
	/// �Q�[���X�e�[�W�𐶐��A������
	/// </summary>
	/// <returns></returns>
	bool CreateStage();

	/// <summary>
	/// UI�𐶐��A������
	/// </summary>
	/// <returns></returns>
	bool CreateUI();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�𐶐�����
	/// </summary>
	bool CreateStageObject();

	/// <summary>
	/// ���X�|�[���}�l�[�W���[�𐶐�����
	/// </summary>
	/// <returns></returns>
	bool CreateRespawnManager();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g���폜����
	/// </summary>
	/// <param name="stage_object_list"></param>
	void RemoveStageObject(std::vector<StageObject*> stage_object_list);

	/// <summary>
	/// �Փ˔�����s��
	/// </summary>
	/// <param name="stage_obj_list"></param>
	void CheckCollisionHit(std::vector<StageObject*> stage_obj_list);

	/// <summary>
	/// ���̃X�e�[�W��ID���m�F����
	/// ���̃X�e�[�W������΁ANEXT_SCENE, ������� BOOT_SCENE��Ԃ�
	/// </summary>
	/// <returns></returns>
	SceneType CheckExistNextStage();

private:
	/// <summary>
	/// �X�e�[�W�w�i
	/// </summary>
	int in_game_back_graphic;

	/// <summary>
	/// �v���C����BGM
	/// </summary>
	int in_game_bgm;

	/// <summary>
	/// ���G��Ԏ���BGM
	/// </summary>
	int invincible_bgm;

	/// <summary>
	/// �S�[���������̌��ʉ�
	/// </summary>
	int goal_sound;

	/// <summary>
	/// �Q�[���I�[�o�[���̌��ʉ�
	/// </summary>
	int game_over_bgm;

	/// <summary>
	/// Play Scene�̃X�e�[�g
	/// </summary>
	EPlaySceneState play_scene_state;

	/// <summary>
	/// �}�b�v�f�[�^�̊Ǘ�
	/// </summary>
	Field* field;

	/// <summary>
	/// �v���C���[
	/// </summary>
	Player* player;

	/// <summary>
	/// ���X�|�[���֘A�̊Ǘ��I�u�W�F�N�g
	/// </summary>
	RespawnManager* respawn_manager;

	/// <summary>
	/// �Q�[���̏�Ԃ��Ǘ�
	/// </summary>
	GameState* game_state;

	/// <summary>
	/// �Q�[�����UI
	/// </summary>
	GameStateUI* game_state_ui;

	/// <summary>
	/// �L�����N�^�[��HpUI
	/// </summary>
	HpUI* hp_ui;

	/// <summary>
	/// �X�^�[�g��UI
	/// </summary>
	StartUI* start_ui;

	/// <summary>
	/// �I����UI
	/// </summary>
	FinishUI* finish_ui;
};