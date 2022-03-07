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
	// Player�̉摜�̎擾
	mPlHandle = CharaGraphics::GetGraHandle(0, 1);

	// Enemy�̉摜�̎擾
	mEneHandles[0] = CharaGraphics::GetGraHandle(1, 1);
	mEneHandles[1] = CharaGraphics::GetGraHandle(1, 4);

	// ����̉摜�̎擾
	mWeaHandles[0] = ItemGraphics::GetGraHandle(8);
	mWeaHandles[1] = ItemGraphics::GetGraHandle(11);

	// Item�̉摜�̎擾
	mIteHandles[0] = ItemGraphics::GetGraHandle(1);
	mIteHandles[1] = ItemGraphics::GetGraHandle(5);
	mIteHandles[2] = ItemGraphics::GetGraHandle(7);

	// ItemBox�̉摜�̎擾
	mIteBHandles[0] = ItemGraphics::GetGraHandle(12);
	mIteBHandles[1] = ItemGraphics::GetGraHandle(14);

	// �t�H���g�̎擾
	mExpStrFontHandles[0] = CreateFontToHandle("MS �S�V�b�N", 40, 2, DX_FONTTYPE_EDGE, -1, 4);
	mExpStrFontHandles[1] = CreateFontToHandle("MS �S�V�b�N", 30, 1, -1);
	mEscStrFontHandle = CreateFontToHandle("HG�n�p�p�S�V�b�NUB �W��", 30, 1, -1);

	// ���ꂼ��̉摜��xy���W�̐ݒ�
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
	// �t�H���g�̍폜
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
	// Player�̉摜�̕`��
	DrawGraph(mPlX, mPlY, mPlHandle[0], TRUE);

	// Enemy�̉摜����ѐ����̕`��
	DrawStringToHandle(400, 100, "�o�Ă���G���Ȃ��|��", GetColor(204, 0, 51), mExpStrFontHandles[0], GetColor(105, 105, 105));
	DrawStringToHandle(300, 150, "�Ō�ɑ҂�������{�X��|���I", GetColor(204, 0, 51), mExpStrFontHandles[0], GetColor(105, 105, 105));
	for (int i = 0; i < 2; i++) {
		DrawGraph(mEneXs[i], mEneYs[i], mEneHandles[i][0], TRUE);
	}

	// ����̉摜����ѐ����̕`��
	for (int i = 0; i < 2; i++) {
		DrawGraph(mWeaXs[i], mWeaYs[i], *mWeaHandles[i], TRUE);
	}
	DrawFormatStringToHandle(220, 310, GetColor(0, 0, 0), mExpStrFontHandles[1], "A�L�[: �W�����v");
	DrawFormatStringToHandle(220, 350, GetColor(0, 0, 0), mExpStrFontHandles[1], "S�L�[: �U��");
	DrawFormatStringToHandle(220, 390, GetColor(0, 0, 0), mExpStrFontHandles[1], "(�|��S�L�[: �ߋ����U��");
	DrawFormatStringToHandle(220, 430, GetColor(0, 0, 0), mExpStrFontHandles[1], "D�L�[: �������U��)");

	// Item�̉摜����ѐ����̕`��
	for (int i = 0; i < 3; i++) {
		DrawGraph(mIteXs[i], mIteYs[i], *mIteHandles[i], TRUE);
	}
	DrawFormatStringToHandle(850, 350, GetColor(0, 0, 0), mExpStrFontHandles[1], "�M���󂷂�");
	DrawFormatStringToHandle(800, 390, GetColor(0, 0, 0), mExpStrFontHandles[1], "�A�C�e�����o�Ă���");

	// ItemBox�̉摜����ѐ����̕`��
	for (int i = 0; i < 2; i++) {
		DrawGraph(mIteBXs[i], mIteBYs[i], mIteBHandles[i][0], TRUE);
	}
	DrawFormatStringToHandle(600, 520, GetColor(0, 0, 0), mExpStrFontHandles[1], "�����󂷂�");
	DrawFormatStringToHandle(570, 560, GetColor(0, 0, 0), mExpStrFontHandles[1], "���킪�o�Ă���");

	DrawFormatStringToHandle(380, 660, GetColor(0, 51, 102), mEscStrFontHandle, "���j���[��ʂɖ߂�iEsc�L�[�������j");
}