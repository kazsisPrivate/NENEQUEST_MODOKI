#include "ConfigScene.h"
#include "DxLib.h"
#include "SceneMgr.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"


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
	// Playerの画像の取得
	mPlHandle = CharaGraphics::GetGraHandle(0, 1);

	// Enemyの画像の取得
	mEneHandles[0] = CharaGraphics::GetGraHandle(1, 1);
	mEneHandles[1] = CharaGraphics::GetGraHandle(1, 4);

	// 武器の画像の取得
	mWeaHandles[0] = ItemGraphics::GetGraHandle(8);
	mWeaHandles[1] = ItemGraphics::GetGraHandle(11);

	// Itemの画像の取得
	mIteHandles[0] = ItemGraphics::GetGraHandle(1);
	mIteHandles[1] = ItemGraphics::GetGraHandle(5);
	mIteHandles[2] = ItemGraphics::GetGraHandle(7);

	// ItemBoxの画像の取得
	mIteBHandles[0] = ItemGraphics::GetGraHandle(12);
	mIteBHandles[1] = ItemGraphics::GetGraHandle(14);

	// フォントの取得
	mExpStrFontHandles[0] = CreateFontToHandle("MS ゴシック", 40, 2, DX_FONTTYPE_EDGE, -1, 4);
	mExpStrFontHandles[1] = CreateFontToHandle("MS ゴシック", 30, 1, -1);
	mEscStrFontHandle = CreateFontToHandle("HG創英角ゴシックUB 標準", 30, 1, -1);

	// それぞれの画像のxy座標の設定
	mPlX = -80, mPlY = 10;
	mEneXs[0] = 1000, mEneYs[0] = 100;
	mEneXs[1] = 1100, mEneYs[1] = 70;
	mWeaXs[0] = 0, mWeaYs[0] = 280;
	mWeaXs[1] = 80, mWeaYs[1] = 330;
	mIteXs[0] = 1120, mIteYs[0] = 310;
	mIteXs[1] = 1050, mIteYs[1] = 380;
	mIteXs[2] = 1150, mIteYs[2] = 380;
	mIteBXs[0] = 650, mIteBYs[0] = 310;
	mIteBXs[1] = 400, mIteBYs[1] = 480;
}


void ConfigScene::Finalize() {
	// フォントの削除
	DeleteFontToHandle(mExpStrFontHandles[0]);
	DeleteFontToHandle(mExpStrFontHandles[1]);
	DeleteFontToHandle(mEscStrFontHandle);

	delete mConfigScene;
	mConfigScene = NULL;
}


void ConfigScene::Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		mSceneChanger->ChangeScene(eSceneMenu);
	}
}


void ConfigScene::Draw() {
	// Playerの画像の描画
	DrawGraph(mPlX, mPlY, mPlHandle[0], TRUE);

	// Enemyの画像および説明の描画
	DrawStringToHandle(400, 100, "出てくる敵をなぎ倒し", GetColor(204, 0, 51), mExpStrFontHandles[0], GetColor(105, 105, 105));
	DrawStringToHandle(300, 150, "最後に待ちうけるボスを倒せ！", GetColor(204, 0, 51), mExpStrFontHandles[0], GetColor(105, 105, 105));
	for (int i = 0; i < 2; i++) {
		DrawGraph(mEneXs[i], mEneYs[i], mEneHandles[i][0], TRUE);
	}

	// 武器の画像および説明の描画
	for (int i = 0; i < 2; i++) {
		DrawGraph(mWeaXs[i], mWeaYs[i], *mWeaHandles[i], TRUE);
	}
	DrawFormatStringToHandle(220, 310, GetColor(0, 0, 0), mExpStrFontHandles[1], "Aキー: ジャンプ");
	DrawFormatStringToHandle(220, 350, GetColor(0, 0, 0), mExpStrFontHandles[1], "Sキー: 攻撃");
	DrawFormatStringToHandle(220, 390, GetColor(0, 0, 0), mExpStrFontHandles[1], "(弓はSキー: 近距離攻撃");
	DrawFormatStringToHandle(220, 430, GetColor(0, 0, 0), mExpStrFontHandles[1], "Dキー: 遠距離攻撃)");

	// Itemの画像および説明の描画
	for (int i = 0; i < 3; i++) {
		DrawGraph(mIteXs[i], mIteYs[i], *mIteHandles[i], TRUE);
	}
	DrawFormatStringToHandle(850, 350, GetColor(0, 0, 0), mExpStrFontHandles[1], "樽を壊すと");
	DrawFormatStringToHandle(800, 390, GetColor(0, 0, 0), mExpStrFontHandles[1], "アイテムが出てくる");

	// ItemBoxの画像および説明の描画
	for (int i = 0; i < 2; i++) {
		DrawGraph(mIteBXs[i], mIteBYs[i], mIteBHandles[i][0], TRUE);
	}
	DrawFormatStringToHandle(600, 520, GetColor(0, 0, 0), mExpStrFontHandles[1], "箱を壊すと");
	DrawFormatStringToHandle(570, 560, GetColor(0, 0, 0), mExpStrFontHandles[1], "武器が出てくる");

	DrawFormatStringToHandle(380, 660, GetColor(0, 51, 102), mEscStrFontHandle, "メニュー画面に戻る（Escキーを押す）");
}