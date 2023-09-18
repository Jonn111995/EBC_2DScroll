#include "Camera.h"
#include "../System/ScreenInfo.h"

Camera::Camera()
	: camera_position()
	, overall_map_size()
{
}

Camera::~Camera()
{
}

void Camera::UpdateCamera(const Vector2D& chase_target_position) {
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	if (screen_info != nullptr) {
		camera_position = chase_target_position;

		Vector2D map_size = screen_info->GetMapSize();

		//マップ全体の左端から、スクリーンサイズの半分を引いて、カメラが移動出来る左端の限界を求める。
		if (camera_position.x < screen_info->GetCenterX()) {
			camera_position.x = screen_info->GetCenterX();
		}

		//マップ全体の右端から、スクリーンサイズの半分を引いて、カメラが移動出来る右端の限界を求める。
		if (camera_position.x > (map_size.x - screen_info->GetCenterX())) {
			camera_position.x = map_size.x - screen_info->GetCenterX();
		}

		//マップ全体の左端から、スクリーンサイズの半分を引いて、カメラが移動出来る左端の限界を求める。
		if (camera_position.y < screen_info->GetCenterY()) {
			camera_position.y = screen_info->GetCenterY();
		}

		//マップ全体の右端から、スクリーンサイズの半分を引いて、カメラが移動出来る右端の限界を求める。
		if (camera_position.y > (map_size.y - screen_info->GetCenterY())) {
			camera_position.y = map_size.y - screen_info->GetCenterY();
		}
	}	
}

Vector2D Camera::GetScreenOffset() const {
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	if (screen_info != nullptr) {
		//スクリーンサイズの半分をカメラ座標から引いて左上原点を求める
		return camera_position  - Vector2D(screen_info->GetCenterX(), screen_info->GetCenterY());
	}
}
