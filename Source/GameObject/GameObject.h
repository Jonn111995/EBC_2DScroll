#pragma once

class Vector2D;

enum class EGameObjectState : unsigned short {
	kPRE_START,	//初期フェーズ
	kPLAYING,	//処理フェーズ
	kPAUSE,		//ポーズフェーズ
	kEND,		//終了フェーズ
};

enum class EActivation : unsigned short {
	kACTIVE,
	kNONE_ACTIVE
};

/// <summary>
/// ゲーム内に表示されるオブジェクトの基底クラス
/// </summary>
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

	/// <summary>
	/// 描画順の取得
	/// </summary>
	/// <returns>描画順</returns>
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/// <summary>
	/// 描画順のセット
	/// </summary>
	/// <param name="new_priority">セットする描画順</param>
	void SetDrawSortPriority(const int new_priority);

	/// <summary>
	/// 処理状態をPlayに変更
	/// </summary>
	void SetPlaying() { game_object_state = EGameObjectState::kPLAYING; }
	/// <summary>
	/// 処理状態をポーズに変更
	/// </summary>
	void SetPause() { game_object_state = EGameObjectState::kPAUSE; }
	/// <summary>
	/// 処理状態を終了状態に変更
	/// </summary>
	void SetEnd() { game_object_state = EGameObjectState::kEND; }

	/// <summary>
	/// オブジェクト
	/// </summary>
	/// <returns></returns>
	EGameObjectState GetGameObjectState() { return game_object_state; }

	/// <summary>
	/// 活動状態に変更
	/// </summary>
	void OnActive() { active_state = EActivation::kACTIVE; }
	/// <summary>
	/// 休止状態に変更
	/// </summary>
	void OffActive() { active_state = EActivation::kNONE_ACTIVE; }

protected:
	/// <summary>
	/// 描画順。数値が小さい順から描画を行う
	/// </summary>
	int draw_sort_priority;

	/// <summary>
	/// ステージオブジェクトの処理ステート
	/// </summary>
	EGameObjectState game_object_state;

	/// <summary>
	/// このオブジェクトが活動中かどうかを表すステート
	/// </summary>
	EActivation active_state;
};