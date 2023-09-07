#include "GameState.h"

namespace {
	const float TIME_UP = 0.f;
}

GameState::GameState()
	: score(0)
	, respawn_remain(0)
	, start_time(0)
	, count_time(0.f)
	, remain_time(0)
	, stage_name("")
	, is_clear(false)
{
}

GameState::~GameState()
{
}

void GameState::Initialize() {
	__super::Initialize();

	//仮
	start_time = 60;
}

void GameState::Finalize() {
	__super::Finalize();
}

void GameState::Update(float delta_seconds) {
	__super::Update(delta_seconds);

	start_time -= delta_seconds;

	if (start_time <= TIME_UP) {

		//ゲームオーバー処理を呼ぶ
	}
	else {
		remain_time = static_cast<int>(start_time);
		//残り時間をUIに渡す
	}
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
