#pragma once
#include "../GameObject.h"
#include <vector>
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"
#include "EMapChipType.h"

class Character;
class StageObject;
class CSVFile;
class RespawnManager;

/// <summary>
/// マップ情報の管理
/// </summary>
class Field : public GameObject {

public:
	Field();
	virtual ~Field();

	/// <summary>
	/// マップ情報の初期化
	/// </summary>
	/// <param name="map_file_name">読み込むマップデータファイル</param>
	/// <returns>true: 初期化成功 false:　初期化失敗</returns>
	bool InitializeField(const char* map_file_name);

	/// <summary>
	/// キャラクターの初期位置を検索し、セットする
	/// </summary>
	/// <returns></returns>
	bool InitializeStageObjectPosition();

	/// <summary>
	/// X方向へ移動出来るか確認
	/// </summary>
	/// <param name="now_position">現在の座標</param>
	/// <param name="move_amount">移動予定量</param>
	/// <param name="collision">コリジョン</param>
	/// <returns>true: 移動可能 false: 移動不可</returns>
	bool CheckMoveToX(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision);

	/// <summary>
	/// Y方向へ移動出来るか確認
	/// </summary>
	/// <param name="now_position">現在の座標</param>
	/// <param name="move_amount">移動予定量</param>
	/// <param name="collision">コリジョン</param>
	/// <returns></returns>
	bool CheckMoveToY(const Vector2D& now_position, const Vector2D& move_amount, const BoxCollisionParams& collision);

	/// <summary>
	/// 地形マップチップと衝突しているか確認
	/// </summary>
	/// <param name="opponent_check_position">衝突相手</param>
	/// <param name="oppnent_center"></param>
	/// <param name="collision"></param>
	/// <returns></returns>
	bool CheckHitGround(Vector2D& opponent_check_position, const Vector2D& oppnent_center, const BoxCollisionParams& collision);

	/// <summary>
	/// ステージに配置されたオブジェクトを追加
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(StageObject& stage_object);
	/// <summary>
	/// ステージに配置されたオブジェクトを削除
	/// </summary>
	/// <param name="stage_object"></param>
	void DeleteStageObject(StageObject* stage_object);

	/// <summary>
	/// ステージに存在するオブジェクトリストを取得
	/// </summary>
	/// <returns>ステージオブジェクトリスト</returns>
	std::vector<StageObject*> GetStageObjectList() { return stage_object_list; }

	/// <summary>
	/// チェックポイントのリストを取得
	/// </summary>
	/// <returns>チェックポイントリスト</returns>
	std::vector<Vector2D> GetCheckPointList();

public:
	
	/// <inheritdoc />
	void Update(float DeltaTime) override;
	/// <inheritdoc />
	void Initialize() override;
	/// <inheritdoc />
	virtual void Finalize();
	/// <inheritdoc />
	void Draw(const Vector2D& screen_offset) override;

private:

	/// <summary>
	/// 地面の最上層のグラフィックハンドル
	/// </summary>
	int ground_graphic_handle_upper[3];
	/// <summary>
	/// 地面の中間層のグラフィックハンドル
	/// </summary>
	int ground_graphic_handle_middle[3];
	/// <summary>
	/// 地面の最下層のグラフィックハンドル
	/// </summary>
	int ground_graphic_handle_bottom[3];

	/// <summary>
	/// 壁のグラフィックハンドル
	/// </summary>
	int wall_graphic_handle[3];

	/// <summary>
	/// ボックスのグラフィックハンドル
	/// </summary>
	int box_graphic_handle;

	/// <summary>
	/// ギミックのあるボックスのグラフィックハンドル
	/// </summary>
	int gimmick_box_graphic_handle[7];

	/// <summary>
	/// CSVファイル読み込み機能インスタンス
	/// </summary>
	CSVFile* csv_file_reader;

	/// <summary>
	/// マップデータ
	/// </summary>
	std::vector<std::vector<int>> map_data;

	/// <summary>
	/// マップに配置されているオブジェクト
	/// </summary>
	std::vector<StageObject*>  stage_object_list;

	/// <summary>
	/// キャラクターのリスト
	/// </summary>
	std::vector<std::vector<Character*>> character_map;

	/// <summary>
	/// アイテムの位置関係
	/// </summary>
	std::vector<std::vector<StageObject*>> item_map;

private:
	/// <summary>
	/// マップを描画する
	/// </summary>
	void DrawMap(const Vector2D& screen_offset);

	/// <summary>
	/// 地面のグラフィックを取得。
	/// </summary>
	int GetGroundGraphic(const int x, const int y);

	/// <summary>
	/// 初期位置をセットする
	/// </summary>
	/// <param name="stage_obj"></param>
	/// <param name="chip_type"></param>
	void SetInitialPosition(StageObject& stage_obj, const MapChipType chip_type);
};

