#include "InvincibleCan.h"
#include "DxLib.h"
#include "../Source/System/SoundManager.h"
#include "Interface/IItemEvent.h"

InvincibleCan::InvincibleCan()
	: invincible_time(10.f)
	, invincible_can_graphic(0)
	, item_event(nullptr)
{
}

InvincibleCan::~InvincibleCan()
{
}

void InvincibleCan::Initialize() {
	__super::Initialize();
	invincible_can_graphic = LoadGraph(_T("Resources/Images/mapchip_033.bmp"));

	SoundManager* sound_manager = SoundManager::GetInstance();
	get_invincible_can_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/se_get_invincible_can.mp3");

	game_object_state = EGameObjectState::kPLAYING;
	body_collision.box_extent = Vector2D(16, 16);
	body_collision.center_position = Vector2D(16, 16);

	body_collision.object_type = kITEM_TYPE;
	body_collision.hit_object_types = kPLAYER_TYPE;
}

void InvincibleCan::Finalize() {
	__super::Finalize();
	item_event = nullptr;
	invincible_can_graphic = 0;
}

void InvincibleCan::Update(float delta_seconds)
{
}

void InvincibleCan::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);

	int x, y;
	GetPosition().ToInt(x, y);

	int x_graphic_size = 0;
	int y_graphic_size = 0;
	GetGraphSize(invincible_can_graphic, &x_graphic_size, &y_graphic_size);

	DrawGraph(x - screen_offset.x, y - screen_offset.y, invincible_can_graphic, true);

	//デバック用
	unsigned int color = GetColor(255, 255, 255);
	DrawBox(x - screen_offset.x, y - screen_offset.y, x - screen_offset.x + x_graphic_size, y - screen_offset.y + y_graphic_size, color, false);
}

void InvincibleCan::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {

	__super::OnHitBoxCollision(hit_object, hit_collision);

	if (game_object_state == EGameObjectState::kPLAYING) {
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlayLoadSound(get_invincible_can_sound);

		item_event->ChangeInvincible(invincible_time);

		item_event->DestroyItem(*this);
		game_object_state = EGameObjectState::kEND;
	}
}
