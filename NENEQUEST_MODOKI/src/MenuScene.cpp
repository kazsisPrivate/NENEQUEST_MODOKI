#include "MenuScene.h"
#include "DxLib.h"
#include "SceneMgr.h"


MenuScene* MenuScene::mMenuScene;


MenuScene::MenuScene(SceneChanger* changer) : BaseScene(changer) {
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
	// 選択に使用する三角形の位置の初期設定
	mTriYId = 0;
	mTriY = TRI_YS[mTriYId];

	// 文字の描画に使用するフォントの取得
	mTitleFontHandle = CreateFontToHandle("MS ゴシック", 200, 3, DX_FONTTYPE_EDGE, -1, 4);
	mOptionFontHandle = CreateFontToHandle(NULL, 50, 9);

	// タイトル文字の設定
	mTitleStrs[0] = "NENE QUEST";
	mTitleStrs[1] = "MODOKI";

	// タイトル文字の位置の設定
	int screenW, screenH;
	GetWindowSize(&screenW, &screenH);
	for (int i = 0; i < 2; i++) {
		// x座標は中央寄せの位置に設定する
		mTitleXs[i] = (screenW - GetDrawStringWidthToHandle(mTitleStrs[i].c_str(), mTitleStrs[i].length(), mTitleFontHandle)) / 2;
		mTitleYs[i] = (GetFontSizeToHandle(mTitleFontHandle) + 20) * i;
	}
}


void MenuScene::Finalize() {
	// フォントの削除
	DeleteFontToHandle(mTitleFontHandle);
	DeleteFontToHandle(mOptionFontHandle);

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
	mTriY = TRI_YS[mTriYId];

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
	// タイトル文字の描画
	for (int i = 0; i < 2; i++) {
		DrawStringToHandle(mTitleXs[i], mTitleYs[i], mTitleStrs[i].c_str(), GetColor(255, 102, 0), mTitleFontHandle, GetColor(105, 105, 105));
	}

	// 選択肢の描画
	DrawStringToHandle(450, 500, "ひとりであそぶ", GetColor(0, 0, 0), mOptionFontHandle);
	DrawStringToHandle(450, 565, "そうさほうほう", GetColor(0, 0, 0), mOptionFontHandle);
	DrawStringToHandle(450, 630, "おわる", GetColor(0, 0, 0), mOptionFontHandle);
	DrawTriangle(395, mTriY - 25, 395, mTriY + 25, 430, mTriY, GetColor(0, 0, 0), FALSE);
}