#include "MageFire.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <math.h>


#define PI 3.14159265358979323846


void MageFire::Initialize() {
	mFiresExist = false;
}


void MageFire::Finalize() {
	mFiresExist = false;
}


void MageFire::StartFire(const int eneX, const int eneY, const int fireType, const int attackType) {
	// 火の画像の読み込み
	if (fireType == 1) {	// 赤い火の玉
		mFireHandle = EffectGraphics::GetGraHandle(5);
	}
	else {	// 青い火の玉
		mFireHandle = EffectGraphics::GetGraHandle(6);
	}

	// 攻撃の種類を入れる
	mAttackType = attackType;

	// 攻撃の方向をセットする
	if (eneX > 600) {	// 左向きの攻撃
		mDirec = -1;
	}
	else {	// 右向きの攻撃
		mDirec = 1;
	}

	// 火の玉の速度の初期化に使用する，火の玉によって速度が変わるため，この変数を使用する
	float speedRate;
	if (fireType == 1) {	// 赤い火の玉のとき
		speedRate = 1.0f;
	}
	else {	// 青い火の玉のとき
		speedRate = 1.4f;	// 赤い火の玉より1.4倍速
	}

	// 攻撃に合わせた初期化を行う
	if (mAttackType == 1) {	// ジグザグ攻撃
		// 各火の玉のxy座標
		for (int i = 0; i < FIRE_NUM; i++) {
			mXs[i] = eneX + mDirec * 62;
			mYs[i] = eneY - 62;
		}

		// 1フレーム当たりのxy座標の増加量の設定
		mDX = mDirec * speedRate * 6;
		if (eneY < 450) {	// enemyが上側にいたら
			for (int i = 0; i < FIRE_NUM; i++) {
				mDYs[i] = speedRate * (-15);
			}
		}
		else {	// enemyが下側にいたら
			for (int i = 0; i < FIRE_NUM; i++) {
				mDYs[i] = speedRate * 15;
			}
		}
	}
	else {	// 回転攻撃
		// 回転攻撃の円の中心座標
		mCX = eneX;
		mCY = eneY;

		// 回転攻撃の円の中心点から各火の玉の距離（円の半径）
		mRadius = 60.0f;

		// 各火の玉の中心位置からの回転角
		for (int i = 0; i < FIRE_NUM; i++) {
			mThetas[i] = PI * 2 * i / 3;
		}

		// 各火の玉のxy座標
		UpdateRotatedFiresXYs();

		// 1フレーム当たりのx座標や回転角の増加量の設定
		mDX = mDirec * speedRate * 4;
		mDTh = mDirec * speedRate * (float)PI * (float)2/180;
		mDR = speedRate * 0.5f;
	}

	mFrameCnt = 0;
	mFiresExist = true;
}


void MageFire::Update() {
	// 各火の玉が画面外に行ったかを確認する
	bool isAtOutside = true;
	for (int i = 0; i < FIRE_NUM; i++) {
		if (mXs[i] > FIRE_DELETE_LX && mXs[i] < FIRE_DELETE_RX) {	// 1つの火の玉でも画面内にあれば
			isAtOutside = false;
		}
	}

	if (isAtOutside) {	// 1つの火の玉でも画面外に出ていたら 
		Finalize();
	}
	else {
		if (mFrameCnt >= FIRE_FIRST_STOP_FRAME_NUM) {	// 火の玉をプレイヤーに認識させるまでの固定時間後に移動を始める
			Move();
		}

		mFrameCnt++;
	}
}

