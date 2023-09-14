#pragma once
#include "../Source/Utility/Vector2D.h"

class Camera {
public :
	Camera();
	virtual ~Camera();
public:
	void UpdateCamera(const Vector2D& chase_target_position);
	Vector2D GetCameraPosition() const { return camera_position; }
	Vector2D GetScreenOffset() const;
	void SetOverallMapWidth(const Vector2D size) { overall_map_size = size; }
private:
	Vector2D camera_position;
	Vector2D overall_map_size;
};