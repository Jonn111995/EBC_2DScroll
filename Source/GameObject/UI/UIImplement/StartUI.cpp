#include "StartUI.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include "../Interface/IUIEvent.h"

namespace {
	const char* START = "START!!";
}

StartUI::StartUI()
{
}

StartUI::~StartUI()
{
}

void StartUI::Initialize()
{
}

void StartUI::Finalize()
{
}

void StartUI::Update(float delta_seconds) {
	switch (game_object_state) {
	case EGameObjectState::kPLAYING:

		switch (ui_state) {
		case EUIState::kSHOW:

			display_count_time += delta_seconds;

			if (display_count_time >= DISPLAY_TIME) {

				display_count_time = 0.0f;

				//UI�I�����������s����B
				ui_event->FInishUI(this);

				ui_state = EUIState::kHIDE;
			}
			break;
		case EUIState::kHIDE:
			break;
		default:
			break;
		}

		break;
	case EGameObjectState::kPAUSE:
		break;
	case EGameObjectState::kEND:
		break;
	}
}

void StartUI::Draw(const Vector2D& screen_offset) {

	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	int FontHandle = CreateFontToHandle(NULL, 32, 10);
	int draw_width = GetDrawFormatStringWidthToHandle(FontHandle, START);
	int x_top = screen_info->GetCenterX() - (draw_width / 2);
	int y_left = screen_info->GetCenterY();
	DrawBox(x_top -(draw_width / 4), y_left, x_top + draw_width + draw_width/4, y_left + 32, GetColor(255, 255, 255), true);
	DrawStringToHandle(screen_info->GetCenterX() - (draw_width / 2), screen_info->GetCenterY(), START, GetColor(255, 0, 0), FontHandle);
}