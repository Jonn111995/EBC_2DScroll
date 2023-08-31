#pragma once
#include "../GameObject.h"
#include <vector>
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"

class Character;
class StageObject;
class CSVFile;

/// <summary>
/// マップ情報の管理
/// </summary>
class Field : public GameObject {

private:

struct GroundObjectInfo{

	Vector2D left_up_pos;
	BoxCollisionParams collision;
};

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
	/// 移動先が移動可能か確認
	/// </summary>
	/// <param name="move_to_position">移動先</param>
	/// <param name="collision">移動するオブジェクトのコリジョン</param>
	/// <returns>true: 移動可能 false: 移動不可</returns>
	bool CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision);

	/// <summary>
	/// 移動先が立てるか確認
	/// </summary>
	/// <param name="move_to_position">移動先</param>
	/// <param name="collision">移動するオブジェクトのコリジョン</param>
	/// <returns>true: 立てる false: 立てない</returns>
	bool CheckStande(Vector2D& move_to_position, const BoxCollisionParams& collision);

public:
	
	/// <inheritdoc />
	void Update(float DeltaTime) override;
	/// <inheritdoc />
	void Initialize() override;
	/// <inheritdoc />
	void Draw(const Vector2D& screen_offset) override;

private:

	/// <summary>
	/// 地面のグラフィックハンドル
	/// </summary>
	int ground_graphic_handle[8];
	int ground_graphic_handle_upper[3];
	int ground_graphic_handle_middle[3];
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
	/// キャラクターの位置関係
	/// </summary>
	std::vector<std::vector<Character*>> character_map;
	/// <summary>
	/// アイテムの位置関係
	/// </summary>
	std::vector<std::vector<StageObject*>> item_map;
	/// <summary>
	/// マップに配置されているオブジェクト
	/// </summary>
	std::vector<StageObject*>  StageObjectList;
private:
	/// <summary>
	/// マップを描画する
	/// </summary>
	void DrawMap();

	/// <summary>
	/// 地面のグラフィックを取得。
	/// </summary>
	int GetGroundGraphic(const int x, const int y);
	/// <summary>
	/// 地面データを読み込む
	/// </summary>
	/// <returns>作成する地面の座標</returns>
	std::vector<Vector2D> ReadGroundData();
	
	/// <summary>
	/// 地面データからオブジェクトを作成する。
	/// </summary>
	/// <param name="left_pos_ground_data">作成する地面オブジェクトの左上座標</param>
	/// <returns></returns>
	void CreateGround(std::vector<Vector2D>& left_pos_ground_data);

	/// <summary>
	/// 壁データを読み込む
	/// </summary>
	/// <returns>作成する地面の座標</returns>
	std::vector<GroundObjectInfo> ReadWallData();

	/// <summary>
	/// 壁データからオブジェクトを作成する
	/// </summary>
	/// <param name="left_pos_ground_data">作成する壁オブジェクトの左上座標</param>
	/// <returns></returns>
	void CreateWall(std::vector<GroundObjectInfo>& left_pos_wall_data);
	/// <summary>
	/// Boxオブジェクトを作成する
	/// </summary>
	void CreateBox();
	
	/// <summary>
	/// ステージに配置されたオブジェクトを追加
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(Character*);
};

