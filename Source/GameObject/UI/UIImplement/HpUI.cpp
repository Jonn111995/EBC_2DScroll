#include "HpUI.h"
#include "../Source/System/ScreenInfo.h"
#include "DxLib.h"
#include <string>
#include <algorithm>

HpUI::HpUI()
	: display_hp(0)
	, display_width(100)
	, hp_guage(0)
	
{
}

HpUI::~HpUI()
{
}

void HpUI::Initialize()
{
}

void HpUI::Finalize()
{
}

void HpUI::Update(float delta_seconds)
{
}

void HpUI::Draw(const Vector2D& screen_offset) {
	if (active_state == EActivation::kNONE_ACTIVE) {
		return;
	}

	int green = 255;
	int red = 0;
	int blue = 0;

	if (display_hp <= max_hp / 2) {
		red = 255;
	}

	if (display_hp <= (max_hp / 4)) {
		green = 0;
	}

	std::to_string(display_hp);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_hp).c_str(), std::to_string(display_hp).size() - 1);
	//F‚ðÂ‚ÉŽw’èB
	DrawString(screen_info->GetLeftX(), 128, std::to_string(display_hp).c_str(), GetColor(0, 0, 255));

	DrawBox(screen_info->GetLeftX(), screen_info->GetLeftY() + 32 + 128, screen_info->GetLeftX() + display_width, 128 + 48, GetColor(255, 255, 255), false);
	DrawBox(screen_info->GetLeftX(), screen_info->GetLeftY() + 32+128, screen_info->GetLeftX() + hp_guage, 128+48, GetColor(red, green, blue), true);
	
}

void HpUI::InitializeHP(const int initial_hp) {
	display_hp = initial_hp;
	max_hp = initial_hp;
	hp_guage = max_hp;
}

void HpUI::SetHP(const int new_hp) {
	display_hp = new_hp;
	hp_guage = display_width * display_hp / max_hp;
}
