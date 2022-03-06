#pragma once
/*
* 魔法使いの敵（EnemyMage）が使用する火の玉の制御を行うクラス
*/
#include "BasicFunc.h"
#include <utility>
#include <vector>


class MageFire : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartFire(const int eneX, const int eneY, const int fireType, const int attackType);	// 火の玉攻撃を始める際の変数設定
																								// fireType(1: 赤い火の玉（速度普通），2: 青い火の玉（速度速い）)
																								// attackType(1: ジグザグ攻撃，2: 回転攻撃)
	int GetFireNum() const;	// 火の玉の数を返す，Enemy側に使用する火の玉を把握させるのに使用する
	int GetFireStopFrameNum(const int attackType) const;	// 火の玉が動き出す前の時間を返す
	std::pair<int, int> GetFiresHitRange();	// 火の玉の当たり判定の範囲を返す，Enemy側で把握させるのに使用する
	bool GetFiresExist() const;	// 火の玉が残っているかどうか，3つの火の玉のうち1つでも画面内に残っていればtrueを返す
	void MakeFiresExistFalse();	// 火の玉を消すために使用する, EnemyMageが攻撃を放つ前にやられたら呼びだす
	void GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys);	// 各火の玉のxy座標を返す，Enemy側で把握させるのに使用する

private:
	void Move();	// 火の玉の移動
	void UpdateRotatedFiresXYs(); // 火の玉の回転角を考慮したxy座標に更新，回転攻撃で使用，呼びだした際のmXs, mYs, mRadius, mThetasを利用して更新する

	int* mFireHandle;
	const int FIRE_NUM = 3;	// 火の玉の数
	float mXs[3];	// それぞれの火の玉のx座標
	float mYs[3];	// それぞれの火の玉のy座標
	float mCX, mCY; // 火の玉の回転攻撃に使用する各火の玉の回転の中心点座標(回転攻撃で使用)
	float mRadius;	// 火の玉の回転攻撃の際の各火の玉の回転の円の半径(回転攻撃で使用)
	float mThetas[3];	// 各火の玉の回転角(回転攻撃で使用)
	const int IMG_W = 120, IMG_H = 108;	// 火の玉の画像の大きさ
	//int count; //火の玉の動きの制御のための時間計測に使う
	int mDirec;	// 攻撃の方向を表す，左向きなら-1，右向きなら1が入っている
	int mAttackType;	// 火の玉の動きのパターン(1: ジグザグ攻撃，2: 回転攻撃)
	float mDX;	// x座標の1フレームあたりの増加分, ジグザグ攻撃では各火の玉のx座標，回転攻撃では回転の円の中心点のx座標
	float mDYs[3];	// それぞれの火の玉のy座標の1フレームあたりの増加分
	float mDTh;	// 回転角の1フレーム当たりの増加分
	float mDR;	// 回転攻撃の際に使用する円の半径の1フレーム当たりの増加分
	const int FIRES_DISAPPEAR_FRAME_NUMS[3] = { 0, 15, 30 };	// 回転攻撃を始める際の火の玉を順に表示していく演出で使用，それぞれの火の玉が現れるフレーム数
	const int FIRES_STOP_FRAME_NUMS[3] = { 30, 35, 40 };	// ジグザグ攻撃を始める際のそれぞれの火の玉の動き出す(動き出すまでに止まっている)フレーム数，1つずつ動かしていく
	const int FIRES_STOP_FRAME_NUM = 90;	// 回転攻撃を始める際の火の玉の動き出す(動き出すまでに止まっている)フレーム数
	const int FIRE_DELETE_LX = -250;	// この座標まですべての火の玉が移動したとき，自動的に消すようにする(左側)
	const int FIRE_DELETE_RX = 1450;	// この座標まですべての火の玉が移動したとき，自動的に消すようにする(右側)
	const int SCREEN_TOP_Y = 50;	// 画面の上の座標，ジグザグ攻撃の玉の跳ね返りで使用する
	const int SCREEN_BOTTOM_Y = 650;	// 画面の下の座標，ジグザグ攻撃の玉の跳ね返りで使用する
	const int FIRE_FIRST_STOP_FRAME_NUM = 30;	// 最初に火の玉を表示させて動き出すまでの時間，火の玉攻撃が来るぞということを認識させるために火の玉を動かない状態で表示する時間
	bool mFiresExist;	// 火の玉が残っているかどうか，3つの火の玉のうち1つでも画面内に残っていればtrue
	int mFrameCnt;	// フレーム数のカウント，火の玉の個別制御のために使用する
};