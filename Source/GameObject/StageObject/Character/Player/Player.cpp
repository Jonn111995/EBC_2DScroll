#include "Player.h"
#include "InputHandler.h"
#include "../Source/Animation/PlayerAnimResourcer.h"
#include "../Interface/CharacterEventInterface.h"
#include "DxLib.h"
#include <iterator>
#include <math.h>

namespace {
	const float AIR_RESISTANCE = 0.8f;
	const float RESET_INITIAL_VELOCITY = 0.0f;
}

Player::Player()
	:input_handler(nullptr)
	, resourcer(nullptr)
	, player_state(EPlayerState::kIDLE)
	, player_anim_state(EPlayerAnimState::kIDLE_ANIM)
	, initial_velocity(0.f)
	, bIsCanJump(true)
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
	body_collision.center_position = Vector2D(64, 84);
	body_collision.box_extent = Vector2D(12, 24);
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

	std::vector<bool> input_button_status = input_handler->CheckInput(delta_time);
	player_state = kIDLE;

	if (input_button_status[kLEFT_B]) {
		input_direction.x = -10.0f;
		SetDirection(CharacterDirection::kLEFT);
	}

	if (input_button_status[kRIGHT_B]) {
		input_direction.x = 10.0f;
		SetDirection(CharacterDirection::kRIGHT);
	}

	if (input_button_status[kJUMP_B]) {
		StartJump();
	}

	if (input_button_status[kATTACK_B]) {
		player_state = kATTACK;
	}

	if (!bIsCanJump) {
		player_state = kJUMP;
	}

	//�X�V��̍��W�Ɣ�r���āA�ړ��ʂ��o�����ߎ擾�B
	Vector2D pre_position = GetPosition();

	switch (player_state) {
		case kJUMP:
			JumpMove(delta_time);
			break;
		default:
			//�ړ�������Character�ɔC����
			__super::Update(delta_time);
			break;
	}

	ChangeAnimState(delta_time, (GetPosition() - pre_position));
}

void Player::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}

void Player::OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) {

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

void Player::ChangeAnimState(const float delta_time, const Vector2D& delta_position) {

	//delta_position�́A�X�V�O�ƌ�̈ړ���

	if (delta_position == Vector2D(0.0f, 0.0f)) {

		if (player_state == kATTACK) {
			player_anim_state = kATTACK_ANIM;
		}
		else {
			player_anim_state = kIDLE_ANIM;
		}
	}

	if (delta_position.x != 0.0f && delta_position.y == 0.0f) {
		player_anim_state = kRUN_ANIM;
	}

	//�W�����v���́A�x�N�g���̒l�ɂ���ăA�j���[�V������ς���
	if (delta_position.y < 0.0f) {
		player_anim_state = kJUMP_UP_ANIM;
	}
	else if (delta_position.y > 0.0f) {

		if (delta_position.x != 0.0f) {
			player_anim_state = kJUMP_MOVE_ANIM;
		}
		else {
			player_anim_state = kJUMP_FALL_ANIM;
		}
	}

	EnterAnimState();
	CheckAnimFrame(delta_time);
}

void Player::EnterAnimState() {

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
}

void Player::CheckAnimFrame(const float delta_time) {

	if (animation_frame <= min_anim_frame) {
		animation_frame = min_anim_frame;
	}

	//�A�j���[�V������؂�ւ����ꍇ�ɋN����o�b�t�@�I�[�o�[�t���[�΍�
	if (animation_frame >= now_animations.size()) {
		animation_frame = min_anim_frame;
	}

	animation_frame += delta_time * anim_speed;

	//�A�j���[�V������؂�ւ����ꍇ�ɋN����o�b�t�@�I�[�o�[�t���[�΍�
	if (animation_frame >= max_anim_frame) {
		animation_frame = min_anim_frame;
	}
}

void Player::StartJump() {

	if (bIsCanJump) {
		bIsCanJump = false;
		initial_velocity = -25;
	}
}

void Player::JumpMove(const float delta_time) {

	Vector2D delta_move_amount;
	Vector2D new_position = GetPosition();
	//DXLib�ł́AY���̉�������+�ɂȂ�Binitial_velocity��Jump()�ŁA-�̒l�łŏ���������Ă���
	initial_velocity += GRAVITY_ACCELARATION;

	input_direction.x *= AIR_RESISTANCE;
	input_direction.y = initial_velocity;
	delta_move_amount = input_direction.Normalize() * MOVEMENT_SPEED * delta_time;

	//�������瓖���蔻��
	bool is_can_move_y = ICharacterEvent->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
	if (!is_can_move_y) {

		bIsCanJump = true;
		initial_velocity = RESET_INITIAL_VELOCITY;
		ChangePlayerState(kIDLE);
		new_position.y = GetPosition().y;
	}
	else {
		new_position.y = GetPosition().y + delta_move_amount.y;
	}

	bool is_can_move_x = ICharacterEvent->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);
	if (is_can_move_x) {
		new_position.x += delta_move_amount.x;
	}

	SetPosition(new_position);
}
