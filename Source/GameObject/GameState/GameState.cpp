#include "GameState.h"
#include "DxLib.h"
#include "Interface/IGameStateEvent.h"
#include "../Source/Utility/Vector2D.h"

namespace {
	const int RESPAWN_REMAIN_APP = 1;
	const float INFORM_TIME = 1.f;
	const float TIME_UP = 0.f;

	const char* INFORM_UP_RESPAEN_RMAIN = "Respawn Remain UP!!!";
}

GameState::GameState()
	: score(0)
	, respawn_remain(3)
	, start_time(0)
	, count_time(0.f)
	, remain_time(0)
	, stage_name("")
	, is_clear(false)
	, game_state_event(nullptr)
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

	switch (game_object_state) {
	case EGameObjectState::kPRE_START:
		//ゲーム開始前は処理しない
		break;
	case EGameObjectState::kPLAYING:
		start_time -= delta_seconds;

		if (is_inform_respawn_remain_up) {
			inform_count_time += delta_seconds;
			inform_movement -= plus;

			if (inform_count_time >= INFORM_TIME) {
				inform_count_time = 0.f;
				is_inform_respawn_remain_up = false;
			}
		}

		if (start_time <= TIME_UP) {
			//ゲームオーバー処理を呼ぶ
			game_state_event->TimeOver();
		}
		else {
			remain_time = static_cast<int>(start_time);
			//残り時間をUIに渡す
			game_state_event->UpdateTimeUI(remain_time);
		}
		break;
	case EGameObjectState::kPAUSE:
		break;
	case EGameObjectState::kEND:
		break;
	}
}

void GameState::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
	if (is_inform_respawn_remain_up) {
		unsigned int color = GetColor(255, 255, 255);
		int str_length = strlen(INFORM_UP_RESPAEN_RMAIN);
		int draw_width = GetDrawStringWidth(INFORM_UP_RESPAEN_RMAIN, str_length);

		Vector2D inform_position;
		game_state_event->GetDrawInformPositon(inform_position);
		DrawFormatString(inform_position.x -screen_offset.x - (draw_width/2), static_cast<float>(inform_position.y - screen_offset.y + inform_movement), color, INFORM_UP_RESPAEN_RMAIN);
	}
}

void GameState::SetScore(const int now_score) {
	score = now_score;
}

int GameState::GetScore() const {
	return score;
}

void GameState::IncreaseScore() {
	score++;
	game_state_event->UpdateScoreUI(score);

	//一定単位毎に残機を増やす
	if (score % RESPAWN_REMAIN_APP == 0) {
		is_inform_respawn_remain_up = true;
		IncreseRespawnRemain();
	}
}

void GameState::SetRespawnRemain(const int respawn_remain) {
	this->respawn_remain = respawn_remain;
}

int GameState::GetRespawnRemain() {
	return respawn_remain;
}

void GameState::IncreseRespawnRemain() {
	respawn_remain++;
	game_state_event->UpdateRespawnRemainUI(respawn_remain);
}

void GameState::ReduceRespawnRemain() {
	respawn_remain--;
	if (respawn_remain <= 0) {
		respawn_remain = 0;
	}
	game_state_event->UpdateRespawnRemainUI(respawn_remain);
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
