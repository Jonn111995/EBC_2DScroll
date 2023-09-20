#pragma once

// シーンタイプの前方宣言
enum class SceneType : unsigned short;

/// <summary>
/// 各シーンを管理するクラス
/// シーンの生成 / 破棄や変更を行う 
/// </summary>
class SceneManager {
public:
	SceneManager();
	virtual ~SceneManager();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// SceneのUpdateを呼ぶ
	/// </summary>
	/// <param name="delta_time">前フレームとの差分時間(s)</param>
	void Update(const float delta_time);

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();

private:
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンの遷移
	/// </summary>
	/// <param name="new_scene_type">遷移したいシーン</param>
	void ChangeScene(SceneType new_scene_type);

	/// <summary>
	/// シーンの生成
	/// </summary>
	/// <param name="new_scene_type">生成する新しいシーン</param>
	/// <returns>生成したシーン</returns>
	class SceneBase* CreateScene(SceneType new_scene_type);

	/// <summary>
	/// 前回のステージでのデータを次のステージに引き継ぐ
	/// スコア、残機数、ステージ名、次のステージIDを引き継ぐ
	/// </summary>
	/// <param name="pre_scene">前回のシーン</param>
	/// <param name="new_scene">次のシーン</param>
	void InheritPreSceneData(const SceneBase& pre_scene, SceneBase& new_scene);

private:
	/// <summary>
	/// 現在のシーン
	/// </summary>
	class SceneBase* current_scene;
};