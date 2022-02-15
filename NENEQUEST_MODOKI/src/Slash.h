#pragma once

#include "BasicFunc.h"
#include <utility>
#include <vector>


class Slash : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartSlash(const int eneX, const int eneY, const int direc, const int attackType);	// 斬撃攻撃を始める際の変数設定
																							// attackType(1: 固定位置の斬撃攻撃，2: 飛ばす斬撃攻撃)
	std::pair<int, int> GetSlashHitRange();	// 火の玉の当たり判定の範囲を返す，Enemy側で把握させるのに使用する
	bool GetSlashExist() const;	// 火の玉が残っているかどうか，3つの火の玉のうち1つでも画面内に残っていればtrueを返す
	std::pair<int, int> GetSlashXY();	// 各火の玉のxy座標を返す，Enemy側で把握させるのに使用する

private:
	void Move();	// 斬撃の移動（飛ばす斬撃攻撃のみで使用）

	int* mSlashHandle;
	int mHandleId;	// 使用している斬撃の画像のid
	int mX, mY;	// 斬撃のxy座標
	int mHitRangeW, mHitRangeH;	// 斬撃の当たり判定
	const int IMG_W = 250, IMG_H = 150;	// 斬撃の画像の大きさ
	int mDirec;	// 攻撃の方向を表す，左向きなら-1，右向きなら1が入っている
	int mAttackType;	// 斬撃の動きのパターン(1: 固定位置の斬撃攻撃，2: 飛ばす斬撃攻撃)
	float mDX;	// x座標の1フレームあたりの増加分（飛ばす斬撃攻撃のみで使用）
	const int SLASH_DELETE_LX = -250;	// この座標まですべての火の玉が移動したとき，自動的に消すようにする(左側)
	const int SLASH_DELETE_RX = 1450;	// この座標まですべての火の玉が移動したとき，自動的に消すようにする(右側)
	bool mSlashExist;	// 斬撃が残っているかどうか，画面内に残っていればtrue
	int mFrameCnt;	// フレーム数のカウント，固定位置の斬撃攻撃の制御のために使用する
	const int SLASH_DELETE_FRAME_NUM = 60;	// このフレーム数を超えたら斬撃を消す（固定位置の斬撃攻撃のみで使用）
};