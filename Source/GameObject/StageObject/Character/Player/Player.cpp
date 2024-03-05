#include "Player.h"
#include "../Source/System/SoundManager.h"
#include "InputHandler.h"
#include "../Source/Animation/PlayerAnimResourcer.h"
#include "../Interface/CharacterEventInterface.h"
#include "../Player/Interface/IPlayerEvent.h"
#include "../Source/GameObject/StageObject/Weapon/Hand.h"
#include "DxLib.h"
#include <iterator>
#include <math.h>

Player::Player()
	:input_handler(nullptr)
	, resourcer(nullptr)
	, player_state(EPlayerState::kIDLE)
	, previous_anim_state(EPlayerAnimState::kIDLE_ANIM)
	, player_anim_state(EPlayerAnimState::kIDLE_ANIM)
	, bIsCanJump(true)
	, invincible_time(DEFAULT_INVINCIBLE_TIME)
{
	SetAttack(10);
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
	character_anim.now_animations = resourcer->GetAnimaitonHandle(kIDLE);
	body_collision.center_position = Vector2D(64, 84);
	body_collision.box_extent = Vector2D(12, 24);
	body_collision.hit_object_types = kENEMY_TYPE | kWEAPON_TYPE | kKILL_TYPE;
	body_collision.object_type = kPLAYER_TYPE;
	game_object_state = EGameObjectState::kPLAYING;
	SetSpeed(MOVEMENT_SPEED);

	SoundManager* sound_manager = SoundManager::GetInstance();
	jump_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/Action/se_jump.mp3");
	dead_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/se_dead.mp3");
	
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
	SoundManager* sound_manager = SoundManager::GetInstance();

	switch (game_object_state) {
	case EGameObjectState::kPLAYING:
	{
		std::vector<bool> input_button_status = input_handler->CheckInput(delta_time);
		if (!is_reject_input) {
			if (input_button_status[kLEFT_B]) {
				input_direction.x = -10.0f;
				SetDirection(CharacterDirection::kLEFT);
				player_anim_state = kRUN_ANIM;
				EnterAnimState();
			}

			if (input_button_status[kRIGHT_B]) {
				input_direction.x = 10.0f;
				SetDirection(CharacterDirection::kRIGHT);
				player_anim_state = kRUN_ANIM;
				EnterAnimState();
			}

			if (input_button_status[kJUMP_B]) {
				StartJump();
				player_anim_state = kJUMP_UP_ANIM;
				EnterAnimState();
			}

			if (input_button_status[kATTACK_B]) {
				if (bIsCanJump) {
					ChangePlayerState(kATTACK);
					player_anim_state = kATTACK_ANIM;
					EnterAnimState();
				}
			}
		}

		//無敵状態チェック
		if (is_no_damage) {
			CheckKeepInvincible(delta_time);
		}

		//更新後の座標と比較して、移動量を出すため取得。
		Vector2D pre_position = GetPosition();

		switch (player_state) {
		case kJUMP:

			initial_velocity += GRAVITY_ACCELARATION;
			input_direction.x *= AIR_RESISTANCE;
			input_direction.y = initial_velocity;
			break;

		case kDAMAGE:

			count_time += delta_time;

			if (count_time < 0.1f) {
				is_reject_input = true;
				input_direction = knock_back_dir;
			}
			else if (count_time > 0.4f) {
				is_reject_input = false;
				ChangeInvincible();
			}
			break;

		case kATTACK:

			if (character_anim.animation_frame >= character_anim.max_anim_frame - 0.2f) {
				ChangePlayerState(kIDLE);
			}
			break;

		case kDEAD: 

			if (DeadMove(delta_time)) {
				CallDestroy();
			}
			break;

		default:
			break;
		}

		//移動処理はCharacterに任せる
		//Updateをどんな状態で呼んでも不具合が起きずに動くように実装する
		__super::Update(delta_time);

		ChangeAnimState(delta_time, GetPosition() - pre_position);
		break;
	}
	case EGameObjectState::kPAUSE:
		break;

	case EGameObjectState::kEND:
		ChangePlayerState(kIDLE);
		ChangeAnimState(delta_time, Vector2D(0.f, 0.f));
		break;
	}
}

