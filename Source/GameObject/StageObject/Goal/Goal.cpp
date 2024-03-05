#include "Goal.h"
#include "DxLib.h"
#include "Interface/IGoalEvent.h"

Goal::Goal()
{
}

Goal::~Goal()
{
}

void Goal::Initialize() {
	__super::Initialize();

	goal_graphic_handle = LoadGraph(_T("Resources/Images/mapchip_046.bmp"));

	game_object_state = EGameObjectState::kPLAYING;
	body_collision.box_extent = Vector2D(24, 32);
	body_collision.center_position = Vector2D(24, 32);

	body_collision.object_type = kITEM_TYPE;
	body_collision.hit_object_types = kPLAYER_TYPE;
}

void Goal::Finalize() {
	__super::Finalize();
	goal_event = nullptr;
	goal_graphic_handle = 0;
}

void Goal::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void Goal::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);

	int x, y;
	GetPosition().ToInt(x, y);

	int x_graphic_size = 0;
	int y_graphic_size = 0;
	GetGraphSize(goal_graphic_handle, &x_graphic_size, &y_graphic_size);

	DrawGraph(x - screen_offset.x, y - screen_offset.y, goal_graphic_handle, true);
}

void Goal::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);
	goal_event->GameClear();
}
