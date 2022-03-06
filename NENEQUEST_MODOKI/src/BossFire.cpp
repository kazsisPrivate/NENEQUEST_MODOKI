#include "BossFire.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <random>
#include <vector>
#include <algorithm>


void BossFire::Initialize() {
	mFiresExist = false;
}


void BossFire::Finalize() {
	mFiresExist = false;
}


void BossFire::StartFire(const int bossX, const int bossY, const int fireType, const int attackType) {
	// 攻撃の種類を入れる
	mAttackType = attackType;

	// EnemyBossの口の位置を入れる
	mBossMouthX = bossX - 212;
	mBossMouthY = bossY - 130;
	
	if (mAttackType == 1) {	// 火の玉吐き出し攻撃
		// 火の画像の読み込み
		if (fireType == 1) {	// 赤い火の玉
			mFireHandle = EffectGraphics::GetGraHandle(8);
		}
		else {	// 青い火の玉
			mFireHandle = EffectGraphics::GetGraHandle(9);
		}
		// 画像サイズの設定
		mImgW = 208, mImgH = 208;
		// 画像idの設定
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mBallHandleIds[i] = 0;
		}

		// 各火の玉の位置の初期化
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			// EnemyBossの口の位置に初期化
			mXs[i] = mBossMouthX;
			mYs[i] = mBossMouthY;
		}

		// 火の玉の速度の初期化に使用する，火の玉によって速度が変わるため，この変数を使用する
		float speedRate;
		if (fireType == 1) {	// 赤い火の玉のとき
			speedRate = 1.0f;
		}
		else {	// 青い火の玉のとき
			speedRate = 1.5f;	// 赤い火の玉より1.5倍速
		}

		// 各火の玉の速度を設定
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mDXs[i] = -1.5 * speedRate;
			mDYs[i] = 3 * speedRate;
		}

		// 火の玉の当たり判定を設定
		mBallHitRangeW = 36, mBallHitRangeH = 36;

		// それぞれの火の玉を吐き出すフレーム数の設定
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mFireBallFrameNums[i] = (60 + 120 * i) / speedRate;
		}

		// 各火の玉の横移動を始めるy座標の設定
		std::vector<int> ballYs{ 300, 450, 600 };
		std::random_device rnd;
		std::shuffle(ballYs.begin(), ballYs.end(), rnd);
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mFireBallYs[i] = ballYs.at(i);
		}
	}
	else {	// ブレス攻撃
		// 火の画像の読み込み
		if (fireType == 1) {	// 赤い火の玉
			mFireHandle = EffectGraphics::GetGraHandle(10);
		}
		else {	// 青い火の玉
			mFireHandle = EffectGraphics::GetGraHandle(11);
		}
		// 画像サイズの設定
		mImgW = 104, mImgH = 104;

		// 各火の玉の位置の初期化
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			// EnemyBossの口の位置に初期化
			mXs[i] = mBossMouthX;
			mYs[i] = mBossMouthY;
		}

		// 各火の玉の加速度の設定
		int tmpNum = 0;
		int itrNum = BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM;
		for (int i = 0; i < itrNum; i++) {
			tmpNum += i + 1;
		}
		mDDX = 300 / (BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM);// (float)tmpNum;	// 250はEnemyBossの口からでた火の玉が消えるまでのx座標の移動量
		mDDY = -230 / (float)tmpNum;	// 230はEnemyBossの口からでた火の玉が消えるまでのy座標の移動量

		// 各火の玉の移動速度の初期化
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mDXs[i] = -mDDX;// *BREATHING_NEW_FIRE_FRAME_NUM* FIRE_BREATH_NUM;
			mDYs[i] = -mDDY * BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM;
		}

		// 各火の玉の拡大率の初期化
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mFireExpRates[i] = 0;
		}

		// 各火の玉の当たり判定を設定
		mOrigHitRangeW = 18, mOrigHitRangeH = 18;
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mBreathHitRangeWs[i] = 0;
			mBreathHitRangeHs[i] = 0;
		}

		// 各火の玉を吐いているかどうかの初期化
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mBreIsExistings[i] = false;
		}

		// 吐き出し始める火の玉のidの設定
		mNextBreathId = 0;
	}

	mFrameCnt = 0;
	mFiresExist = true;
}


void BossFire::Update() {
	if (mAttackType == 1) {	// 火の玉吐き出し攻撃
		FireBall();
	}
	else {	// ブレス攻撃
		FireBreath();
	}

	mFrameCnt++;
}


void BossFire::Draw() {
	if (mAttackType == 1) {	// 火の玉吐き出し攻撃
		// 各火の玉の描画
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			if (mFrameCnt >= mFireBallFrameNums[i]) {	// 火の玉を吐き出し始めていたら
				DrawGraph((int)mXs[i] - mImgW / 2, (int)mYs[i] - mImgH / 2, mFireHandle[mBallHandleIds[i]], TRUE);
				DrawBox((int)mXs[i] - mBallHitRangeW, (int)mYs[i] - mBallHitRangeH,
					(int)mXs[i] + mBallHitRangeW, (int)mYs[i] + mBallHitRangeH, GetColor(255, 0, 0), FALSE);
			}
		}
	}
	else {	// ブレス攻撃
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			if (mBreIsExistings[i]) {	// 火の玉が存在していたら
				DrawRotaGraph((int)mXs[i], (int)mYs[i], (double)mFireExpRates[i], 0, *mFireHandle, TRUE);
				DrawBox((int)(mXs[i] - mBreathHitRangeWs[i]), (int)(mYs[i] - mBreathHitRangeHs[i]),
					(int)(mXs[i] + mBreathHitRangeWs[i]), (int)(mYs[i] + mBreathHitRangeHs[i]), GetColor(255, 0, 0), FALSE);
			}
		}
	}
}


