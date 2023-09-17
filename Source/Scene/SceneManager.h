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
	/**
	 * 初期化
	 */
	void Initialize();

	/**
	 * 更新
	 * @param delta_seconds	前フレームとの差分時間(s)
	 */
	void Update(float delta_seconds);

	/**
	 * 解放
	 */
	void Finalize();

private:
	/**
	 * 描画
	 */
	void Draw();

	/**
	 * シーンの遷移
	 * @param	new_scene_type	遷移したいシーン
	 */
	void ChangeScene(SceneType new_scene_type);

	/**
	 * シーンの生成
	 * @param	new_scene_type	生成する新しいシーン
	 * @return	生成したシーン
	 */
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