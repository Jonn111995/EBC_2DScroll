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
	__super::Initialize();
	active_state = EActivation::kNONE_ACTIVE;
}

void GameStateUI::Finalize() {
	__super::Finalize();
}

void GameStateUI::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void GameStateUI::Draw(const Vector2D& screen_offset) {

	if (active_state == EActivation::kNONE_ACTIVE) {
		return;
	}

	DrawTime();
	DrawRespawnRemain();
}

//TODO::以下の関数は処理がほとんど同じなので、あとで最適化する
void GameStateUI::DrawTime() {
	std::to_string(display_time);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_time).c_str(), std::to_string(display_time).size() - 1);
	//色を青に指定。
	int color = GetColor(0, 0, 255);
	DrawString(screen_info->GetCenterX() - draw_width / 2, 0, std::to_string(display_time).c_str(), color);
}

void GameStateUI::DrawRespawnRemain() {
	std::to_string(display_respawn_remain);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_respawn_remain).c_str(), std::to_string(display_respawn_remain).size() - 1);
	//色を青に指定。
	int color = GetColor(0, 0, 255);
	DrawString(screen_info->GetCenterX()+32 - draw_width / 2, 0, std::to_string(display_respawn_remain).c_str(), color);
}
