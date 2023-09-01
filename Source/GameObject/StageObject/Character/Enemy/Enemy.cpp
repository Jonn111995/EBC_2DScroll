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

	LoadGraph("murasuke_pp_wait", wait_enemy_graphic_handle);
	SetDirection(kLEFT);
	now_animations.push_back(wait_enemy_graphic_handle);
	anim_speed = 4.0f;
	min_anim_frame = 0.0f;
	max_anim_frame = now_animations.size() - 1.0f;
}

void Enemy::Finalize() {
	__super::Finalize();
}

void Enemy::Update(float delta_time) {
	__super::Update(delta_time);
}

void Enemy::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}

void Enemy::OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision){
	__super::OnHitBoxCollision(hit_object, hit_collision);
}
