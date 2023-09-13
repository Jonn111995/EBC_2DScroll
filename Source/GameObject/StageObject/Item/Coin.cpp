#include "Coin.h"
#include "DxLib.h"
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
	game_object_state = EGameObjectState::kPLAYING;
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
	DrawGraph(x, y, coin_graphic_handle, true);
}

void Coin::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);

	if (game_object_state == EGameObjectState::kPLAYING) {
		item_event->ScoreUp();
		item_event->DestroyItem(*this);
		game_object_state = EGameObjectState::kEND;
	}
}