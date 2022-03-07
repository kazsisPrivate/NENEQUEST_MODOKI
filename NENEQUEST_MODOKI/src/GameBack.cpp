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
	mIsAtBsSt = false;

	mStrFontHandle = CreateFontToHandle("MS ゴシック", 60, 1, -1);
}


void GameBack::Finalize() {
	// 背景画像の削除
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mNorStHandles[i]);
		DeleteGraph(mCloudHandles[i]);
	}
	DeleteGraph(mBsStHandle);

	// フォントの削除
	DeleteFontToHandle(mStrFontHandle);
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
	
	if (mIsChangingSt) {	// BossStageに移行中のとき
		// BossStageの描画
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
		
		// NormalStageの描画
		for (int i = 0; i < 2; i++) {
			if (mIsMovingNorSts[i]) {	// NormalStageの画像を動かしているとき
				DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
			}
		}

		// BossStageへ移行中なことを表すための文字の描画
		DrawFormatStringToHandle(300, 200, GetColor(255, 0, 0), mStrFontHandle, "!BossStage!");
	}
	else if (!mIsAtBsSt) {	// NormalStageであるとき（BossStageでないとき）
		// NormalStageの描画
		for (int i = 0; i < 2; i++) {
			DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
		}
	}
	else {	// BossStageのとき
		// BossStageの描画
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
	}
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

		// NormalStageの画像が移動範囲の左端に行っていた際の処理
		for (int i = 0; i < 2; i++) {
			if (mNorStXs[i] <= BACK_X_MIN) {
				// NormalStageの画像の動きを止める
				mIsMovingNorSts[i] = false;
				mNorStXs[i] = BACK_X_MAX;

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