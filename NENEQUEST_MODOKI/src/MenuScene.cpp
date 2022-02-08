#include "MenuScene.h"
#include "DxLib.h"
#include "SceneMgr.h"


MenuScene* MenuScene::mMenuScene;


MenuScene::MenuScene(SceneChanger* changer) : BaseScene(changer) {
	// 選択に使用する三角形の位置の初期設定
	mTriYId = 0;
	mTriY = mTriYs[mTriYId];
}


MenuScene* MenuScene::GetInstance() {
	if (!MenuScene::mMenuScene) {
		SceneMgr* sceneMgr = SceneMgr::GetInstance();
		MenuScene::mMenuScene = new MenuScene(sceneMgr);
		MenuScene::mMenuScene->Initialize();
	}

	return MenuScene::mMenuScene;
}


void MenuScene::Initialize() {
	mImageHandle = 0;
	mFontHandle = CreateFontToHandle(NULL, 50, 9);
}


void MenuScene::Finalize() {
	delete mMenuScene;
	mMenuScene = NULL;
}


void MenuScene::Update() {
	// 入力キーを取得
	gpUpdateKey();

	// 選択に使用する三角形の座標変更
	if (key[KEY_INPUT_UP] == 1) mTriYId += 2;
	if (key[KEY_INPUT_DOWN] == 1) mTriYId += 1;
	mTriYId %= 3;
	mTriY = mTriYs[mTriYId];

	// 選択後の処理
	if (key[KEY_INPUT_RETURN] == 1) {
		if (mTriYId == 0) {
			mSceneChanger->ChangeScene(eSceneGame);
		}
		else if (mTriYId == 1) {
			mSceneChanger->ChangeScene(eSceneConfig);
		}
		else {
			DxLib_End();
		}
	}
}


void MenuScene::Draw() {
	BaseScene::Draw();
	DrawStringToHandle(450, 500, "ひとりであそぶ", GetColor(0, 0, 0), mFontHandle);
	DrawStringToHandle(450, 565, "そうさほうほう", GetColor(0, 0, 0), mFontHandle);
	DrawStringToHandle(450, 630, "おわる", GetColor(0, 0, 0), mFontHandle);
	DrawTriangle(395, mTriY - 25, 395, mTriY + 25, 430, mTriY, GetColor(0, 0, 0), FALSE);
}