#include "DxLib.h"
#include "GameBack.h"
//#include "PlayerData.h"
//#include "EnemyData.h"

GameBack::GameBack() : mMountain1X(0), mMountain2X(END_RIGHT_X), mClouds1X(0), mClouds2X(END_RIGHT_X), mBoStX(END_RIGHT_X), mUpdFraCnt(1), mBackChCnt(0), mIsBossStage(false) {
	//PlayerData::SetBossFlag(false);
}


void GameBack::Initialize() {
	mMo1Handle = LoadGraph("images/mountain.png");
	mMo2Handle = LoadGraph("images/mountain.png");
	mCl1Handle = LoadGraph("images/clouds1.jpg");
	mCl2Handle = LoadGraph("images/clouds2.jpg");
	mBoStHandle = LoadGraph("images/bossMountain.png");
}


void GameBack::Finalize() {
	DeleteGraph(mMo1Handle);
	DeleteGraph(mMo2Handle);
	DeleteGraph(mCl1Handle);
	DeleteGraph(mCl2Handle);
	DeleteGraph(mBoStHandle);
}


void GameBack::Update() {
	if (mIsBossStage == false) {
		UpdateNormal();
	}
	else {
		UpdateBoss();
	}
}


void GameBack::Draw() {
	DrawGraph(mClouds1X, 0, mCl1Handle, TRUE);
	DrawGraph(mClouds2X, 0, mCl2Handle, TRUE);
	if (mIsBossStage == false) {
		DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);
	}
	else {
		DrawGraph(mBoStX, 0, mBoStHandle, TRUE);

		if (mMountain1X != END_LEFT_X && mMountain1X != END_RIGHT_X) {
			DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		}
		else if (mMountain2X != END_LEFT_X && mMountain2X != END_RIGHT_X) {
			DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);
		}

	}

	DrawFormatString(500, 200, GetColor(255, 255, 255), "ys = %d", mBackChCnt);
}

void GameBack::UpdateNormal() {
	// �ʒu�̍X�V
	mMountain1X -= 1;
	mMountain2X -= 1;
	mClouds1X -= 0.5f;
	mClouds2X -= 0.5f;

	// �R�̉摜����ʂ̒[�ɍs���Ă����ۂ̏���
	if (mMountain1X <= END_LEFT_X) {
		mMountain1X = END_RIGHT_X;
		mBackChCnt++;
	}
	else if (mMountain2X <= END_LEFT_X) {
		mMountain2X = END_RIGHT_X;
		mBackChCnt++;
	}

	// �_�̉摜����ʂ̒[�ɍs���Ă����ۂ̏���
	if (mClouds1X <= END_LEFT_X) {
		mClouds1X = END_RIGHT_X;
	}
	else if (mClouds2X <= END_LEFT_X) {
		mClouds2X = END_RIGHT_X;
	}

	// BossStage�Ɉڍs���邩���Ȃ����̔���
	/*if (mBackChCnt == 1) {
		mIsBossStage = true;
		PlayerData::SetBossFlag(true);
		EnemyData::SetBossFlag(true);
	}*/
}

void GameBack::UpdateBoss() {
	//if (mUpdFraCnt <= END_RIGHT_X) { //mountain�̔w�i���[����[�܂ňړ����I���̂ɂ����鎞��
	//	if (mUpdFraCnt % UPDATE_FRAME_NUM == 0) {
	//		mClouds1X -= 1;
	//		mClouds2X -= 1;
	//		mBoStX -= 2;

	//		if (mMountain1X == END_RIGHT_X) {//END_LEFT_X����END_RIGHT_X�Ɉړ�����Ă���͂�������
	//			mMountain2X -= 2;
	//		}
	//		else { //mMountain2X == END_RIGHT_X�@�̂Ƃ�
	//			mMountain1X -= 2;
	//		}

	//		if (mClouds1X == END_LEFT_X) {
	//			mClouds1X = END_RIGHT_X;
	//		}
	//		else if (mClouds2X == END_LEFT_X) {
	//			mClouds2X = END_RIGHT_X;
	//		}
	//	}
	//}
	//else {
	//	if (mUpdFraCnt % UPDATE_FRAME_NUM == 0) {
	//		mClouds1X -= 1;
	//		mClouds2X -= 1;

	//		if (mClouds1X == END_LEFT_X) {
	//			mClouds1X = END_RIGHT_X;
	//		}
	//		else if (mClouds2X == END_LEFT_X) {
	//			mClouds2X = END_RIGHT_X;
	//		}

	//		mUpdFraCnt = END_RIGHT_X; //�������Ă����mUpdFraCnt�� 1281��1282��1281�@�ƃ��[�v���Ă����悤�ɂł���
	//	}
	//}

	//mUpdFraCnt++;
}