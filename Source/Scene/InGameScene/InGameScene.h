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
///	�v���C���
/// </summary>
class InGameScene : public SceneBase, public IInGameScene
{
public:
	InGameScene();
	virtual ~InGameScene();

public:
	//~ Begin SceneBase interface
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual SceneType Update(float delta_seconds) override;
	virtual void Draw() override;
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
	/// HP��^����C�x���g
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
	/// <param name="dead_object"></param>
	virtual void DeadEvent(StageObject* dead_object) override;

	/// <summary>
	/// �v���C���[�����S��Ԃɕς���
	/// </summary>
	/// <param name="kill_target"></param>
	virtual void KillEvent(const StageObject* kill_target) override;

	/// <summary>
	/// ���X�|�[�����������s
	/// </summary>
	/// <returns>���X�|�[������</returns>
	virtual bool ExecuteRespawn() override;

	/// <summary>
	/// UI�̕\���I�����C�x���g
	/// </summary>
	/// <param name="ui_component"></param>
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
	/// <param name="delete_object"></param>
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
	virtual void FinishInvincibleState() override;

private:
	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�𐶐�����
	/// </summary>
	void CreateStageObject();

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