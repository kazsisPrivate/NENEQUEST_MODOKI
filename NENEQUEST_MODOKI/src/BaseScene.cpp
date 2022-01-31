#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(SceneChanger* changer) :
	mImageHandle(0) {
	mSceneChanger = changer;
}

void BaseScene::Finalize() {
	DeleteGraph(mImageHandle);	// 画像をメモリから削除
	DeleteFontToHandle(mFontHandle);	// フォントをメモリから削除
}

void BaseScene::Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);	// 画像を描画
}