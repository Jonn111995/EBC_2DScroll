#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize() {
	__super::Initialize();

	wait_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_pp_wait.bmp"));

	now_animations.push_back(wait_enemy_graphic_handle);
	anim_speed = 4.0f;
	min_anim_frame = 0.0f;
	max_anim_frame = now_animations.size() - 1.0f;

	SetSpeed(50.f);

	body_collision.object_type = kENEMY_TYPE;
	body_collision.center_position = Vector2D(20, 28);
	body_collision.box_extent = Vector2D(10.f, 18.f);
}

void Enemy::Finalize() {
	__super::Finalize();
}

void Enemy::Update(float delta_time) {

	input_direction.x = -0.1f;
	__super::Update(delta_time);
}

void Enemy::Draw(const Vector2D& screen_offset) {
	unsigned int color = GetColor(255, 0, 0);
	DrawFormatString(0, 32, color, "X=%f, Y=%f:::::", body_collision.center_position2.x, body_collision.center_position2.y);

	__super::Draw(screen_offset);
}

void Enemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision){
	__super::OnHitBoxCollision(hit_object, hit_collision);
}
