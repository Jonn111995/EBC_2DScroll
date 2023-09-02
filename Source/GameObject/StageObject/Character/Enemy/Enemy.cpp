#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
	: range_move(300.f)
	, move_amount(0.f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize() {
	__super::Initialize();

	wait_enemy_graphic_handle = LoadGraph(_T("Resources/Images/murasuke_pp_wait.bmp"));
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), 4, 4, 1, 40, 48, walk_enemy_graphic_handle);
	int array_size = sizeof(*walk_enemy_graphic_handle);
	now_animations.assign(walk_enemy_graphic_handle, walk_enemy_graphic_handle + array_size);
	//now_animations.push_back(walk_enemy_graphic_handle[0]);
	anim_speed = 5.0f;
	min_anim_frame = 0.0f;
	max_anim_frame = now_animations.size() - 1.0f;
	move_amount = range_move / 2;
	SetSpeed(50.f);
	body_collision.object_type = kENEMY_TYPE;
	body_collision.center_position = Vector2D(20, 28);
	body_collision.box_extent = Vector2D(10.f, 18.f);
}

void Enemy::Finalize() {
	__super::Finalize();
}

void Enemy::Update(float delta_time) {

	if (move_amount <= 0) {
		move_amount = range_move / 2;
		SetDirection(kLEFT);
	}
	else if (move_amount >= range_move) {
		move_amount = range_move / 2;
		SetDirection(kRIGHT);
	}

	switch (GetDirection()) {
	case kRIGHT:
		move_amount--;
		input_direction.x = -1.f;
		break;
	case kLEFT:
		move_amount++;
		input_direction.x = 1.f;
		break;
	}
	__super::Update(delta_time);

	if (animation_frame <= min_anim_frame) {
		animation_frame = min_anim_frame;
	}

	//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
	if (animation_frame >= now_animations.size()) {
		animation_frame = min_anim_frame;
	}

	animation_frame += delta_time * anim_speed;

	//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
	if (animation_frame >= max_anim_frame) {
		animation_frame = min_anim_frame;
	}
}

void Enemy::Draw(const Vector2D& screen_offset) {
	unsigned int color = GetColor(255, 0, 0);
	DrawFormatString(0, 32, color, "X=%f, Y=%f:::::", body_collision.center_position2.x, body_collision.center_position2.y);

	__super::Draw(screen_offset);
}

void Enemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision){
	__super::OnHitBoxCollision(hit_object, hit_collision);
}
