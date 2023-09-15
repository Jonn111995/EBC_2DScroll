#pragma once
#include <vector>
#include "../GameObject.h"
#include "../Source/Utility/Vector2D.h"

class Character;

/// <summary>
/// リスポーンマネージャのステート
/// </summary>
enum class ERespawnManagerState {
	kOBSERVE,			//チェックポイント監視中
	kINFORM_PASS_POINT	//通過通知中
};

/// <summary>
/// リスポーン処理を管理
/// </summary>
class RespawnManager : public GameObject{
public:
	RespawnManager();
	virtual ~RespawnManager();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta_seconds">前フレームとの差分時間(s)</param>
	virtual void Update(float delta_seconds);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset);

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Finalize();
public:
	/// <summary>
	/// チェックポイントリストをセット
	/// </summary>
	/// <param name="check_point_list">チェックポイントリスト</param>
	void SetCheckPointList(std::vector<Vector2D> check_point_list);

	/// <summary>
	/// チェックポイントを通過したかどうかを監視するオブジェクトをセット
	/// </summary>
	/// <param name="observe_object">監視対象のオブジェクト</param>
	void SetObserveObject(Character& observe_object) { this->observe_object = &observe_object; }

	/// <summary>
	/// キャラクターのリスポーンを実行
	/// </summary>
	void RespawnObject();
private:

	ERespawnManagerState now_state;
	/// <summary>
	/// 追跡するオブジェクト
	/// </summary>
	Character* observe_object;

	/// <summary>
	/// 現在のチェックポイント
	/// </summary>
	Vector2D now_check_point;

	/// <summary>
	/// 次のチェックポイント
	/// </summary>
	Vector2D next_check_point;

	/// <summary>
	/// チェックポイントの場所一覧
	/// </summary>
	std::vector<Vector2D> check_point_list;

	/// <summary>
	/// チェックポイントを通過したか？
	/// </summary>
	bool is_pass_check_point;

	/// <summary>
	/// 通知カウント時間
	/// </summary>
	float inform_count_time;

	float inform_movement;
	float initial_velocity = -30;
	float plus = 1.f;

};
