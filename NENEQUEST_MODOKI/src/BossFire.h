#pragma once

#include "BasicFunc.h"
#include <vector>

class BossFire : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override; 
	void Update() override;
	void Draw() override;
	void StartFire(const int bossX, const int bossY, const int fireType, const int attackType);	// 火の玉攻撃を始める際の変数設定
																								// fireType(1: 赤い火の玉（速度普通），2: 青い火の玉（速度速い）)
																								// attackType(1: 火の玉吐き出し攻撃，2: ブレス攻撃)
	int GetFireNum(const int attackType) const;	// 火の玉の数を返す，Enemy側に使用する火の玉を把握させるのに使用する
	bool GetFiresExist() const;	// 火の玉が残っているかどうか，1つでも残っていればtrueを返す
	void GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys);	// 各火の玉のxy座標を返す，Enemy側で把握させるのに使用する
	void GetFiresHitRangeWHs(std::vector<int>& hitRangeWs, std::vector<int>& hitRangeHs);	// 各火の玉の当たり判定を返す，Enemy側で把握させるのに使用する
	

private:
	void FireBall();	// 火の玉吐き出し攻撃
	void FireBreath();	// ブレス攻撃
	float CalcBreathY(const float x);	// x座標からブレス攻撃のy座標を求める

	int* mFireHandle;
	const int FIRE_BALL_NUM = 3;	// 火の玉吐き出し攻撃で使用する火の玉の数
	const int FIRE_BREATH_NUM = 5;	// ブレス攻撃で使用する火の玉の数
	int mBallHandleIds[3]; // 火の玉吐き出し攻撃で使用する，それぞれの火の玉が斜めを向いている画像か横を向いている画像か使い分ける
	float mXs[5], mYs[5];	// それぞれの火の玉のxy座標
	float mDXs[5], mDYs[5]; // x, yの1フレームあたりの増加（減少）量
	float mDDX, mDDY;	// x, yの1フレーム当たりの加速度，ブレス攻撃の火の玉の移動速度を徐々に上げていくのに使用する
	int mBossMouthX, mBossMouthY;	// EnemyBossの口の位置，火の玉の吐き出し始めの座標として使用する
	int mBallHitRangeW, mBallHitRangeH;	// 火の玉吐き出し攻撃で使用する火の玉の当たり判定の範囲
	int mOrigHitRangeW, mOrigHitRangeH;	// ブレス攻撃で使用する火の玉の元画像の元の当たり判定の範囲（拡大率によって変化させる前の当たり判定の範囲）
	float mBreathHitRangeWs[5];	// ブレス攻撃で使用する火の玉の当たり判定の範囲（幅），それぞれの火の玉の当たり判定の大きさは異なり，変化する
	float mBreathHitRangeHs[5];	// ブレス攻撃で使用する火の玉の当たり判定の範囲（高さ），それぞれの火の玉の当たり判定の大きさは異なり，変化する 
	int mImgW, mImgH;	// 火の玉の画像の大きさ
	float mFireExpRates[5];	// 火の玉の画像の表示に用いる拡大率，ブレス攻撃の時に使用する
	int mAttackType;	// 火の玉の動きのパターン(1: 火の玉吐き出し攻撃，2: ブレス攻撃)
	bool mFiresExist;	// 火の玉が残っているかどうか，1つでも残っていればtrue
	int mFrameCnt;	// フレーム数のカウント，火の玉の個別制御のために使用する
	int mFireBallFrameNums[3];	// 火の玉吐き出し攻撃で火の玉を順に吐き出していく演出で使用，それぞれの火の玉を吐き出すフレーム数
	//const int FIRE_BALLS_FRAME_NUMS[3] = { 60, 180, 300 };	// 火の玉掃き出し攻撃で火の玉を順に吐き出していく演出で使用，それぞれの火の玉を吐き出すフレーム数
	const int FIRE_DELETE_LX = -250;	// 火の玉吐き出し攻撃において，この座標まですべての火の玉が移動したとき，自動的に消すようにする(左側)
	int mFireBallYs[3];	// 火の玉吐き出し攻撃においてそれぞれの火の玉の横移動を始めるy座標（吐き出し攻撃では斜め下に吐き出してから横移動を始める）
	const int PREPARING_BRE_FRAME_NUM = 60;	// ブレス攻撃をし始めるまで待機しているフレーム数，このフレーム数を超えたらブレス攻撃をし始める
	const int BREATHING_FRAME_NUM = 360;	// ブレス攻撃をしているフレーム数，このフレーム数を超えたらブレス攻撃で使用している火の玉を消し始める 
	const int BREATHING_NEW_FIRE_FRAME_NUM = 10;	// ブレス攻撃の際に前に口から火の玉を出した後から，新しく口から火の玉を出すまでのフレーム数
	int mNextBreathId;	// ブレス攻撃で次に吐き出す火の玉のid番号（0 ～ (FIRE_BREATH_NUM - 1)）
	bool mBreIsExistings[5];	// ブレス攻撃で火の玉を使用中（吐き出しているとき）だったらtrue
};