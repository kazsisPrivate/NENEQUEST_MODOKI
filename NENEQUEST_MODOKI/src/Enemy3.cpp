// イノシシ3（hp1, 角突き出し攻撃あり）
#include "Enemy3.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy3::Enemy3(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyBoar(changer, CharaGraphics::GetGraHandle(1, 3), itemIdx, x, y) {
}


void Enemy3::Initialize() {
	EnemyBoar::Initialize();

	// 当たり判定関連の設定
	mImgW = 393, mImgH = 177;
	mHitRangeAW = 60, mHitRangeAH = 35;

	// 攻撃や体力の設定
	mAX = mX - 124, mAY = mY;
	mEneANum = 1;	// 体当たりするだけだから0
	mHp = 1;
}


void Enemy3::Update() {
	if (mHp > 0 && mX >= ENE_BOAR_DELETE_X) {	// 生きていて，画面内にいるときの処理
		// hpの更新
		UpdateHp();

		Walk();

		Attack();

		if (mIsGod) {	// 攻撃を受けた後の無敵時間のとき
			if (mGodFrameCnt == GOD_FRAME_NUM) {	// 無敵時間が終わったら
				mIsGod = false;
				mGodFrameCnt = 0;
			}
			else {	// 無敵時間中なら
				// 無敵時間であることを表す画像にする
				if ((mGodFrameCnt / 20) % 2 == 0) {	// 点滅処理
					mHandleId += 4;
				}

				mGodFrameCnt++;
			}
		}

		mExistingFrameCnt++;
	}
	else {	// 画面外に行くか，死んだときの処理（死んだときは死んだことを認識させるための10フレームの硬直を行う）
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM || mX < ENE_BOAR_DELETE_X) {
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -1000, -1000);	// -1000は適当に画面外の数値にしている
		}

		// ダメージをくらったことがわかる画像にする
		if (mGodFrameCnt == 0) {	// elseの中を最初に通ったときに設定する
			mHandleId += 4;
		}

		mGodFrameCnt++;
	}
}


void Enemy3::Draw() {
	DrawGraph(mX - mImgW / 2 - 72, mY - mImgH / 2, mEneHandle[mHandleId], TRUE);
}


void Enemy3::Attack() {
	// 攻撃の座標の更新
	mAX = mX - 124;
	mAY = mY;

	if (mIsAttacking) {	// 角攻撃中なら
		// 角攻撃の画像にする
		mHandleId += 2;
	}
	else if ((mX > mPlX) && (mX < mPlX + 400)
		&& (mY > mPlY - 100) && (mY < mPlY + 100)) {	// Enemy3がPlayerの近くに近づいたとき
		// 角を伸ばした状態にする
		mIsAttacking = true;
	}
}


void Enemy3::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	(*eneAXYMapVec).at(0)["ax"] = mAX;
	(*eneAXYMapVec).at(0)["ay"] = mAY;
	(*eneAXYMapVec).at(0)["hitRangeAW"] = mHitRangeAW;
	(*eneAXYMapVec).at(0)["hitRangeAH"] = mHitRangeAH;
}