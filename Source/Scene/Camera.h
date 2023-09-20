#pragma once
#include "../Source/Utility/Vector2D.h"

/// <summary>
/// カメラ
/// スクロール処理に必要なオフセットを管理する
/// </summary>
class Camera {
public :
	Camera();
	virtual ~Camera();
public:
	/// <summary>
	/// オフセットの更新
	/// </summary>
	/// <param name="chase_target_position">画面の中心に捉えるオブジェクト</param>
	void UpdateCamera(const Vector2D& chase_target_position);

	/// <summary>
	/// カメラの座標を取得
	/// </summary>
	/// <returns>カメラ座標</returns>
	Vector2D GetCameraPosition() const { return camera_position; }

	/// <summary>
	/// オフセットを取得
	/// 描画する範囲の左上原点。
	/// カメラから画面サイズの半分を引くことで求める
	/// </summary>
	/// <returns>オフセット</returns>
	Vector2D GetScreenOffset() const;

	/// <summary>
	/// ワールド座標のXY軸の大きさをセット
	/// </summary>
	/// <param name="size">ワールド座標のサイズ</param>
	void SetOverallMapWidth(const Vector2D size) { overall_map_size = size; }

private:
	/// <summary>
	/// カメラ座標
	/// </summary>
	Vector2D camera_position;

	/// <summary>
	/// ワールド座標のサイズ
	/// </summary>
	Vector2D overall_map_size;
};