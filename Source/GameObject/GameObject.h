#pragma once

class Vector2D;

/**
 * ゲーム内に表示されるオブジェクトの基底クラス
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta_seconds">前フレームとの差分時間(s)</param>
	virtual void Update(float delta_seconds) {}

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset) {}

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Finalize() {}

	/**
	 * シーンの取得
	 * @return owner_scene
	 */
	//class SceneBase* GetOwnerScene() const { return owner_scene; }

	/**
	 * シーンのセット
	 * @param	new_owner_scene	セットするPosition
	 */
	//void SetOwnerScene(class SceneBase* new_owner_scene);

	/**
	 * 描画順の取得
	 * @return	draw_sort_priority
	 */
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/**
	 * 描画順のセット
	 * @param	new_priority	セットする描画順
	 */
	void SetDrawSortPriority(const int new_priority);

private:
	// オーナーとなるシーン
	//class SceneBase* owner_scene;

	// 描画順。数値が小さい順から描画を行う
	int draw_sort_priority;
};