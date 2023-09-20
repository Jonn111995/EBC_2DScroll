#include "DxLib.h"

#include "BootScene.h"
#include "../../System/ScreenInfo.h"

namespace {
	const SceneType NEXT_SCENE = SceneType::TITLE_SCENE;
	const float UPDATE_SOEED = 8.f;
	const float FIRST_BOOT_STRING_INDEX = 0.f;
	const char* COMPLETE_BOOT = "READY START!!";
}

BootScene::BootScene()
	: boot_scene_state(EBootSceneState::kPLAYING)
	, boot_array_num(0.f)
	, boot_array{ "Boot   ","Boot.  ","Boot.. ","Boot..." }
	, boot_count_time(0.f)
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
	__super::Update(delta_seconds);

	switch (boot_scene_state) {
	case EBootSceneState::kPLAYING:
		//1�b������������ݐώ��Ԃɖ��t���[���̎��Ԃ𑫂��B
		if (boot_count_time < 1.0f) {
			boot_count_time += delta_seconds;
		}

		UpdateBootAnimation(delta_seconds);

		//1�b�ȏ�ɂȂ�����A�^�C�g�����x���ɑJ�ڂ���B
		if (boot_count_time >= 1.0f) {
			use_boot = COMPLETE_BOOT;
			boot_scene_state = EBootSceneState::kEND;
		}
		break;
	case EBootSceneState::kEND:
		return NEXT_SCENE;
		break;
	}
	return GetSceneType();
}

void BootScene::Draw() {
	__super::Draw();
	//Boot�����̕`��
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	int draw_string_width = GetDrawStringWidth(use_boot.c_str(), -1);

	const int HALF_SIZE = 2;
	 //�Q�[����ʂ̉�������A������̉����������āA������Q�Ŋ���B��������ƁA�����񂪐^�񒆂ɂȂ鍶���W���v�Z�o����B
	DrawString((screen_info->GetResolutionX() - draw_string_width) / HALF_SIZE, screen_info->GetCenterY(), use_boot.c_str(), GetColor(255, 255, 0));
}

void BootScene::Finalize() {
	__super::Finalize();
}

void BootScene::UpdateBootAnimation(const float delta_time) {

	//�z��̗v�f�����I�сA�������B�z��w��̕ϐ���float�Ȃ̂ŁAint��cast�B
	use_boot = boot_array[static_cast<int>(boot_array_num)];

	//�z��w��̕ϐ��̒l��ω�������Bfloat�ɂ��邱�ƂŁA�����̕ω��̑������������ɂ��Ă���B
	boot_array_num += UPDATE_SOEED * delta_time;
	
	if (boot_array_num >= sizeof(boot_array) / sizeof(std::string)) {
		boot_array_num = FIRST_BOOT_STRING_INDEX;
	}
}
