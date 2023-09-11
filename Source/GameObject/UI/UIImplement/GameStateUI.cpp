#include "GameStateUI.h"
#include "DxLib.h"
#include <stdio.h>
#include "../Source/System/ScreenInfo.h"

GameStateUI::GameStateUI()
{
}

GameStateUI::~GameStateUI()
{
}

void GameStateUI::Initialize() {
	active_state = EActivation::kNONE_ACTIVE;
}

void GameStateUI::Finalize() {
}

void GameStateUI::Update(float delta_seconds)
{
}

void GameStateUI::Draw(const Vector2D& screen_offset) {

	if (active_state == EActivation::kNONE_ACTIVE) {
		return;
	}
	std::to_string(display_time);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	
	int draw_width = GetDrawStringWidth(std::to_string(display_time).c_str(), std::to_string(display_time).size()-1);
	//F‚ðÂ‚ÉŽw’èB
	int color = GetColor(0, 0, 255);
	DrawString(screen_info->GetCenterX() - draw_width / 2, 0, std::to_string(display_time).c_str(), color);	
}
