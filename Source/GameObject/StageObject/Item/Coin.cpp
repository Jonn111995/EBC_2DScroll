#include "Coin.h"
#include "DxLib.h"
#include "../Source/System/SoundManager.h"
#include "Interface/IItemEvent.h"
Coin::Coin()
	: coin_graphic_handle(0)
	, item_event(nullptr)
{
}

Coin::~Coin()
{
}

void Coin::Initialize() {
	__super::Initialize();
	coin_graphic_handle = LoadGraph(_T("Resources/Images/mapchip_035.bmp"));
	
	SoundManager* sound_manager = SoundManager::GetInstance();
	get_coin_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/se_get_coin.mp3");
	game_object_state = EGameObjectState::kPLAYING;
	body_collision.box_extent = Vector2D( 16, 16 );
	body_collision.center_position = Vector2D(16, 16);

	body_collision.object_type = kITEM_TYPE;
	body_collision.hit_object_types = kPLAYER_TYPE;
}

void Coin::Finalize() {
	__super::Finalize();
	item_event = nullptr;
	coin_graphic_handle = 0;
}

void Coin::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void Coin::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);

	int x, y;
	GetPosition().ToInt(x, y);

	int x_graphic_size = 0;
	int y_graphic_size = 0;
	GetGraphSize(coin_graphic_handle, &x_graphic_size, &y_graphic_size);

	DrawGraph(x - screen_offset.x, y - screen_offset.y, coin_graphic_handle, true);

	//デバック用
	unsigned int color = GetColor(255, 255, 255);
	DrawBox(x - screen_offset.x, y - screen_offset.y, x - screen_offset.x + x_graphic_size, y - screen_offset.y + y_graphic_size, color, false);
}

void Coin::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);

	if (game_object_state == EGameObjectState::kPLAYING) {
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlayLoadSound(get_coin_sound);

		item_event->ScoreUp();

		item_event->DestroyItem(*this);
		game_object_state = EGameObjectState::kEND;
	}
}
