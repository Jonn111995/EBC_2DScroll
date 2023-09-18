#include "DxLib.h"

#include "TitleScene.h"
#include "../Source/System/SoundManager.h"
#include "../Source/System/ScreenInfo.h"

namespace {
	const SceneType NEXT_SCENE = SceneType::IN_GAME_SCENE;
	const char* TITLE = "GO!! RUN!! COLLON";
	const char* START_EXPLAIN = "Start To Push Enter Key";
}

TitleScene::TitleScene()
	: title_graphic(0)
	, title_bgm(0)
	, decide_sound(0)
	, title_font(0)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize() {
	__super::Initialize();
	SoundManager* sound_manager = SoundManager::GetInstance();

	title_graphic = LoadGraph("Resources/Images/pipo-bg001.jpg");
	decide_sound = sound_manager->LoadSoundResource("Resources/Sounds/SE/decide03.mp3");
	title_bgm = sound_manager->LoadSoundResource("Resources/Sounds/BGM/Pops_05.mp3");
	title_font = CreateFontToHandle(NULL, 32, 10);

	sound_manager->PlayLoadSound(title_bgm, true);
}

SceneType TitleScene::Update(float delta_seconds) {
	
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SoundManager* sound_manager = SoundManager::GetInstance();
		sound_manager->PlayLoadSound(decide_sound);
		return NEXT_SCENE;
	}
	return GetSceneType();
}

void TitleScene::Draw() {
	__super::Draw();
	const int HALF = 2;
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	//背景を描画
	DrawGraph(screen_info->GetLeftX(), screen_info->GetLeftY(), title_graphic, true);

	//タイトル文字を描画
	int draw_width = GetDrawFormatStringWidthToHandle(title_font, TITLE);
	int x_top = screen_info->GetCenterX() - (draw_width / HALF);
	int y_left = screen_info->GetCenterY();
	DrawBox(x_top - (draw_width / 4), y_left, x_top + draw_width + draw_width / 4, y_left + 32, GetColor(255, 255, 255), true);
	DrawStringToHandle(x_top, y_left, TITLE, GetColor(255, 0, 0), title_font);

	//"Start To Push Enter Key"を描画
	draw_width = GetDrawStringWidth(START_EXPLAIN, strlen(START_EXPLAIN));
	x_top = screen_info->GetCenterX() - (draw_width / HALF);
	DrawString(x_top, y_left + 48, START_EXPLAIN, GetColor(0, 0, 0));
}

void TitleScene::Finalize() {
	__super::Finalize();
	//タイトル画面からは必ずステージの1-1から。
	//TODO::セレクト画面とか入れたら変更予定
	inherit_info.stage_id = EStageID::kSTAGE_1_1;
	inherit_info.respawn_remain = 3;

	SoundManager* sound_manager = SoundManager::GetInstance();
	sound_manager->StopSound(title_bgm);
	sound_manager->UnLoadSoundResource(title_bgm);

	DeleteGraph(title_graphic);
	DeleteFontToHandle(title_font);

	title_font = 0;
	title_graphic = 0;
	title_bgm = 0;
}