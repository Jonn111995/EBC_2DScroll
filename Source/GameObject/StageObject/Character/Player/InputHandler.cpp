#include "InputHandler.h"
#include "DxLib.h"

EButton InputHandler::CheckInput(float delta_time) {
   
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		return EButton::kLEFT_B;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		return EButton::kRIGHT_B;
	}
	else if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		return EButton::kJUMP_B;
	}

	else if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		return EButton::kATTACK_B;
	}
}
