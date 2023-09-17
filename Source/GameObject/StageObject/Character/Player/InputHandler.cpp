#include "InputHandler.h"
#include "DxLib.h"

InputHandler::InputHandler(){
}

InputHandler::~InputHandler(){

}

std::vector<bool> InputHandler::CheckInput(float delta_time) {
  
	return_key_status[kLEFT_B] = CheckLeftButton(delta_time);
	return_key_status[kRIGHT_B] = CheckRightButton(delta_time);
	return_key_status[kJUMP_B] = CheckJumpButton(delta_time);
	return_key_status[kATTACK_B] = CheckAttackButton(delta_time);
	
	std::vector<bool> return_status(std::begin(return_key_status), std::end(return_key_status));
	return return_status;
}

bool InputHandler::CheckKeyKeepingPush(int key, bool& key_status, float delta_time, float& push_time) {
	
	bool bIsPush = CheckHitKey(key) == 1;

	if (bIsPush) {

		key_status = true;

		push_time += delta_time;
		if (push_time > 0.2f) {

			//trueにして処理を実行
			return true;
		}
		return false;
	}

	//ボタンが離されたら
	if (bIsPush == false && key_status == true) {

		push_time = 0.0f;
		key_status = false;
		return false;
	}

	return false;
}

bool InputHandler::CheckMouseKeepingClick(int key, bool& key_status, float delta_time, float& push_time) {
	bool is_push = GetMouseInput() == key;

	if (is_push && !key_status) {

		push_time += delta_time;
		if (push_time < 1.f) {
			key_status = true;
			//trueにして処理を実行
			return true;
		}
	}

	//ボタンが離されたら
	if (!is_push) {

		push_time = 0.0f;
		key_status = false;
		return false;
	}

	return false;
}

bool InputHandler::CheckLeftButton(float time) {
	bool check = CheckHitKey(KEY_INPUT_A) == 1;

	return check == true;
}

bool InputHandler::CheckRightButton(float time) {

	bool check = CheckHitKey(KEY_INPUT_D) == 1;

	return check == true;
}

bool InputHandler::CheckJumpButton(float time) {
	bool check = CheckHitKey(KEY_INPUT_SPACE) == 1;
	bool check_keeping_push = CheckKeyKeepingPush(KEY_INPUT_SPACE, check_key_status[kJUMP_B], time, push_time[kJUMP_B]);
	return check == true && check_keeping_push == false;
}

bool InputHandler::CheckAttackButton(float time) {
	return CheckMouseKeepingClick(MOUSE_INPUT_LEFT, check_key_status[kATTACK_B], time, push_time[kATTACK_B]);//) {
}