void MageFire::Draw() {
	// 各火の玉を描画
	for (int i = 0; i < 3; i++) {
		if (mFrameCnt >= FIRES_DISAPPEAR_FRAME_NUMS[i]) {
			DrawGraph((int)mXs[i] - IMG_W / 2, (int)mYs[i] - IMG_H / 2, *mFireHandle, TRUE);
		}
	}
	//DrawGraph(x[0] - sizeX / 2, y[0] - sizeY / 2, fireHandle[0], TRUE);
	//DrawFormatString(700, 500, GetColor(255, 255, 255), "px = %d, ex = %d", x[0] - sizeX /2, y[0] - sizeY / 2);
	//for (int i = 0; i < 3; i++) {
	//	//DrawBox(x[i] - sizeX / 2 + 30, y[i] - sizeY / 2 + 30, x[i] + sizeX / 2 - 30, y[i] + sizeY / 2 - 30, GetColor(0, 0, 0), TRUE);
	//}
}

void MageFire::Move() {
	if (mAttackType == 1) {	// ジグザグ攻撃
		// 各火の玉のxy座標を更新
		//for (int i = 0; i < FIRE_NUM; i++) {
		//	if (mFrameCnt >= FIRES_STOP_FRAME_NUMS[i]) {
		//		if (mYs[i] > SCREEN_BOTTOM_Y || mYs[i] < SCREEN_TOP_Y) {	// 火の玉のy座標が上下のどちらかの端に行ったら
		//			// y軸の進行方向を反転する
		//			mDYs[i] *= -1;
		//		}

		//		// xy座標の更新
		//		mXs[i] += mDX;
		//		mYs[i] += mDYs[i];
		//	}
		//}



		if (mFrameCnt > 60) {
			for (int i = 0; i < 3; i++) {
				if (mYs[i] > SCREEN_BOTTOM_Y || mYs[i] < SCREEN_TOP_Y) {
					mDYs[i] *= -1;
				}

				mXs[i] += mDX;
				mYs[i] += mDYs[i];
			}
		}
		else if (mFrameCnt > 45) {
			for (int i = 0; i < 2; i++) {
				if (mYs[i] > SCREEN_BOTTOM_Y || mYs[i] < SCREEN_TOP_Y) {
					mDYs[i] *= -1;
				}

				mXs[i] += mDX / 3;
				mYs[i] += mDYs[i] / 1.5;
			}
		}
		else {
			if (mYs[0] > SCREEN_BOTTOM_Y || mYs[0] < SCREEN_TOP_Y) {
				mDYs[0] *= -1;
			}

			mXs[0] += mDX / 3;
			mYs[0] += mDYs[0] / 1.5;
		}
	}
	else {	// 回転攻撃
		// それぞれの火の玉の回転角を更新
		for (int i = 0; i < FIRE_NUM; i++) {
			mThetas[i] += mDTh;
		}

		// それぞれの火の玉のxy座標を更新
		UpdateRotatedFiresXYs();

		// 火の玉の回転の円の中心点のx座標と円の半径を更新
		if (mFrameCnt >= FIRES_STOP_FRAME_NUM) {
			mCX += mDX;
			mRadius += mDR;
		}
	}
}


void MageFire::UpdateRotatedFiresXYs() {
	// 数学座標と同じようにするためにy座標値を反転
	// x - cX = 0
	// y = -(mCY + mRadius);
	// cY = -mCY; 
	// -mRadius = y - cY と下でなっていることに注意
	
	// 各火の玉のxy座標を更新
	for (int i = 0; i < FIRE_NUM; i++) {
		mXs[i] = -(-mRadius) * sin(-mThetas[i]) + mCX;
		mYs[i] = ((-mRadius) * cos(-mThetas[i]) + mCY);
	}
}


int MageFire::GetFireNum() const {
	return FIRE_NUM;
}


std::pair<int, int> MageFire::GetFiresHitRange() {
	// 火の玉の当たり判定の範囲
	int hitRangeW = IMG_W / 2 - 30;
	int hitRangeH = IMG_H / 2 - 30;

	return { hitRangeW, hitRangeH };
}


bool MageFire::GetFiresExist() const {
	return mFiresExist;
}


void MageFire::GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys) {
	// 各火の玉のxy座標を入れる
	for (int i = 0; i < FIRE_NUM; i++) {
		xs.at(i) = mXs[i];
		ys.at(i) = mYs[i];
	}
}

