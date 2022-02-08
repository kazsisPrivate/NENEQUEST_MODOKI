#include "ConfigScene.h"
#include "DxLib.h"
#include "SceneMgr.h"


ConfigScene* ConfigScene::mConfigScene;


ConfigScene::ConfigScene(SceneChanger* changer) : BaseScene(changer) {
}


ConfigScene* ConfigScene::GetInstance() {
	if (!ConfigScene::mConfigScene) {
		SceneMgr* sceneMgr = SceneMgr::GetInstance();
		ConfigScene::mConfigScene = new ConfigScene(sceneMgr);
		ConfigScene::mConfigScene->Initialize();
	}

	return ConfigScene::mConfigScene;
}


void ConfigScene::Initialize() {
	mImageHandle = LoadGraph("images/clouds1.png");
}


void ConfigScene::Finalize() {
	delete mConfigScene;
	mConfigScene = NULL;
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