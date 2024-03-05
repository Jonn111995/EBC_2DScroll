#include "HpUI.h"
#include "../Source/System/ScreenInfo.h"
#include "DxLib.h"
#include <string>
#include <algorithm>

HpUI::HpUI()
	: display_hp(0)
	, hp_guage_width(100)
	, hp_guage(0)
{
	draw_sort_priority = 1;
}

HpUI::~HpUI()
{
}

void HpUI::Initialize() {
	__super::Initialize();
}

void HpUI::Finalize() {
	__super::Finalize();
}

void HpUI::Update(float delta_seconds) {
	__super::Update(delta_seconds);
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

	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	//HPの数値
	std::to_string(display_hp);
	int draw_width = GetDrawStringWidth(std::to_string(display_hp).c_str(), std::to_string(display_hp).size() - 1);
	
	//HPバーの囲い
	DrawBox(screen_info->GetLeftX()+5, screen_info->GetLeftY() +9, screen_info->GetLeftX() + hp_guage_width +1, 25, GetColor(255, 255, 255), false);
	DrawBox(screen_info->GetLeftX()+4, screen_info->GetLeftY()+10, screen_info->GetLeftX() + hp_guage_width, 24, GetColor(0, 0, 0), true);
	//HPバーの中身
	DrawBox(screen_info->GetLeftX()+4, screen_info->GetLeftY()+10, screen_info->GetLeftX() + hp_guage, 24, GetColor(red, green, blue), true);
	
}

void HpUI::InitializeHP(const int initial_hp) {
	display_hp = initial_hp;
	max_hp = initial_hp;
	hp_guage = initial_hp;
}

void HpUI::SetHP(const int new_hp) {
	display_hp = new_hp;
	hp_guage = hp_guage_width * display_hp / max_hp;
}
