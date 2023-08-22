#pragma once
#include <vector>
#include"../Source/GameObject/StageObject/Character/Player/EPlayerState.h"

class PlayerAnimResourcer {

private:
	int loaded_sprite_wait[4];
	int loaded_sprite_run[8];
	int loaded_sprite_jump[6];
	int loaded_sprite_attack[3];

public:
	void Initialize();
	void Finalize();
	std::vector<int> GetAnimaitonHandle(EPlayerState now_state);
private:
	void DeleteHandleArray(int handle_array[]);
	int* GetAnimationHandleHelper(EPlayerState now_state, int& out_array_size);

};

