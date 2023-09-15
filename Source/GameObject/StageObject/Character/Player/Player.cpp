#include "Player.h"
#include "InputHandler.h"
#include "../Source/Animation/PlayerAnimResourcer.h"
#include "../Interface/CharacterEventInterface.h"
#include "../Player/Interface/IPlayerEvent.h"
#include "../Source/GameObject/StageObject/Weapon/Hand.h"
#include "DxLib.h"
#include <iterator>
#include <math.h>

namespace {
	const float AIR_RESISTANCE = 0.8f;
	const float RESET_INITIAL_VELOCITY = 0.0f;
	const float DEFAULT_INVINCIBLE_TIME = 1.5f;
}

Player::Player()
	:input_handler(nullptr)
	, resourcer(nullptr)
	, player_state(EPlayerState::kIDLE)
	, player_anim_state(EPlayerAnimState::kIDLE_ANIM)
	, initial_velocity(0.f)
	, bIsCanJump(true)
	, bIsNoDamage(false)
	, invincible_time(DEFAULT_INVINCIBLE_TIME)
{
	SetAttack(10);
	//SetHp(10);
}

Player::~Player()
{
}

void Player::Initialize() {
	__super::Initialize();

    input_handler = new InputHandler();
	resourcer = new PlayerAnimResourcer();
	equip_weapon = new Hand();
	equip_weapon->Initialize();
	equip_weapon->SetOwner(this);
	resourcer->Initialize();
	body_collision.center_position = Vector2D(64, 84);
	body_collision.box_extent = Vector2D(12, 24);
	body_collision.hit_object_types = kENEMY_TYPE | kWEAPON_TYPE;
	body_collision.object_type = kPLAYER_TYPE;
	game_object_state = EGameObjectState::kPLAYING;
	
}

void Player::Finalize(){
	__super::Finalize();

	delete input_handler;

	resourcer->Finalize();
	delete resourcer;
	
	equip_weapon->Finalize();
	delete equip_weapon;

	player_event = nullptr;
	input_handler = nullptr;
	resourcer = nullptr;
	equip_weapon = nullptr;
}

void Player::Update(float delta_time) {

	switch (game_object_state) {
	case EGameObjectState::kPLAYING:
	{
		std::vector<bool> input_button_status = input_handler->CheckInput(delta_time);
		if (!is_reject_input) {
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
				ChangePlayerState(kATTACK);
			}

			if (!bIsCanJump) {
				ChangePlayerState(kJUMP);
			}
		}

		//�X�V��̍��W�Ɣ�r���āA�ړ��ʂ��o�����ߎ擾�B
		Vector2D pre_position = GetPosition();

		if (bIsNoDamage) {
			count_time += delta_time;

			if (count_time > invincible_time) {
				ChangePlayerState(kIDLE);
				bIsNoDamage = false;
				is_get_damaged = false;
				invincible_time = DEFAULT_INVINCIBLE_TIME;
				count_time = 0.f;
			}
		}

		switch (player_state) {
		case kJUMP:
			JumpMove(delta_time);
			break;
		case kDAMAGE:
			count_time += delta_time;
			if (count_time < 0.1f) {

				is_reject_input = true;
				Vector2D recoil_dir = { 0.f, 0.f };
				input_direction = knock_back_dir;
				//���̂Ƃ���Move�ő�p�\
				Move(delta_time);
				//KnockBack(delta_time, knock_back_dir);
			}
			else if (count_time > 0.4f) {
				ChangePlayerState(kINVINCIBLE);
			}
			break;
		case kATTACK:
			if (animation_frame >= max_anim_frame - 0.2f) {
				ChangePlayerState(kIDLE);
			}

		case kINVINCIBLE:
			//���G��Ԃ̎��͈ړ����������������̂ŁAbreak��u�����Ƀt�H�[�X���[����B
		default:
			//�ړ�������Character�ɔC����
			__super::Update(delta_time);
			break;
		}

		ChangeAnimState(delta_time, (GetPosition() - pre_position));
		break;
	}
	case EGameObjectState::kPAUSE:
		break;
	case EGameObjectState::kEND:
		count_time += delta_time;
		if (count_time > 1.5f) {
			CallDeadEvent();
			game_object_state = EGameObjectState::kPLAYING;
		}
		break;
	}
}

