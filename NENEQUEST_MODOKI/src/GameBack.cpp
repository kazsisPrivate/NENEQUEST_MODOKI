#include "DxLib.h"
#include "GameBack.h"


void GameBack::Initialize() {
	// 背景画像の読み込み
	mNorStHandles[0] = LoadGraph("images/normalstage.png");
	mNorStHandles[1] = LoadGraph("images/normalstage.png");
	mCloudHandles[0] = LoadGraph("images/clouds1.jpg");
	mCloudHandles[1] = LoadGraph("images/clouds2.jpg");
	mBsStHandle = LoadGraph("images/bossstage.png");

	// 背景画像の位置
	mNorStXs[0] = 0;
	mNorStXs[1] = BACK_X_MAX;
	mCloudXs[0] = 0;
	mCloudXs[1] = BACK_X_MIN;
	mBsStX = BACK_X_MAX;

	// BossStageに入っているか関連の設定
	mIsChangingSt = false;
	for (int i = 0; i < 2; i++) {
		mIsMovingNorSts[i] = true;
	}
	//mIsMovingBsSt = false;
	mIsAtBsSt = false;	
}


void GameBack::Finalize() {
	// 背景画像の削除
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mNorStHandles[i]);
		DeleteGraph(mCloudHandles[i]);
	}
	DeleteGraph(mBsStHandle);
}


void GameBack::Update() {
	if (!mIsAtBsSt) {	// BossStageでないとき
		UpdateNormalBack();
	}
	else {	// BossStageのとき
		UpdateBossBack();
	}
}


void GameBack::Draw() {
	// 雲の描画
	for (int i = 0; i < 2; i++) {
		DrawGraph(mCloudXs[i], 0, mCloudHandles[i], TRUE);
	}

	//// NormalStageの描画
	//for (int i = 0; i < 2; i++) {
	//	DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
	//}
	/*DrawGraph(mClouds1X, 0, mCl1Handle, TRUE);
	DrawGraph(mClouds2X, 0, mCl2Handle, TRUE);*/
	
	if (mIsChangingSt) {	// BossStageに移行中のとき
		// BossStageの描画
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
		//if (mIsMovingBsSt) {	// BossStageの画像を動かしているとき
		//	DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
		//}
		
		// NormalStageの描画
		for (int i = 0; i < 2; i++) {
			if (mIsMovingNorSts[i]) {	// NormalStageの画像を動かしているとき
				DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
			}
		}
		/*if (mMountain1X != END_LEFT_X && mMountain1X != END_RIGHT_X) {
			DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		}
		else if (mMountain2X != END_LEFT_X && mMountain2X != END_RIGHT_X) {
			DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);
		}*/

	}
	else if (!mIsAtBsSt) {	// NormalStageであるとき（BossStageでないとき）
		// NormalStageの描画
		for (int i = 0; i < 2; i++) {
			DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
		}
		//// 山の描画
		//for (int i = 0; i < 2; i++) {
		//	DrawGraph(mMountainXs[i], 0, mMountainHandles[i], TRUE);
		//}
		/*DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);*/
	}
	else {	// BossStageのとき
		// BossStageの描画
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
	}

	//DrawFormatString(500, 200, GetColor(255, 255, 255), "ys = %d", mBackChCnt);
}


