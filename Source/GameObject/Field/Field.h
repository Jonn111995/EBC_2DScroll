#pragma once
#include "../GameObject.h"
#include <vector>

class Character;
class StageObject;
class CSVFile;

/// <summary>
/// マップ情報の管理.
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

	/// <summary>
	/// 壁のグラフィックハンドル
	/// </summary>
	int wall_graphic_handle;

	/// <summary>
	/// ？ボックスのグラフィックハンドル
	/// </summary>
	int box_graphic_handle;

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
	
	/// <summary>
	/// 地面の描画を行う
	/// </summary>
	void DrawGroundSet();
	/// <summary>
	/// ステージに配置されたオブジェクトを追加
	/// </summary>
	/// <param name=""></param>
	void AddStageObject(Character*);
};

