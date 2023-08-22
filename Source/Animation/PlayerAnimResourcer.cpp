#include "PlayerAnimResourcer.h"
#include "DxLib.h"

void PlayerAnimResourcer::Initialize() {

	LoadDivGraph(_T("Resources/Images/collon_wait.bmp"), 4, 4, 1, 128, 128, loaded_sprite_wait);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), 8, 4, 2, 128, 128, loaded_sprite_run);
	LoadDivGraph(_T("Resources/Images/collon_jump.bmp"), 6, 4, 2, 128, 128, loaded_sprite_jump);
	LoadDivGraph(_T("Resources/Images/collon_attack.bmp"), 3, 3, 1, 128, 128, loaded_sprite_attack);
}

void PlayerAnimResourcer::Finalize() {

	for (auto& handle : loaded_sprite_wait) {
		DeleteGraph(handle);
		handle = 0;
	}

	for (auto& handle : loaded_sprite_run) {
		DeleteGraph(handle);
		handle = 0;
	}

	for (auto& handle : loaded_sprite_jump) {
		DeleteGraph(handle);
		handle = 0;
	}
	for (auto& handle : loaded_sprite_attack) {
		DeleteGraph(handle);
		handle = 0;
	}
}

std::vector<int> PlayerAnimResourcer::GetAnimaitonHandle(EPlayerState now_state) {

	int array_size = 0;
	std::vector<int> return_animation;
	int* head_anim_array = GetAnimationHandleHelper(now_state, array_size);

	array_size = array_size / sizeof(*head_anim_array);
	return_animation.assign(head_anim_array, head_anim_array + array_size);
	return return_animation;
}

void PlayerAnimResourcer::DeleteHandleArray(int handle_array[]) {

}

int* PlayerAnimResourcer::GetAnimationHandleHelper(EPlayerState now_state, int& out_array_size)
{
	switch (now_state) {
	case kIDLE:
		
		out_array_size = sizeof(loaded_sprite_wait);
		return loaded_sprite_wait;
		break;
	case kWALK:
	case kRUN:
		out_array_size = sizeof(loaded_sprite_run);
		return loaded_sprite_run;
		break;
	case kATTACK:
		out_array_size = sizeof(loaded_sprite_attack);
		return loaded_sprite_attack;
		break;
	case kJUMP:
		out_array_size = sizeof(loaded_sprite_jump);
		return loaded_sprite_jump;
		break;
	}
}