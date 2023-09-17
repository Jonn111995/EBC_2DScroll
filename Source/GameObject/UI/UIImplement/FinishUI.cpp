#include "FinishUI.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include "../Interface/IUIEvent.h"

namespace {
	const char* FINISH = "Finish";
}

FinishUI::FinishUI()
	: display_string("")
{
	draw_sort_priority = 1;
}

FinishUI::~FinishUI()
{
}

void FinishUI::Initialize() {
	font_handle = CreateFontToHandle(NULL, 32, 10);
}

void FinishUI::Finalize() {
	DeleteFontToHandle(font_handle);
}

void FinishUI::Update(float delta_seconds) {
	switch (game_object_state) {
	case EGameObjectState::kPLAYING:

		switch (ui_state) {
		case EUIState::kSHOW:

			display_count_time += delta_seconds;

			if (display_count_time >= DISPLAY_TIME) {

				display_count_time = 0.0f;

				//UII—¹ˆ—‚ðŽÀs‚·‚éB
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

void FinishUI::Draw(const Vector2D& screen_offset) {

	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	int draw_width = GetDrawFormatStringWidthToHandle(font_handle, display_string);
	int x_top = screen_info->GetCenterX() - (draw_width / 2);
	int y_left = screen_info->GetCenterY();
	DrawBox(x_top - (draw_width / 4), y_left, x_top + draw_width + draw_width / 4, y_left + 32, GetColor(255, 255, 255), true);
	DrawStringToHandle(screen_info->GetCenterX() - (draw_width / 2), screen_info->GetCenterY(), display_string, GetColor(255, 0, 0), font_handle);
}
