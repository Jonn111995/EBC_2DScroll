#include "GameStateUI.h"
#include "DxLib.h"
#include <stdio.h>
#include "../Source/System/ScreenInfo.h"

GameStateUI::GameStateUI()
	: display_score(0)
	, display_time(0)
	, display_respawn_remain(0)
	, stage_name("")
{
	draw_sort_priority = 1;
}

GameStateUI::~GameStateUI()
{
}

void GameStateUI::Initialize() {
	__super::Initialize();
}

void GameStateUI::Finalize() {
	__super::Finalize();
}

void GameStateUI::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void GameStateUI::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
	
	DrawTime();
	DrawRespawnRemain();
	DrawScore();
}

void GameStateUI::DrawTime() {
	std::to_string(display_time);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_time).c_str(), std::to_string(display_time).size() - 1);
	int color = GetColor(255, 0, 0);
	DrawString(screen_info->GetCenterX() - draw_width / 2, 0, std::to_string(display_time).c_str(), color);
}

void GameStateUI::DrawRespawnRemain() {
	std::to_string(display_respawn_remain);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_respawn_remain).c_str(), std::to_string(display_respawn_remain).size() - 1);
	int color = GetColor(255, 255, 255);
	
	DrawString(screen_info->GetCenterX()+32 - draw_width / 2, 0, std::to_string(display_respawn_remain).c_str(), color);
}

void GameStateUI::DrawScore() {
	std::to_string(display_score);
	ScreenInfo* screen_info = ScreenInfo::GetInstance();

	int draw_width = GetDrawStringWidth(std::to_string(display_score).c_str(), std::to_string(display_score).size() - 1);
	int color = GetColor(0, 255, 0);

	DrawString(screen_info->GetCenterX() + 64 - draw_width / 2, 0, std::to_string(display_score).c_str(), color);
}
