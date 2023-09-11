#pragma once

#include "../SceneBase.h"
#include "../Source/Scene/TitleScene/Interface/TitleSceneInterface.h"

class Field;
class Player;
class GameState;
class GameStateUI;
class HpUI;

enum class EPlaySceneState : unsigned short{

	kPRE_START,			//準備中
	kSTART_UI,			//スタートUI表示フェーズ
	kWAIT_END_START_UI,		//UI表示終了待機フェーズ
	kPLAYING,			//プレイ中
	kFINISH_UI,			//フィニッシュUI表示
	kWAIT_END_FINISH_UI,//フィニッシュUI表示終了待機フェーズ
	kPAUSE,				//ポーズフェーズ
	kFINISH,				//終了フェーズ
	kChangeLevel,		//レベル切り替えフェーズ
	kFinished,			//終了済みフェーズ
};

/**
 * サンプルシーン
 * サンプル用に簡易的に実装
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
	/// マップデータの管理
	/// </summary>
	Field* field;

	/// <summary>
	/// プレイヤー
	/// </summary>
	Player* player;

	/// <summary>
	/// ゲームの状態を管理
	/// </summary>
	GameState* game_state;

	/// <summary>
	/// ゲーム状態UI
	/// </summary>
	GameStateUI* game_state_ui;

	/// <summary>
	/// キャラクターのHpUI
	/// </summary>
	HpUI* hp_ui;
};