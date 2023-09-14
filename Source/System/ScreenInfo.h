#pragma once
#include "../Utility/Vector2D.h"

/// <summary>
/// スクリーン情報を保持するシングルトン.
/// </summary>
class ScreenInfo {

private:

	/// <summary>
	/// Xの解像度
	/// </summary>
	int resolution_x;

	/// <summary>
	/// Yの解像度
	/// </summary>
	int resolution_y;

	/// <summary>
	/// 画面の中心のX座標
	/// </summary>
	int display_center_x;

	/// <summary>
	/// 画面の中心のY座標
	/// </summary>
	int display_center_y;

	/// <summary>
	/// マップのXサイズ
	/// </summary>
	int map_x_size;

	/// <summary>
	/// マップのYサイズ
	/// </summary>
	int map_y_size;

	/// <summary>
	/// マップの左上のX座標
	/// </summary>
	float map_left_x;

	/// <summary>
	/// マップの左のY座標
	/// </summary>
	float map_left_y;

private:
	ScreenInfo();

public:
	/// <summary>
	/// シングルトンインスタンス
	/// </summary>
	static ScreenInfo* screen_info;

	~ScreenInfo();

	/// <summary>
	/// インスタンスを作成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static ScreenInfo* GetInstance();

	/// <summary>
	/// インスタンスを削除する
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	//Xの解像度を取得する
	int GetResolutionX();

	//Yの解像度を取得する。
	int GetResolutionY();

	//Xの中心座標を取得する。
	int GetCenterX();

	//Yの中心座標を取得する。
	int GetCenterY();

	//マップサイズを設定する。
	void SetMapSize(int x, int y);
	Vector2D GetMapSize() const;

	//左のX座標を取得する。
	float GetLeftX();

	//左のY座標を取得する。
	float GetLeftY();
};