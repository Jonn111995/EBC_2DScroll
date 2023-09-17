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

	kPRE_START,			//準備中
	kSTART_UI,			//スタートUI表示フェーズ
	kWAIT_END_START_UI,	//UI表示終了待機フェーズ
	kPLAYING,			//プレイ中
	kFINISH_UI,			//フィニッシュUI表示
	kWAIT_END_FINISH_UI,//フィニッシュUI表示終了待機フェーズ
	kPAUSE,				//ポーズフェーズ
	kFINISH,			//終了フェーズ
	kChangeLevel,		//レベル切り替えフェーズ
	kFinished,			//終了済みフェーズ
};

/// <summary>
///	プレイ画面
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
	/// X方向に衝突があるかチェック
	/// </summary>
	/// <param name="now_position">現在の座標</param>
	/// <param name="move_amount">移動量</param>
	/// <param name="collision">衝突判定を行うオブジェクトのコリジョン</param>
	/// <returns>true: 衝突している　false:衝突していない</returns>
	virtual bool CheckCanMoveToX(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	/// <summary>
	/// Y方向に衝突があるかチェック
	/// </summary>
	/// <param name="now_position">現在の座標</param>
	/// <param name="move_amount">移動量</param>
	/// <param name="collision">衝突判定を行うオブジェクトのコリジョン</param>
	/// <returns>true: 衝突している　false:衝突していない</returns>
	virtual bool CheckCanMoveToY(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	/// <summary>
	/// 武器オブジェクトを当たり判定チェック配列に追加する
	/// </summary>
	/// <param name="weapon">使用した武器</param>
	virtual void AddWeapon(BaseWeapon& weapon) override;

	/// <summary>
	/// 武器オブジェクトを当たり判定配列から削除する
	/// </summary>
	/// <param name="weapon">使用した武器</param>
	virtual void RemoveWeapon(BaseWeapon* weapon) override;

	/// <summary>
	/// HPを与えるイベント
	/// </summary>
	/// <param name="give_gamage_chara">ダメージを与えるオブジェクト</param>
	/// <param name="opponent_chara">ダメージを受けるオブジェクト</param>
	/// <param name="damage">ダメージ数</param>
	virtual void GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) override;

	/// <summary>
	/// HPUIの値を更新する
	/// </summary>
	/// <param name="now_hp">新しいHP</param>
	virtual void UpdateHpUI(const int now_hp) override;

	/// <summary>
	/// 残機数を更新する
	/// </summary>
	/// <param name="respawn_remain">新しい残機数</param>
	virtual void UpdateRespawnRemainUI(const int respawn_remain) override;

	/// <summary>
	/// スコアを更新する
	/// </summary>
	/// <param name="new_score">新しいスコア数</param>
	virtual void UpdateScoreUI(const int new_score) override;

	/// <summary>
	/// キャラの死亡イベント
	/// </summary>
	/// <param name="dead_object"></param>
	virtual void DeadEvent(StageObject* dead_object) override;

	/// <summary>
	/// プレイヤーを死亡状態に変える
	/// </summary>
	/// <param name="kill_target"></param>
	virtual void KillEvent(const StageObject* kill_target) override;

	/// <summary>
	/// リスポーン処理を実行
	/// </summary>
	/// <returns>リスポーン成功</returns>
	virtual bool ExecuteRespawn() override;

	/// <summary>
	/// UIの表示終了時イベント
	/// </summary>
	/// <param name="ui_component"></param>
	virtual void FInishUI(UIComponent* ui_component) override;

	/// <summary>
	/// ゲームクリア処理を実行
	/// </summary>
	virtual void GameClear() override;


	//~ Begin Item Interface

	/// <summary>
	/// GameStateのScoreを増加
	/// </summary>
	virtual void ScoreUp() override;
	/// <summary>
	/// プレイヤーを無敵状態に変更
	/// </summary>
	virtual void ChangeInvincible(const float invincible_time) override;
	/// <summary>
	/// アイテムを削除
	/// </summary>
	/// <param name="delete_object"></param>
	virtual void DestroyItem(StageObject& delete_object) override;

	//~ End Item Interface

	/// <summary>
	/// 通知を表示する場所を取得
	/// </summary>
	/// <param name="draw_postion"></param>
	virtual void GetDrawInformPositon(Vector2D& draw_postion) override;

	/// <summary>
	/// プレイヤーを敵が索敵する
	/// </summary>
	/// <param name="enemy">索敵する敵</param>
	/// <returns> true: 発見した false: 発見出来なかった</returns>
	virtual bool SerchPlayer(Enemy* enemy) override;

	/// <summary>
	/// 時間UIを更新する
	/// </summary>
	/// <param name="remain_time">残り時間</param>
	virtual void UpdateTimeUI(int remain_time) override;

	/// <summary>
	/// 制限時間オーバーのイベント
	/// </summary>
	virtual void TimeOver() override;
	virtual void FinishInvincibleState() override;

private:
	/// <summary>
	/// ステージオブジェクトを生成する
	/// </summary>
	void CreateStageObject();

	SceneType CheckExistNextStage();

private:
	/// <summary>
	/// ステージ背景
	/// </summary>
	int in_game_back_graphic;

	/// <summary>
	/// プレイ中のBGM
	/// </summary>
	int in_game_bgm;

	/// <summary>
	/// 無敵状態時のBGM
	/// </summary>
	int invincible_bgm;

	/// <summary>
	/// ゴールした時の効果音
	/// </summary>
	int goal_sound;

	/// <summary>
	/// Play Sceneのステート
	/// </summary>
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
	/// リスポーン関連の管理オブジェクト
	/// </summary>
	RespawnManager* respawn_manager;

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

	/// <summary>
	/// スタート時UI
	/// </summary>
	StartUI* start_ui;

	/// <summary>
	/// 終了時UI
	/// </summary>
	FinishUI* finish_ui;
};