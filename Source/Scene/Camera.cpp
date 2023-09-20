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

		//�}�b�v�S�̂̍��[����A�X�N���[���T�C�Y�̔����������āA�J�������ړ��o���鍶�[�̌��E�����߂�B
		if (camera_position.x < screen_info->GetCenterX()) {
			camera_position.x = screen_info->GetCenterX();
		}

		//�}�b�v�S�̂̉E�[����A�X�N���[���T�C�Y�̔����������āA�J�������ړ��o����E�[�̌��E�����߂�B
		if (camera_position.x > (map_size.x - screen_info->GetCenterX())) {
			camera_position.x = map_size.x - screen_info->GetCenterX();
		}

		//�}�b�v�S�̂̍��[����A�X�N���[���T�C�Y�̔����������āA�J�������ړ��o���鍶�[�̌��E�����߂�B
		if (camera_position.y < screen_info->GetCenterY()) {
			camera_position.y = screen_info->GetCenterY();
		}

		//�}�b�v�S�̂̉E�[����A�X�N���[���T�C�Y�̔����������āA�J�������ړ��o����E�[�̌��E�����߂�B
		if (camera_position.y > (map_size.y - screen_info->GetCenterY())) {
			camera_position.y = map_size.y - screen_info->GetCenterY();
		}
	}	
}

Vector2D Camera::GetScreenOffset() const {
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	if (screen_info != nullptr) {
		//�X�N���[���T�C�Y�̔������J�������W��������č��㌴�_�����߂�
		return camera_position  - Vector2D(screen_info->GetCenterX(), screen_info->GetCenterY());
	}
}
