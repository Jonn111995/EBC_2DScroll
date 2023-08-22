#include "Player.h"
#include "InputHandler.h"
#include "../Source/Animation/PlayerAnimResourcer.h"
#include "DxLib.h"
#include <iterator>
#include <math.h>

Player::Player()
	:input_handler(nullptr)
	,resourcer(nullptr)
	,player_state(EPlayerState::kIDLE)
	,player_anim_state(EPlayerAnimState::kIDLE_ANIM)
	,anim_speed(0.0f)
	,animation_frame(0.0f)
	,min_anim_frame(0.0f)
	,max_anim_frame(0.0f)
{
}

Player::~Player()
{
}

void Player::Initialize() {

	__super::Initialize();

    input_handler = new InputHandler();
	resourcer = new PlayerAnimResourcer();
	resourcer->Initialize();
}

void Player::Finalize(){

	__super::Finalize();

	delete input_handler;
	resourcer->Finalize();
	delete resourcer;
	input_handler = nullptr;
	resourcer = nullptr;
}

void Player::Update(float delta_time) {

	__super::Update(delta_time);

	std::vector<bool> input_button_status = input_handler->CheckInput(delta_time);
	Vector2D input_dir;
	player_state = kIDLE;

	if (input_button_status[kLEFT_B]) {
		input_dir.x = -50;
		SetDirection(CharacterDirection::kLEFT);
	}

	if (input_button_status[kRIGHT_B]) {
		input_dir.x = 50;
		SetDirection(CharacterDirection::kRIGHT);
	}

	if (input_button_status[kJUMP_B]) {
		Jump();
	}

	if (input_button_status[kATTACK_B]) {
		player_state = kATTACK;
	}
	
	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position;

	if (!bIsCanJump) {
		velocity += gravity_accelaration;

		input_dir.y = velocity;
		delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_time;

		if ((GetPosition().y + delta_position.y) > y_ground) {
			input_dir.y = y_ground;
			delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_time;
			velocity = 0;
			bIsCanJump = true;
			ChangePlayerState(kIDLE);
		}
		SetPosition(GetPosition() + delta_position);
	}
	else {
		delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_time;
		SetPosition(GetPosition() + delta_position);
	}


	if (delta_position == Vector2D(0.0f, 0.0f)) {

		if (player_state == kATTACK) {
			player_anim_state = kATTACK_ANIM;
		} else {
			player_anim_state = kIDLE_ANIM;
		}
	}

	if (delta_position.x != 0.0f && delta_position.y == 0.0f) {
		player_anim_state = kRUN_ANIM;
	}
	
	if (delta_position.y < 0.0f) {
		player_anim_state = kJUMP_UP_ANIM;
	} else if (delta_position.y > 0.0f) {

		if (delta_position.x != 0.0f) {
			player_anim_state = kJUMP_MOVE_ANIM;
		} else {
			player_anim_state = kJUMP_FALL_ANIM;
		}
	}
	
	switch (player_anim_state) {
	case kIDLE_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kIDLE);
		anim_speed = 4.0f;
		min_anim_frame = 0.0f;
		max_anim_frame = now_animations.size() - 1.0f;
		break;
	case kRUN_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kRUN);
		anim_speed = 10.0f;
		min_anim_frame = 0.0f;
		max_anim_frame = now_animations.size() - 1.0f;
		break;
	case kJUMP_UP_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		anim_speed = 10.0f;
		min_anim_frame = 0.0f;
		max_anim_frame = 1.99f;
		break;
	case kJUMP_MOVE_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		anim_speed = 5.0f;
		min_anim_frame = 2.0f;
		max_anim_frame = 3.99f;
		break;
	case kJUMP_FALL_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		anim_speed = 20.0f;
		min_anim_frame = 4.0f;
		max_anim_frame = 5.99f;
		break;
	case kATTACK_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kATTACK);
		anim_speed = 5.0f;
		min_anim_frame = 0.0f;
		max_anim_frame = now_animations.size() - 1;
		break;
	}

	if (animation_frame <= min_anim_frame) {
		animation_frame = min_anim_frame;
	}

	//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
	if (animation_frame >= now_animations.size()) {
		animation_frame = min_anim_frame;
	}

	animation_frame += delta_time * anim_speed;

	if (animation_frame >= max_anim_frame) {
		animation_frame = min_anim_frame;
	}
}

void Player::Draw(const Vector2D& screen_offset) {

	int x, y;
	GetPosition().ToInt(x, y);
	switch (GetDirection()) {

	case kLEFT:
		DrawTurnGraph(x, y, now_animations[animation_frame], true);
		break;

	case kRIGHT:
		DrawGraph(x, y, now_animations[animation_frame], true);
		break;
	}
}

void Player::OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision)
{
}

void Player::ChangePlayerState(const EPlayerState new_state) {

	ExitState();
	player_state = new_state;
	EnterState();
}

void Player::EnterState() {

	switch (player_state) {

	case kIDLE:
		break;
	case kWALK:
		break;
	case kRUN:
		break;
	case kJUMP:
		break;
	case kATTACK:
		break;
	case kDEAD:
		break;
	}
}

void Player::ExitState() {
	switch (player_state) {

	case kIDLE:
		break;
	case kWALK:
		break;
	case kRUN:
		break;
	case kJUMP:
		break;
	case kDEAD:
		break;
	}
}

void Player::Jump() {

	if (bIsCanJump) {
		bIsCanJump = false;
		velocity = -50;
		y_ground = GetPosition().y;
	}
}
