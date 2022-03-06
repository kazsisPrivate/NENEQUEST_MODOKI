#pragma once
/*
* PlayerとEnemyの基底クラス
*/
#include "BasicFunc.h"


class Chara : public BasicFunc { 
protected:
	virtual void Walk() {};	// 移動
	virtual void UpdateHp() {};	// 体力の更新

	int mImgW, mImgH;	// キャラクターの画像の横(width)、縦のサイズ(height)
	int mHandleId;	// 使用している画像のid番号

	int mHp;	// charaのHP, PlayerのHPは6
	int mAttack;	/// charaの攻撃力
	float mSpeed; // charaの移動速度
	int mX, mY;	// charaの中心のx,y座標
	int mHitRangeW, mHitRangeH;	// charaの当たり判定の中心座標からの範囲(width, height)

	bool mIsAttacking;	// 攻撃中ならばtrue
	bool mIsGod;	// ダメージを受けてから，無敵になっているかの判定で使う
	int mGodFrameCnt;	// ダメージを受けた時の点滅描画や無敵時間のカウント等に使う
};