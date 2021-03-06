#include "Arrow.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include "EffectGraphics.h"
#include <math.h>

#define PI 3.14159265358979323846


void Arrow::Initialize() {
	// 弓矢が存在していない状態に初期化
	mArrowExists = false;

	// 弓矢の画像や当たったときのエフェクト画像の取得
	mHitEffectHandle = EffectGraphics::GetGraHandle(4);
}


void Arrow::Finalize() {
	mArrowExists = false;
	mAExistingFrameCnt = 0;
}


void Arrow::StartArrow(const int x, const int y, const int type) {
	// 位置
	mXCenter = x;
	mYCenter = y;
	// 弓矢の種類
	mType = type;

	// 弓矢が存在しているかどうかの設定
	mArrowExists = true;

	// 弓矢の当たったときに使用する変数
	mIsHit = false;
	mHitFrameCnt = 0;

	// 弓矢の種類に対応した値の設定
	if (mType == 1 || mType == 3) {	// 右向き
		mArrowHandle = ItemGraphics::GetGraHandle(15);
		mDX = 20;
		
		if (mType == 1) {	// 弱い弓矢
			mDTh = 2.0f;
			mTheta = -PI * (10 / (float)180);
			mDYFirst = 10;
		}
		else {	// 強い弓矢
			mDTh = 1.5f;
			mTheta = -PI * (50 / (float)180);
			mDYFirst = 20;
		}
	}
	else {	// 左向き
		mArrowHandle = ItemGraphics::GetGraHandle(16);
		mDX = -20;

		if (mType == 2) {	// 弱い弓矢
			mDTh = -2.0f;
			mTheta = PI * (40 / (float)180);
			mDYFirst = 10;
		}
		else {	// 強い弓矢
			mDTh = -1.5f;
			mTheta = PI * (50 / (float)180);
			mDYFirst = 20;
		}
	}

	// 弓矢の動きに使用する変数の設定
	mIsMoving = true;
	mYStart = mYCenter;
	mYPrev = mYCenter;
	mYCenter = mYCenter - mDYFirst;
}


void Arrow::Update() {
	if (mIsHit) {
		if (mHitFrameCnt == 20) {	// 当たってから20フレーム後
			Finalize();	// 弓矢（当たったエフェクト）を消す
		}

		mHitFrameCnt++;
	}
	else if (mAExistingFrameCnt == 80) {	// 放ってから80フレーム後
		Finalize();	// 弓矢を消す
	}

	if (mIsHit) {	// 弓矢が何かに当たれば動きを止める
		mIsMoving = false;
	}

	if (mIsMoving) {	// 弓矢が動いているとき（何にもあたっていないとき）
		Move();
	}

	mAExistingFrameCnt++;
}


void Arrow::Draw() {
	if (mIsHit) {	// 何かにあたったとき
		// 当たったエフェクトの画像の描画
		DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, *mHitEffectHandle, TRUE);
	}
	else {
		// 弓矢の描画
		DrawRotaGraph(mXCenter, mYCenter, 1, mTheta, *mArrowHandle, TRUE);
	}
}

void Arrow::Move() {
	// x座標の更新
	mXCenter += mDX;

	// y座標の更新
	int yTemp = mYCenter;
	mYCenter += (mYCenter - mYPrev) + 1;
	mYPrev = yTemp;

	if (mYCenter >= mYStart + 80) {		// 特定の位置まで下がるれば動きを止める
		mIsMoving = false;
	}
	
	// 回転角の更新
	mTheta += PI * (mDTh / (float)180);
	
	if (mType == 1 || mType == 3) {	// 右向きのとき
		mX = mXCenter + (36 * cos(-mTheta));
		mY = mYCenter - (36 * sin(-mTheta));
	}
	else {	// 左向きのとき
		mX = mXCenter - 36 * cos(mTheta);
		mY = mYCenter - 36 * sin(mTheta);
	}
}


bool Arrow::GetIsMoving() const {
	return mIsMoving;
}


bool Arrow::GetArrowExists() const {
	return mArrowExists;
}


std::tuple<int, int> Arrow::GetArrowXY() {
	return { mXCenter, mYCenter };
}


void Arrow::SetIsHit(const bool isHit) {
	mIsHit = isHit;
}