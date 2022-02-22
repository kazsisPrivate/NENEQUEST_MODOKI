#pragma once

// 鎌使い
#include "Enemy.h"
#include "Slash.h"
#include <vector>


class Enemy7 : public Enemy {
public:
	Enemy7(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemyのデータを渡すために使用する

protected:
	//virtual void Walk() override;
	//virtual void Attack();	// 火の玉の攻撃
	virtual void FadeIn();	// 出現時及び，火の玉攻撃の前のフェードイン
	virtual void FadeOut();	// 火の玉攻撃の後のフェードアウト
	virtual void Hide();	// フェードアウトとフェードインの間の姿を隠している時の処理

	Slash* mSlash;
	int mAX, mAY;	// 斬撃のxy座標
	int mHitRangeAW, mHitRangeAH;	// 斬撃の当たり判定範囲
	int mAlphaValue;	// Enemy7の透明度，FadeIn, FadeOutで透けるために使用する
	int DELTA_ALPHA = 9;	// フェードインとフェードアウトの際のα値の1フレーム当たりの増加/減少分
	int mRoutineDoneCnt;	// 動作を終えた回数，特定の回数終わらせた後に自動的に消すようにするために使用する
							// 動作とは，（フェードイン → 火の玉攻撃 → フェードアウト）のセットで1回とカウントする
							// ただし，最初の一回目は，（フェードイン → 一瞬固定立ち → フェードアウト）のセットとする
	int mDeleteRoDoneNum;	// この回数の動作をした後は，自動的に消すようにする
	bool mHasFinishedRos;	// 動作をmDeleteRoDoneNumの数までおわらしたときにtrueとなる
	bool mIsFadingIn;	// フェードインしているときtrue
	bool mIsFadingOut;	// フェードアウトしているときtrue
	bool mIsHiding;	// 動作の間に姿を隠している（消している）ときtrue
	int mHidingFrameCnt;	// フェードインとフェードアウトの間に姿を隠している（消している）フレーム数のカウント
	const int HIDING_FRAME_NUM_MIN = 60;	// 最悪でも個のフレーム数分，フェードインとフェードアウトの間に姿を隠している（消している）
	bool mEne7IsDead;	// mHpが0，かつ消していいとき（死んだことを認識させるための固定時間後など）にtrueになる
	int mAttackFrameCnt;	// 攻撃をしている際（火の玉を出し始めてから）のフレーム数をカウントする，フェードアウトの開始などで使用する
	const int STOP_FRAME_NUM = 150;	// フェードインで入ってきてから固定立ちしている時間（1回目の動作の時のみ使用）
	const int ATTACK_STATE_FRAME_NUM = 60;	// 攻撃をしてから（火の玉を出し始めてから），フェードアウトを始めるまでのフレーム数（2回目以降の動作の時使用）
	int mAttackDirec;	// 斬撃攻撃の放つ方向（-1: 左向き，1: 右向き）
	int mAttackType;	// 斬撃攻撃の種類（1: 固定位置の斬撃攻撃，2: 飛ばす斬撃攻撃）
};

