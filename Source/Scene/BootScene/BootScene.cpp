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
		//1�b������������ݐώ��Ԃɖ��t���[���̎��Ԃ𑫂��B
		/*if (boot_count_time < 1.0f) {

			boot_count_time += delta_seconds;
		}*/
		boot_count_time += delta_seconds;
		//1�b�ȏ�ɂȂ�����A�^�C�g�����x���ɑJ�ڂ���B
		if (boot_count_time >= 1.0f) {

			boot_scene_state = EBootSceneState::kEND;
			return NEXT_SCENE;
		}

		//�z��̗v�f�����I�сA�������B�z��w��̕ϐ���float�Ȃ̂ŁAint��cast�B
		use_boot_ = boot_array_[static_cast<int>(boot_array_num_)];

		//�z��w��̕ϐ��̒l��ω�������Bfloat�ɂ��邱�ƂŁA�����̕ω��̑������������ɂ��Ă���B

		boot_array_num_ += 8.0f * delta_seconds;

		//�z��w��̒l��4�𒴂�����A0�ɖ߂��B
		//�������邱�ƂŁA�z��̗v�f�����邮��񂵂Ă����B
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

	//�Q�[�����N���X�̃C���X�^���X���擾
	ScreenInfo* screen_info = ScreenInfo::GetInstance();
	screen_info->Initialize();

	//������̉������擾
	int draw_width = GetDrawStringWidth(use_boot_.c_str(), -1);

	//�������`�ʂ���B
	 //�Q�[����ʂ̉�������A������̉����������āA������Q�Ŋ���B��������ƁA�����񂪐^�񒆂ɂȂ鍶���W���v�Z�o����B
	DrawString((screen_info->GetResolutionX() - draw_width) / 2, screen_info->GetCenterY(), use_boot_.c_str(), GetColor(255, 255, 0));
}

void BootScene::Finalize()
{
}

void BootScene::DestroyBookDeleteObject()
{
}
