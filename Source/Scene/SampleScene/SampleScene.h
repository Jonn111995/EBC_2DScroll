#pragma once

#include "../SceneBase.h"
#include "../Source/Scene/TitleScene/Interface/TitleSceneInterface.h"

class Field;
class Player;
class GameState;
class GameStateUI;
class HpUI;

enum class EPlaySceneState : unsigned short{

	kPRE_START,			//������
	kSTART_UI,			//�X�^�[�gUI�\���t�F�[�Y
	kWAIT_END_START_UI,		//UI�\���I���ҋ@�t�F�[�Y
	kPLAYING,			//�v���C��
	kFINISH_UI,			//�t�B�j�b�V��UI�\��
	kWAIT_END_FINISH_UI,//�t�B�j�b�V��UI�\���I���ҋ@�t�F�[�Y
	kPAUSE,				//�|�[�Y�t�F�[�Y
	kFINISH,				//�I���t�F�[�Y
	kChangeLevel,		//���x���؂�ւ��t�F�[�Y
	kFinished,			//�I���ς݃t�F�[�Y
};

/**
 * �T���v���V�[��
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class SampleScene : public SceneBase, public TitleSceneInterface
{
public:
	SampleScene();
	virtual ~SampleScene() {}

public:
	//~ Begin CSceneBase interface
	virtual void Initialize() override;	
	virtual void Finalize() override;
	virtual SceneType Update(float delta_seconds) override;
	virtual void Draw() override;
	virtual SceneType GetSceneType() const override { return SceneType::SAMPLE_SCENE; }
	bool CheckCanMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	bool CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) override;
	virtual bool CheckCanMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	virtual bool CheckCanMoveToY(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	virtual void AddWeapon(BaseWeapon& weapon) override;
	virtual void RemoveWeapon(BaseWeapon* weapon) override;
	virtual void GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) override;
	virtual void UpdateHpUI(const int now_hp) override;



	virtual bool SerchPlayer(Enemy* enemy) override;
	virtual void UpdateTimeUI(int remain_time) override;
	virtual void TimeOver() override;
	//~ End SceneBase interface

private:

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
};