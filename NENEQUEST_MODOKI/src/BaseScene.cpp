#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(SceneChanger* changer) :
	mImageHandle(0) {
	mSceneChanger = changer;
}

void BaseScene::Finalize() {
	DeleteGraph(mImageHandle);	// ‰æ‘œ‚ğƒƒ‚ƒŠ‚©‚çíœ
	DeleteFontToHandle(mFontHandle);	// ƒtƒHƒ“ƒg‚ğƒƒ‚ƒŠ‚©‚çíœ
}

void BaseScene::Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);	// ‰æ‘œ‚ğ•`‰æ
}