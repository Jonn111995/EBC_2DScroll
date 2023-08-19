#include "SampleObject.h"

#include "DxLib.h"
#include <vector>

SampleObject::SampleObject()
	: loaded_sprite_handle(0)
{
}

SampleObject::~SampleObject()
{
	Finalize();
}

void SampleObject::Initialize()
{
	__super::Initialize();
	count = 0;

	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	loaded_sprite_handle = LoadGraph(_T("Resources/Images/collon_wait.bmp"));
	LoadDivGraph(_T("Resources/Images/collon_wait.bmp"),4,4,1,128,128,loaded_sprits);
}

void SampleObject::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	count += delta_seconds *2.0f;
	if (count >= 4.0f) {
		count = 0.0f;
	}
	// “®‚©‚·
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		input_dir.y = -1;
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		input_dir.y = 1;
	}
	
	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void SampleObject::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	int num = static_cast<int>(count);
	// ‰æ‘œ‚Ì•`‰æ
	int x, y;
	GetPosition().ToInt(x, y);
	DrawGraph(x, y, loaded_sprits[0], true);

}

void SampleObject::Finalize()
{
	__super::Finalize();

	// ‰æ‘œ‚Ì”jŠü
	DeleteGraph(loaded_sprite_handle);
	loaded_sprite_handle = 0;
}