#pragma once

#include "BasicFunc.h"

class Chara : public BasicFunc { 
public:
	virtual void Walk() {};	// 移動
	virtual void Jump() {};	// ジャンプ
	virtual void Attack() {};	// 攻撃
	virtual void UpdateSAP() {};	// 移動速度と攻撃力の更新
	virtual void UpdateHit() {};	// 当たり判定の更新

protected:
	int mHp;	// charaのHP, PlayerのHPは6
	int mAttack;	/// charaの攻撃力
	float mSpeed; // charaの移動速度
	int mX, mY;	// charaの中心のx,y座標
	int mAX, mAY;	// charaの攻撃の中心のxy座標
	int mImgW, mImgH;	// charaHandle[]の画像の横(width)、縦のサイズ(height)
	int mHitRangeW, mHitRangeH;	// charaの当たり判定の中心座標からの範囲(width, height)
	int mHitRangeAW, mHitRangeAH; //charaの攻撃の当たり判定の中心座標からの範囲(width, height)
	long long mFrameCnt; //時間の経過を計る
	//int ix, iy;
	int mHandleId;	// charaHandle[]の[]の番号
	int mAFrameCnt;	// 攻撃したあと，次に攻撃できるようになるまでのインターバルとして使用する
	int mYStart, mYPrev;	// ジャンプ処理で使用する。以前のy座標を表す
	int mGodFrameCnt;	// ダメージを受けた時の点滅描画や無敵時間のカウント等に使う
	bool mIsJumping;	// ジャンプ中ならばtrue
	bool mIsAttacking;	// 攻撃中ならばtrue
	bool mIsGod;	// ダメージを受けてから，無敵になっているかの判定で使う
	bool mIsDead;	// mHpが0，かつ消していいとき（死んだことを認識させるための固定時間後など）にtrueになる
};