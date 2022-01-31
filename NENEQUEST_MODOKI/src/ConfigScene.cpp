#include "ConfigScene.h"
#include "DxLib.h"

ConfigScene::ConfigScene(SceneChanger* changer) : BaseScene(changer) {
}

void ConfigScene::Initialize() {
	mImageHandle = LoadGraph("images/clouds1.png");
}

void ConfigScene::Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		mSceneChanger->ChangeScene(eSceneMenu);
	}
}

void ConfigScene::Draw() {
	BaseScene::Draw();
	DrawString(0, 0, "設定画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}