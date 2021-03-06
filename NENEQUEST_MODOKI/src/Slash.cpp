#include "Slash.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <math.h>


#define PI 3.14159265358979323846


void Slash::Initialize() {
	mSlashExist = false;
}


void Slash::Finalize() {
	mSlashExist = false;
}


void Slash::StartSlash(const int eneX, const int eneY, const int direc, const int attackType) {
	// 斬撃画像の読み込み
	mSlashHandle = EffectGraphics::GetGraHandle(7);

	// 攻撃の種類を入れる
	mAttackType = attackType;

	// 攻撃の方向をセットする
	mDirec = direc;	// 右向きなら1, 左向きなら-1

	// 攻撃に合わせた初期化を行う
	if (mAttackType == 1) {	// 固定位置の斬撃攻撃
		// 斬撃のxy座標
		mX = eneX + mDirec * 100;
		mY = eneY;

		// 斬撃の当たり判定
		mHitRangeW = 63;
		mHitRangeH = 50;

		// 斬撃の画像id
		mHandleId = 1 + mDirec * 0.5;	// 左向きなら0が入り，右向きなら1が入る
	}
	else {	// 回転攻撃
		// 斬撃のxy座標
		mX = eneX + mDirec * 100;
		mY = eneY;

		// 斬撃の当たり判定
		mHitRangeW = 63;
		mHitRangeH = 50;

		// 斬撃のx座標の増加分
		mDX = mDirec * 40;

		// 斬撃の画像id
		mHandleId = 3 + mDirec * 0.5;	// 左向きなら0が入り，右向きなら1が入る
	}

	mFrameCnt = 0;
	mSlashExist = true;
}


void Slash::Update() {
	if (mAttackType == 1) {	// 固定位置の斬撃攻撃のとき
		if (mFrameCnt == SLASH_DELETE_FRAME_NUM) {	// 特定のフレーム数になったら
			Finalize();
		}
		else {
			mFrameCnt++;
		}
	}
	else {	// 飛ばす斬撃攻撃のとき
		if (mX < SLASH_DELETE_LX || mX > SLASH_DELETE_RX) {	// 斬撃が画面外に出ていたら 
			Finalize();
		}
		else {
			Move();

			mFrameCnt++;
		}
	}
}


void Slash::Draw() {
	DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mSlashHandle[mHandleId], TRUE);
}


void Slash::Move() {
	mX += mDX;
}


std::pair<int, int> Slash::GetSlashHitRange() {
	return { mHitRangeW, mHitRangeH };
}


bool Slash::GetSlashExist() const {
	return mSlashExist;
}


std::pair<int, int> Slash::GetSlashXY() {
	return { mX, mY };
}