void Player::Draw(const Vector2D& screen_offset) {

	if (player_state == kDAMAGE || is_no_damage) {
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

	if (player_state == kDEAD) {
		return;
	}

	if (!is_no_damage && (hit_collision.object_type & kENEMY_TYPE || hit_collision.object_type & kWEAPON_TYPE)) {
		ChangePlayerState(kDAMAGE);
		__super::OnHitBoxCollision(hit_object, hit_collision);
	}
	else if (is_use_item && hit_collision.object_type & kENEMY_TYPE) {
		character_event->GiveDamageEvent(*this, *hit_object, 1000);
	}
}


void Player::ChangePlayerState(const EPlayerState new_state) {

	ExitState();
	player_state = new_state;
	EnterState();
}

void Player::EnterState() {
	if (!character_anim.is_can_be_interrupted) {
		return;
	}

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
	case kDAMAGE:
		ChangeAnimState(0.f, Vector2D(0.f, 0.f));
		break;
	case kDEAD:
		count_time = 0.f;
		is_no_damage = false;
		is_reject_input = true;
		is_use_item = false;
		invincible_time = 1.5;
		initial_velocity = INITIAL_JUMP_VELOCITY;
		SetSpeed(100.f);
		ChangeAnimState(0.f, Vector2D(0.f, 0.f));
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
	case kDAMAGE:
		break;
	case kDEAD:
		is_reject_input = false;
		SetSpeed(MOVEMENT_SPEED);
		break;
	}
}

void Player::SetInvincibleState() {
	ChangeInvincible();
}

void Player::SetDeadState() {
	if (player_state == kDEAD) {
		return;
	}
	SoundManager::GetInstance()->PlayLoadSound(dead_sound);

	ChangePlayerState(kDEAD);
}


void Player::ChangeAnimState(const float delta_time = 0.0f, const Vector2D& delta_position = Vector2D(0.f,0.f)) {

	//delta_positionは、更新前と後の移動量
	
	SetIsMove(false);

	if (delta_position == Vector2D(0.0f, 0.0f) || player_state == kDEAD) {

		if (player_state == kATTACK) {
			player_anim_state = kATTACK_ANIM;
		}
		else if (player_state == kDAMAGE || player_state == kDEAD) {
			player_anim_state = kDAMAGE_ANIM;
		}
		else {
			player_anim_state = kIDLE_ANIM;
		}
		
	}
	else {
		SetIsMove(true);
	}

	if (GetIsMove()) {

		if (delta_position.x != 0.0f && delta_position.y == 0.0f) {
			player_anim_state = kRUN_ANIM;
		}

		//ジャンプ中は、ベクトルの値によってアニメーションを変える
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
	}

	EnterAnimState();
	
	UpdateAnimFrame(delta_time);
}

void Player::EnterAnimState() {

	if (player_anim_state == previous_anim_state)
	{
		return;
	}
	previous_anim_state = player_anim_state;
	switch (player_anim_state) {
	case kIDLE_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kIDLE);
		character_anim.anim_speed = 4.0f;
		character_anim.min_anim_frame = 0.0f;
		character_anim.animation_frame = character_anim.min_anim_frame;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
		character_anim.is_loop = true;
		character_anim.is_can_be_interrupted = true;
		break;
	case kRUN_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kRUN);
		character_anim.anim_speed = 10.0f;
		character_anim.min_anim_frame = 0.0f;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1.0f;
		character_anim.is_loop = false;
		character_anim.is_can_be_interrupted = true;
		break;
	case kJUMP_UP_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		character_anim.anim_speed = 10.0f;
		character_anim.min_anim_frame = 0.0f;
		character_anim.max_anim_frame = 1.99f;
		character_anim.is_loop = true;
		character_anim.is_can_be_interrupted = false;
		break;
	case kJUMP_MOVE_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		character_anim.anim_speed = 5.0f;
		character_anim.min_anim_frame = 2.0f;
		character_anim.max_anim_frame = 3.99f;
		break;
	case kJUMP_FALL_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kJUMP);
		character_anim.anim_speed = 20.0f;
		character_anim.min_anim_frame = 4.0f;
		character_anim.max_anim_frame = 5.99f;
		break;
	case kATTACK_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kATTACK);
		character_anim.anim_speed = 4.5f;
		character_anim.min_anim_frame = 0.0f;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1;
		character_anim.is_loop = false;
		character_anim.is_can_be_interrupted = false;
		break;
	case kDAMAGE_ANIM:
		character_anim.now_animations = resourcer->GetAnimaitonHandle(EPlayerState::kDAMAGE);
		character_anim.anim_speed = 0.0f;
		character_anim.min_anim_frame = 0.0f;
		character_anim.max_anim_frame = character_anim.now_animations.size() - 1;
		break;
	}
}

