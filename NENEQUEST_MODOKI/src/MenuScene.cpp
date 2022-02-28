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
	// �I���Ɏg�p����O�p�`�̈ʒu�̏����ݒ�
	mTriYId = 0;
	mTriY = TRI_YS[mTriYId];

	// �����̕`��Ɏg�p����t�H���g�̎擾
	mTitleFontHandle = CreateFontToHandle("MS �S�V�b�N", 200, 3, DX_FONTTYPE_EDGE, -1, 4);
	mOptionFontHandle = CreateFontToHandle(NULL, 50, 9);

	// �^�C�g�������̐ݒ�
	mTitleStrs[0] = "NENE QUEST";
	mTitleStrs[1] = "MODOKI";

	// �^�C�g�������̈ʒu�̐ݒ�
	int screenW, screenH;
	GetWindowSize(&screenW, &screenH);
	for (int i = 0; i < 2; i++) {
		// x���W�͒����񂹂̈ʒu�ɐݒ肷��
		mTitleXs[i] = (screenW - GetDrawStringWidthToHandle(mTitleStrs[i].c_str(), mTitleStrs[i].length(), mTitleFontHandle)) / 2;
		mTitleYs[i] = (GetFontSizeToHandle(mTitleFontHandle) + 20) * i;
	}
}


void MenuScene::Finalize() {
	// �t�H���g�̍폜
	DeleteFontToHandle(mTitleFontHandle);
	DeleteFontToHandle(mOptionFontHandle);

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
	mTriY = TRI_YS[mTriYId];

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
	// �^�C�g�������̕`��
	for (int i = 0; i < 2; i++) {
		DrawStringToHandle(mTitleXs[i], mTitleYs[i], mTitleStrs[i].c_str(), GetColor(255, 102, 0), mTitleFontHandle, GetColor(105, 105, 105));
	}

	// �I�����̕`��
	DrawStringToHandle(450, 500, "�ЂƂ�ł�����", GetColor(0, 0, 0), mOptionFontHandle);
	DrawStringToHandle(450, 565, "�������ق��ق�", GetColor(0, 0, 0), mOptionFontHandle);
	DrawStringToHandle(450, 630, "�����", GetColor(0, 0, 0), mOptionFontHandle);
	DrawTriangle(395, mTriY - 25, 395, mTriY + 25, 430, mTriY, GetColor(0, 0, 0), FALSE);
}