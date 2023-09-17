#include "BootScene.h"
#include "DxLib.h"
#include "../../System/ScreenInfo.h"

BootScene::BootScene()
	: boot_scene_state(EBootSceneState::kPLAYING)
{
}

BootScene::~BootScene()
{
}

void BootScene::Initialize() {
	__super::Initialize();
	inherit_info.score = 0;
	inherit_info.respawn_remain = 0;
	inherit_info.stage_name = "";
	inherit_info.stage_id = EStageID::kNONE;
}

SceneType BootScene::Update(float delta_seconds) {
	switch (boot_scene_state) {
	case EBootSceneState::kPLAYING:
		//1秒未満だったら累積時間に毎フレームの時間を足す。
		/*if (boot_count_time < 1.0f) {

			boot_count_time += delta_seconds;
		}*/
		boot_count_time += delta_seconds;
		//1秒以上になったら、タイトルレベルに遷移する。
		if (boot_count_time >= 1.0f) {

			boot_scene_state = EBootSceneState::kEND;
			return NEXT_SCENE;
		}

		//配列の要素から一つ選び、代入する。配列指定の変数がfloatなので、intにcast。
		use_boot_ = boot_array_[static_cast<int>(boot_array_num_)];

		//配列指定の変数の値を変化させる。floatにすることで、文字の変化の速さをゆっくりにしている。

		boot_array_num_ += 8.0f * delta_seconds;

		//配列指定の値が4を超えたら、0に戻す。
		//そうすることで、配列の要素をぐるぐる回していく。
		if (boot_array_num_ >= 4.0f) {
			boot_array_num_ = 0.0f;
		}

		return GetSceneType();

	case EBootSceneState::kEND:
		break;
	}
	return GetSceneType();
}

void BootScene::Draw() {
	ScreenInfo::CreateInstance();

	//ゲーム情報クラスのインスタンスを取得
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	//文字列の横幅を取得
	int draw_width = GetDrawStringWidth(use_boot_.c_str(), -1);

	//文字列を描写する。
	 //ゲーム画面の横幅から、文字列の横幅を引いて、それを２で割る。そうすると、文字列が真ん中になる左座標が計算出来る。
	DrawString((screen_info->GetResolutionX() - draw_width) / 2, screen_info->GetCenterY(), use_boot_.c_str(), GetColor(255, 255, 0));
}

void BootScene::Finalize()
{
}

void BootScene::DestroyBookDeleteObject()
{
}
