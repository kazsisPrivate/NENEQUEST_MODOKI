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
	// 位置の更新
	mMountain1X -= 1;
	mMountain2X -= 1;
	mClouds1X -= 0.5f;
	mClouds2X -= 0.5f;

	// 山の画像が画面の端に行っていた際の処理
	if (mMountain1X <= END_LEFT_X) {
		mMountain1X = END_RIGHT_X;
		mBackChCnt++;
	}
	else if (mMountain2X <= END_LEFT_X) {
		mMountain2X = END_RIGHT_X;
		mBackChCnt++;
	}

	// 雲の画像が画面の端に行っていた際の処理
	if (mClouds1X <= END_LEFT_X) {
		mClouds1X = END_RIGHT_X;
	}
	else if (mClouds2X <= END_LEFT_X) {
		mClouds2X = END_RIGHT_X;
	}

	// BossStageに移行するかしないかの判定
	/*if (mBackChCnt == 1) {
		mIsBossStage = true;
		PlayerData::SetBossFlag(true);
		EnemyData::SetBossFlag(true);
	}*/
}

void GameBack::UpdateBoss() {
	//if (mUpdFraCnt <= END_RIGHT_X) { //mountainの背景が端から端まで移動し終わるのにかかる時間
	//	if (mUpdFraCnt % UPDATE_FRAME_NUM == 0) {
	//		mClouds1X -= 1;
	//		mClouds2X -= 1;
	//		mBoStX -= 2;

	//		if (mMountain1X == END_RIGHT_X) {//END_LEFT_XからEND_RIGHT_Xに移動されているはずだから
	//			mMountain2X -= 2;
	//		}
	//		else { //mMountain2X == END_RIGHT_X　のとき
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

	//		mUpdFraCnt = END_RIGHT_X; //こうしているとmUpdFraCntは 1281→1282→1281　とループしていくようにできる
	//	}
	//}

	//mUpdFraCnt++;
}