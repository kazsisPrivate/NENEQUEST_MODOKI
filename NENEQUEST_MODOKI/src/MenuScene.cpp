#include "MenuScene.h"
#include "DxLib.h"
#include "SceneMgr.h"


MenuScene* MenuScene::mMenuScene;


MenuScene::MenuScene(SceneChanger* changer) : BaseScene(changer) {
	// �I���Ɏg�p����O�p�`�̈ʒu�̏����ݒ�
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
	// ���̓L�[���擾
	gpUpdateKey();

	// �I���Ɏg�p����O�p�`�̍��W�ύX
	if (key[KEY_INPUT_UP] == 1) mTriYId += 2;
	if (key[KEY_INPUT_DOWN] == 1) mTriYId += 1;
	mTriYId %= 3;
	mTriY = mTriYs[mTriYId];

	// �I����̏���
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
	DrawStringToHandle(450, 500, "�ЂƂ�ł�����", GetColor(0, 0, 0), mFontHandle);
	DrawStringToHandle(450, 565, "�������ق��ق�", GetColor(0, 0, 0), mFontHandle);
	DrawStringToHandle(450, 630, "�����", GetColor(0, 0, 0), mFontHandle);
	DrawTriangle(395, mTriY - 25, 395, mTriY + 25, 430, mTriY, GetColor(0, 0, 0), FALSE);
}