void Player::Draw(const Vector2D& screen_offset) {
	//�f�o�b�N�p
	unsigned int color = GetColor(255, 0, 0);
	DrawFormatString(0, 0, color, "X=%f, Y=%f:::::", body_collision.center_position2.x, body_collision.center_position2.y);

	if (player_state == kDAMAGE || bIsNoDamage) {
		if (((int)(count_time * 10) % (int)(0.2f * 10)) == 0.f) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		}
	}
	__super::Draw(screen_offset);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	equip_weapon->Draw(screen_offset);
}

void Player::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {

	if (!bIsNoDamage) {
		ChangePlayerState(kDAMAGE);
		ChangeAnimState(0.f, Vector2D(0.f, 0.f));
		__super::OnHitBoxCollision(hit_object, hit_collision);
	}
	else if (bIsNoDamage && hit_collision.object_type & kENEMY_TYPE) {
		character_event->GiveDamageEvent(*this, *hit_object, 1000);
	}
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
		Attack();
		break;
	case kINVINCIBLE:
		is_reject_input = false;
		bIsNoDamage = true;
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
	case kATTACK:
		character_event->RemoveWeapon(equip_weapon);
		break;
	case kINVINCIBLE:
		break;
	case kDEAD:
		break;
	}
}

void Player::SetInvincibleState() {
	ChangePlayerState(kINVINCIBLE);
}

void Player::ChangeAnimState(const float delta_time = 0.0f, const Vector2D& delta_position = Vector2D(0.f,0.f)) {

	//delta_position�́A�X�V�O�ƌ�̈ړ���
	if (player_state == kIDLE) {
		player_anim_state = kIDLE_ANIM;
	}

	if (delta_position == Vector2D(0.0f, 0.0f)) {

		if (player_state == kATTACK) {
			player_anim_state = kATTACK_ANIM;
		}
		else if (player_state == kDAMAGE) {
			player_anim_state = kDAMAGE_ANIM;
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
	UpdateAnimFrame(delta_time);
}

void Player::EnterAnimState() {

	switch (player_anim_state) {
	case kIDLE_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kIDLE);
		anim_speed = 4.0f;
		min_anim_frame = 0.0f;
		animation_frame = min_anim_frame;
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
		anim_speed = 4.5f;
		min_anim_frame = 0.0f;
		max_anim_frame = now_animations.size() - 1;
		break;
	case kDAMAGE_ANIM:
		now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kDAMAGE);
		anim_speed = 0.0f;
		min_anim_frame = 0.0f;
		max_anim_frame = now_animations.size() - 1;
		break;
	}
}

void Player::UpdateAnimFrame(const float delta_time) {

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

void Player::KnockBack(const float delta_time, const Vector2D& recoil_velocity) {
	__super::KnockBack(delta_time, recoil_velocity);
}

void Player::Attack() {
	equip_weapon->SetWeaponDirection();
	equip_weapon->SetAttackRange(body_collision);
	character_event->AddWeapon(*equip_weapon);
}

void Player::StopAttack() {
	character_event->RemoveWeapon(equip_weapon);
}

void Player::CallDeadEvent() {

	if (!player_event->ExecuteRespawn()) {
		__super::CallDeadEvent();
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
	bool is_can_move_y = character_event->CheckCanMoveToY(GetPosition(), delta_move_amount, body_collision);
	if (!is_can_move_y) {

		bIsCanJump = true;
		initial_velocity = RESET_INITIAL_VELOCITY;
		ChangePlayerState(kIDLE);
		new_position.y = GetPosition().y;
	}
	else {
		new_position.y = GetPosition().y + delta_move_amount.y;
	}

	bool is_can_move_x = character_event->CheckCanMoveToX(GetPosition(), delta_move_amount, body_collision);
	if (is_can_move_x) {
		new_position.x += delta_move_amount.x;
	}
	Vector2D amount = new_position - GetPosition();
	body_collision.center_position2 += amount;
	SetPosition(new_position);
}
