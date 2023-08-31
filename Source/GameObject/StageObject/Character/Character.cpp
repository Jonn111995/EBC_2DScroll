#include "Character.h"
#include "DxLib.h"
#include "Interface/CharacterEventInterface.h"

void Character::Update(float delta_time) {
	//移動ベクトル。下方向
	

}

void Character::Draw(const Vector2D& screen_offset)
{
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

	unsigned int color = GetColor(255, 0, 0);
	int x2 = x + body_collision.center_position.x - body_collision.box_extent.x;
	int y2 = y + body_collision.center_position.y - body_collision.box_extent.y;

	//デバック用
	DrawBox(x2, y2, x2 + body_collision.box_extent.x * 2, y2 + body_collision.box_extent.y * 2, color, false);
}

void Character::GiveDamage(Character& target)
{
}

void Character::GetDamage(Character& opponent, const int damage)
{
}
