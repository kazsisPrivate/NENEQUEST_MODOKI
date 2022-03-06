#pragma once
/*
* 魔法使いの敵（Enemy4～6）の基底クラス
*/
#include "Enemy.h"
#include "MageFire.h"
#include <vector>


class EnemyMage : public Enemy {
public:
	EnemyMage(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemyのデータを渡すために使用する

protected:
	virtual void Walk() override;
	virtual void FadeIn();	// 出現時及び，火の玉攻撃の前のフェードイン
	virtual void FadeOut();	// 火の玉攻撃の後のフェードアウト
	virtual void Hide();	// フェードアウトとフェードインの間の姿を隠している時の処理

	MageFire* mMageFire;
	int mFireType;	// 使用する火の玉の種類（1: 赤い火の玉（速度普通），2: 青い火の玉（速度速い））
	int mFireNum;	// 使用する火の玉の数（MageFireクラスから受け取る）
	int mFireStopFrameNum;	// 火の玉攻撃が動き始めるまでの時間（攻撃準備時間，火の玉が画面に見えてはいる）

	std::vector<int> mAXs;	// 各火の玉のx座標
	std::vector<int> mAYs;	// 各火の玉のy座標
	int mHitRangeAW, mHitRangeAH;	// 火の玉の当たり判定範囲
	int mDirecY;	// EnemyMageのWalkの際のy座標の移動の向き制御に使用する
	const int ENE_MAGE_Y_MAX = 610;	// EnemyMageのWalkの際のy座標の移動範囲（最大）
	const int ENE_MAGE_Y_MIN = 290;	// EnemyMageのWalkの際のy座標の移動範囲（最小）
	int mAlphaValue;	// EnemyMageの透明度，FadeIn, FadeOutで透けるために使用する
	int DELTA_ALPHA = 7;	// フェードインとフェードアウトの際のα値の1フレーム当たりの増加/減少分

	int mRoutineDoneCnt;	// 動作を終えた回数，特定の回数終わらせた後に自動的に消すようにするために使用する
							// 動作とは，（フェードイン → 火の玉攻撃 → フェードアウト）のセットで1回とカウントする
							// ただし，最初の一回目は，（フェードイン → 歩行 → フェードアウト）のセットとする
	int mDeleteRoDoneNum;	// この回数の動作をした後は，自動的に消すようにする

	bool mIsFadingIn;	// フェードインしているときtrue
	bool mIsFadingOut;	// フェードアウトしているときtrue
	bool mIsHiding;	// 動作の間に姿を隠している（消している）ときtrue
	int mHidingFrameCnt;	// フェードインとフェードアウトの間に姿を隠している（消している）フレーム数のカウント
	const int HIDING_FRAME_NUM_MIN = 60;	// 最悪でも個のフレーム数分，フェードインとフェードアウトの間に姿を隠している（消している）
	bool mMageIsDead;	// mHpが0，かつEnemyMage自体を消していいとき（死んだことを認識させるための固定時間後など）にtrueになる
	bool mHasFinishedRos;	// 動作をmDeleteRoDoneNumの数までおわらしたときにtrueとなる
	int mAttackFrameCnt;	// 攻撃をしている際（火の玉を出し始めてから）のフレーム数をカウントする，フェードアウトの開始などで使用する
	const int WALK_FRAME_NUM = 120;	// フェードインで入ってきてから移動している時間（1回目の動作の時のみ使用）
	const int ATTACK_STATE_FRAME_NUM = 300;	// 攻撃をしてから（火の玉を出し始めてから），フェードアウトを始めるまでのフレーム数（2回目以降の動作の時使用）
};

