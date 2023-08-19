#include "Player.h"
#include "InputHandler.h"
#include "DxLib.h"

Player::Player()
	:input_handler(nullptr)
	, loaded_sprits()
{
}

Player::~Player()
{
}

void Player::Initialize() {

    input_handler = new InputHandler();
	LoadDivGraph(_T("Resources/Images/collon_wait.bmp"), 4, 4, 1, 128, 128, loaded_sprits);
}

void Player::Finalize(){

	delete input_handler;
	input_handler = nullptr;
}

void Player::Update(float delta_time) {

	EButton input_button = input_handler->CheckInput(delta_time);

}

void Player::Draw(const Vector2D& screen_offset) {

	DrawGraph(GetPosition().x, GetPosition().y, loaded_sprits[0], true);
}

void Player::OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision)
{
}

void Player::ChangePlayerState(const EPlayerState new_state)
{
}

void Player::EnterState()
{
}

void Player::ExitState()
{
}
