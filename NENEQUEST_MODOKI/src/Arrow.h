#pragma once

#include "BasicFunc.h"
#include <tuple>


class Arrow : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartArrow(const int x, const int y, const int moveType);
	bool GetArrowExists() const;
	bool GetIsMoving() const;	// 弓矢が動いているときかどうかを渡す，攻撃の当たり判定で使用する
	std::tuple<int, int> GetArrowXY();	// 攻撃の当たり判定を確認させるために弓矢の座標を渡す
	void SetIsHit(const bool isHit);	// Arrowが何かにあたったかどうかを入れる

private:
	void Move();	//	弓矢の移動
	void UpdateHit();	//	弓矢の当たり判定と敵に弓矢が当たったかどうかの判定
	int* mArrowHandle;	// 弓矢の画像
	int* mHitEffectHandle;	// 弓矢が当たった瞬間に出る当たったエフェクトの画像
	int mX, mY;	// 弓矢のx,y座標（左上端）
	int mXCenter, mYCenter; // 弓矢の回転の中心のx,y座標
	int mDX;	// x座標の1フレームあたりの増加量，強く放つか弱く放つかで変化する
	const int HIT_RANGE_W = 11;	// 弓矢の当たり判定の範囲(Width)
	const int HIT_RANGE_H = 10;	// 弓矢の当たり判定の範囲(Height)
	int mYPrev, mYStart;	// 弓矢の自由落下の処理で使用する
	int mDYFirst;	// y座標の1フレーム当たりの増加量の最初の値，強く放つか弱く放つかで変化する
	const int IMG_W = 70;	// Arrowの画像の大きさ（Width）
	const int IMG_H = 64;	// Arrowの画像の大きさ（Height）
	int mAExistingFrameCnt;	// 弓矢が放たれてからのフレーム数，弓矢の動きの制御のための時間計測に使う
	const int A_EXISTING_FRAME_NUM = 80;	// 弓矢が放たれてから弓矢を消すまでのフレーム数
	int mHitFrameCnt;	// 弓矢が敵やItemに当たってから経過したフレーム数
	const int HIT_FRAME_NUM = 20;	// 弓矢が敵やItemにあたってから弓矢を消すまでのフレーム数
	int mType;	// 弓矢の動きのタイプ（1：右向きの弱い弓矢，2：左向きの弱い弓矢，3：右向きの強い弓矢，4：左向きの強い弓矢）
	float mTheta;	// mXCenter, mYCenterを中心とした弓矢の回転角
	float mDTh;	// mThetaの1フレームあたりの増加量
	bool mArrowExists;	// 弓矢が存在していればtrue，Player_4のほうでUpdateやDrawをさせるかの判断のためにある
	bool mIsMoving; //	矢が動いている間（何にもあたっていない間）はture
	bool mIsHit;	// 敵やItemに矢が当たったかどうかの判定に使用する
};