void Player::UpdateAnimFrame(const float delta_time) {

	if (character_anim.animation_frame <= character_anim.min_anim_frame) {
		character_anim.animation_frame = character_anim.min_anim_frame;
	}

	//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
	if (character_anim.animation_frame >= character_anim.now_animations.size()) {
		character_anim.animation_frame = character_anim.min_anim_frame;
	}

	character_anim.animation_frame += delta_time * character_anim.anim_speed;

	//アニメーションを切り替えた場合に起こるバッファオーバーフロー対策
	if (character_anim.animation_frame >= character_anim.max_anim_frame) {
		character_anim.animation_frame = character_anim.min_anim_frame;
	}
}


void Player::Attack() {
	equip_weapon->SetWeaponDirection();
	equip_weapon->SetAttackRange(body_collision);
	character_event->AddWeapon(*equip_weapon);
}

void Player::StopAttack() {
	character_event->RemoveWeapon(equip_weapon);
}

bool Player::DeadMove(const float delta_time) {
	return __super::DeadMove(delta_time);
}

void Player::CallDestroy() {
	if (!player_event->ExecuteRespawn()) {
		game_object_state = EGameObjectState::kEND;
		__super::CallDestroy();
	}
	else {
		InitialWhenRespawn();
		ChangePlayerState(kIDLE);
	}
}

void Player::StartJump() {

	if (bIsCanJump) {
		ChangePlayerState(kJUMP);
		bIsCanJump = false;
		initial_velocity = INITIAL_JUMP_VELOCITY;
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlayLoadSound(jump_sound);
	}
}

void Player::JumpMove(const float delta_time) {

	Vector2D delta_move_amount;
	Vector2D new_position = GetPosition();
	//DXLibでは、Y軸の下方向が+になる。initial_velocityがJump()で、-の値でで初期化されている
	initial_velocity += GRAVITY_ACCELARATION;

	input_direction.x *= AIR_RESISTANCE;
	input_direction.y = initial_velocity;
	delta_move_amount = input_direction.Normalize() * MOVEMENT_SPEED * delta_time;

	//ここから当たり判定
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

void Player::ChangeInvincible() {
	is_no_damage = true;
}

void Player::CheckKeepInvincible(const float delta_time) {

	count_time += delta_time;

	if (count_time > invincible_time) {
		ChangePlayerState(kIDLE);
		is_no_damage = false;
		is_use_item = false;
		invincible_time = DEFAULT_INVINCIBLE_TIME;
		count_time = 0.f;
	}
}

void Player::InitialWhenRespawn() {
	bIsCanJump = true;
	count_time = 0.f;
	is_no_damage = false;
	is_use_item = false;
	is_reject_input = false;
}

float Player::UpdateXPosition(const bool is_can_move_to_x, const float update_x_amount) {
	return __super::UpdateXPosition(is_can_move_to_x, update_x_amount);
}


float Player::UpdateYPosition(const bool is_can_move_to_y, const float update_y_amount) {

	switch (player_state) {
	case kJUMP:
		if (!is_can_move_to_y) {

			bIsCanJump = true;
			initial_velocity = RESET_INITIAL_VELOCITY;
			ChangePlayerState(kIDLE);
			return  GetPosition().y;
		}
		else {
			return GetPosition().y + update_y_amount;
		}
		break;
	default:
		return __super::UpdateYPosition(is_can_move_to_y, update_y_amount);
	}
}