void GameBack::UpdateNormalBack() {
	if (mIsChangingSt) {	// BossStageへの変更中のとき
		// NormalStageと雲の位置の更新
		for (int i = 0; i < 2; i++) {
			if (mIsMovingNorSts[i]) {	// NormalStageの画像を動かしているとき
				mNorStXs[i] -= 1;
			}
			
			mCloudXs[i] -= 0.5f;
		}

		//for (int i = 0; i < 2; i++) {
		//	if (mIsMovingNorSts[i] &&	// NormalStageの画像を動かしているときで
		//		mNorStXs[i] < BACK_X_MAX - BRIDGE_LX && mNorStXs[i] > 0) {	// 画面内で橋が映りこまないとき
		//		// BossStageの画像を動き始めさせる
		//		mIsMovingBsSt = true;
		//		mBsStX = mNorStXs[i];

		//		// NormalStageの画像の動きを止める
		//		mIsMovingNorSts[i] = false;
		//		mNorStXs[i] = BACK_X_MAX;
		//	}
		//}

		// NormalStageの画像が移動範囲の左端に行っていた際の処理
		for (int i = 0; i < 2; i++) {
			if (mNorStXs[i] <= BACK_X_MIN) {
				// NormalStageの画像の動きを止める
				mIsMovingNorSts[i] = false;
				mNorStXs[i] = BACK_X_MAX;
				
				//if (!mIsMovingBsSt) {	// BossStageの画像を動き出させていなければ
				//	mIsMovingBsSt = true;
				//}

				break;
			}
		}

		// 雲の画像が移動範囲の左端に行っていた際の処理
		for (int i = 0; i < 2; i++) {
			if (mCloudXs[i] <= BACK_X_MIN) {
				mCloudXs[i] = BACK_X_MAX;
			}
		}

		// BossStageの位置の更新
		if (mBsStX > 0) {	// 画面の左端にBossStageの画像がいっていなければ(BossStageの背景への移行が終わっていなければ)
			mBsStX -= 1;
		}
		else {	// 画面の左端にBossStageの画像がいっていれば
			// BossStageへの移行を終了する
			//mIsMovingBsSt = false;
			mIsChangingSt = false;
			// BossStageに入ったことにする
			mIsAtBsSt = true;
		}
	}
	else {	// BossStageでなく，BossStageへ変更中でないとき
		// 位置の更新
		for (int i = 0; i < 2; i++) {
			mNorStXs[i] -= 1;
			mCloudXs[i] -= 0.5f;
		}

		// 山の画像が移動範囲の左端に行っていた際の処理
		for (int i = 0; i < 2; i++) {
			if (mNorStXs[i] <= BACK_X_MIN) {
				mNorStXs[i] = BACK_X_MAX;
			}
		}

		// 雲の画像が移動範囲の左端に行っていた際の処理
		for (int i = 0; i < 2; i++) {
			if (mCloudXs[i] <= BACK_X_MIN) {
				mCloudXs[i] = BACK_X_MAX;
			}
		}
	}

	// 位置の更新
	/*mMountain1X -= 1;
	mMountain2X -= 1;
	mClouds1X -= 0.5f;
	mClouds2X -= 0.5f;*/

	// 山の画像が移動範囲の左端に行っていた際の処理
	/*if (mMountain1X <= END_LEFT_X) {
		mMountain1X = END_RIGHT_X;
		mBackChCnt++;
	}
	else if (mMountain2X <= END_LEFT_X) {
		mMountain2X = END_RIGHT_X;
		mBackChCnt++;
	}*/

	// 雲の画像が移動範囲の左端に行っていた際の処理
	/*if (mClouds1X <= END_LEFT_X) {
		mClouds1X = END_RIGHT_X;
	}
	else if (mClouds2X <= END_LEFT_X) {
		mClouds2X = END_RIGHT_X;
	}*/

	// BossStageに移行するかしないかの判定
	/*if (mBackChCnt == 1) {
		mIsBossStage = true;
		PlayerData::SetBossFlag(true);
		EnemyData::SetBossFlag(true);
	}*/
}

void GameBack::UpdateBossBack() {
	// 雲の位置の更新
	for (int i = 0; i < 2; i++) {
		mCloudXs[i] -= 0.5f;
	}

	// 雲の画像が移動範囲の左端に行っていた際の処理
	for (int i = 0; i < 2; i++) {
		if (mCloudXs[i] <= BACK_X_MIN) {
			mCloudXs[i] = BACK_X_MAX;
		}
	}

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


void GameBack::StartChangingSt() {
	// BossStageの背景画像のx座標をセットする
	bool hasSetBsStX = false;	// BossStageの背景画像のx座標をセットしたかどうか
	// NormalStageの背景画像と入れ替えられる位置にNormalStageの背景画像があれば交換する
	for (int i = 0; i < 2; i++) {
		if (mIsMovingNorSts[i] &&	// NormalStageの画像を動かしているときで
			mNorStXs[i] < BACK_X_MAX && mNorStXs[i] > BACK_X_MAX - BRIDGE_LX) {	// 画面内で橋が映りこまないとき
			// BossStageの画像をセットする
			mBsStX = mNorStXs[i];
			hasSetBsStX = true;

			// BossStageといれかえて映す必要のなくなったNormalStageの画像の動きを止める
			mIsMovingNorSts[i] = false;
			mNorStXs[i] = BACK_X_MAX;
		}
	}
	if (!hasSetBsStX) {	// BossStageの画像のx座標をセットしていなかったら
		// 2つのNormalStageの画像右側にある画像の右端のx座標をBossStageのx座標としてセットする
		if (mNorStXs[0] > mNorStXs[1]) {
			mBsStX = mNorStXs[0] + STAGE_IMG_W;
		}
		else {
			mBsStX = mNorStXs[1] + STAGE_IMG_W;
		}
	}

	// BossStageへ移行中を始める
	mIsChangingSt = true;
}


int GameBack::GetBsStX() {
	return mBsStX;
}


bool GameBack::GetIsAtBsSt() {
	return mIsAtBsSt;
}