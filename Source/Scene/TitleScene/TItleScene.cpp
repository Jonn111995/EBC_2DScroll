#include "TitleScene.h"
#include "DxLib.h"
namespace {
	const SceneType NEXT_SCENE = SceneType::IN_GAME_SCENE;
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize() {
	title_graphic = LoadGraph("Resources/Images/pipo-bg001.jpg");
}

SceneType TitleScene::Update(float delta_seconds) {

	if (CheckHitKey(KEY_INPUT_RETURN)) {
		return NEXT_SCENE;
	}

	return GetSceneType();
}

void TitleScene::Draw() {
	DrawGraph(0, 0, title_graphic, true);
}

void TitleScene::Finalize() {
	DeleteGraph(title_graphic);
	title_graphic = 0;
}

void TitleScene::DestroyBookDeleteObject()
{
}
