#include "GameState.h"

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::Initialize() {
	__super::Initialize();
}

void GameState::Finalize() {
	__super::Finalize();
}

void GameState::Update(float delta_seconds) {
	__super::Update(delta_seconds);

}

void GameState::SetScore(const int now_score) {
	score = now_score;
}

int GameState::GetScore() const {
	return score;
}

void GameState::SetRespawnRemain(const int respawn_remain) {
	this->respawn_remain = respawn_remain;
}

int GameState::GetRespawnRemain() {
	return respawn_remain;
}

int GameState::GetRemainTime() const {
	return remain_time;
}

void GameState::SetStageName(const std::string new_stage_name) {
	stage_name = new_stage_name;
}

std::string GameState::GetStageName() const {
	return stage_name;
}

void GameState::SetbIsClear(const bool is_clear) {
	this->is_clear = is_clear;
}

bool GameState::GetbIsClear() const {
	return is_clear;
}
