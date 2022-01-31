#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(SceneChanger* changer) :
	mImageHandle(0) {
	mSceneChanger = changer;
}

void BaseScene::Finalize() {
	DeleteGraph(mImageHandle);	// �摜������������폜
	DeleteFontToHandle(mFontHandle);	// �t�H���g������������폜
}

void BaseScene::Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);	// �摜��`��
}