void BossFire::FireBall() {
	// 各火の玉が画面外に行ったかを確認する
	bool isAtOutside = true;
	for (int i = 0; i < FIRE_BALL_NUM; i++) {
		if (mXs[i] > FIRE_DELETE_LX) {	// 1つの火の玉でも画面内にあれば
			isAtOutside = false;
		}
	}

	if (isAtOutside) {	// 1つの火の玉でも画面外に出ていたら 
		Finalize();
	}
	else {
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			if (mFrameCnt >= mFireBallFrameNums[i]) {	 // 火の玉の吐き出させ始めるフレーム数を超えていたら
				// xy座標の更新をする
				mXs[i] += mDXs[i];
				mYs[i] += mDYs[i];

				if (mDYs[i] != 0 &&	// 横移動を始めていなくて
					mYs[i] >= mFireBallYs[i]) {	// 横移動を始める座標を超えていたら
					// 横移動を始めさせる
					mDXs[i] *= 2;
					mDYs[i] = 0;
					mBallHandleIds[i] = 1;
				}
			}
		}
	}
}


void BossFire::FireBreath() {
	if (mFrameCnt > PREPARING_BRE_FRAME_NUM) {	// 火の玉を吐き出し始めるフレーム数を超えているとき
		if (mFrameCnt % BREATHING_NEW_FIRE_FRAME_NUM == 0) {	// 新しく火の玉を吐き出し始めるフレーム数だったら
			// 火の玉をEnemyBossの口元の座標にする（戻す）
			mXs[mNextBreathId] = mBossMouthX;
			mYs[mNextBreathId] = mBossMouthY;

			// 拡大率を0にする（戻す）
			mFireExpRates[mNextBreathId] = 0;

			// 火の玉の移動速度を設定する（戻す）
			mDXs[mNextBreathId] = -mDDX;// *BREATHING_NEW_FIRE_FRAME_NUM* FIRE_BREATH_NUM;
			mDYs[mNextBreathId] = 26;

			if (mFrameCnt >= BREATHING_FRAME_NUM) {	// 火の玉を吐き出し終えるフレーム数を超えていたら
				// 火を消す
				mBreIsExistings[mNextBreathId] = false;
			}
			else {
				// 火を出す
				mBreIsExistings[mNextBreathId] = true;
			}

			mNextBreathId = (mNextBreathId + 1) % FIRE_BREATH_NUM;
		}
	}

	for (int i = 0; i < FIRE_BREATH_NUM; i++) {
		if (mBreIsExistings[i]) {
			// 座標と拡大率を更新する
			mXs[i] += mDXs[i];
			mYs[i] = CalcBreathY(mXs[i]);// mDYs[i];
			mFireExpRates[i] += 0.06f;

			// 当たり判定の範囲を更新する
			mBreathHitRangeWs[i] = mOrigHitRangeW * mFireExpRates[i];
			mBreathHitRangeHs[i] = mOrigHitRangeH * mFireExpRates[i];

			// x, yの増加量を更新する
			//mDXs[i] += mDDX;
			mDYs[i] += 0.5f;
		}
	}

	if (mFrameCnt >= BREATHING_FRAME_NUM) {	// 火の玉を吐き出し終えるフレーム数を超えているとき
		// 火の玉をすべて消し終わっているかどうか確認する
		bool hasDeleted = true;
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			if (mBreIsExistings[i]) {	// 1つでも火を消し終わっていなかったら
				hasDeleted = false;
			}
		}

		if (hasDeleted) {	// すべての火の玉を消し終わっていたら
			Finalize();
		}
	}
}


float BossFire::CalcBreathY(const float x) {
	/*float y = -260 / (float)90000 * 
		std::pow(x - mBossMouthX + 300, 2) + 530;*/
	float y = 520 / (1 + exp(0.02 * (x - mBossMouthX))) + 10;
	// y = (260 * 2) / (1 + exp(0.05 * (x - mBossMouthX))) + (270 - 260)

	return y;
}


int BossFire::GetFireNum(const int attackType) const {
	if (attackType == 1) {	// 火の玉吐き出し攻撃
		return FIRE_BALL_NUM;
	}
	else {	// ブレス攻撃
		return FIRE_BREATH_NUM;
	}
}


bool BossFire::GetFiresExist() const {
	return mFiresExist;
}


void BossFire::GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys) {
	// 各火の玉のxy座標を入れる
	if (mAttackType == 1) {	// 火の玉吐き出し攻撃のとき
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			xs.at(i) = mXs[i];
			ys.at(i) = mYs[i];
		}
	}
	else {
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {	// ブレス攻撃のとき
			xs.at(i) = mXs[i];
			ys.at(i) = mYs[i];
		}
	}
}


void BossFire::GetFiresHitRangeWHs(std::vector<int>& hitRangeWs, std::vector<int>& hitRangeHs) {
	// 各火の玉のxy座標を入れる
	if (mAttackType == 1) {	// 火の玉吐き出し攻撃のとき
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			hitRangeWs.at(i) = mBallHitRangeW;
			hitRangeHs.at(i) = mBallHitRangeH;
		}
	}
	else {
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {	// ブレス攻撃のとき
			hitRangeWs.at(i) = mBreathHitRangeWs[i];
			hitRangeHs.at(i) = mBreathHitRangeHs[i];
		}
	}
}