// Enemy1～3のイノシシの敵の基底クラス
#include "EnemyBoar.h"
#include "DxLib.h"


EnemyBoar::EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y)
	: Enemy(changer, graph, eneIdx, x, y) {
}


void EnemyBoar::Initialize() {
	Enemy::Initialize();

	// 当たり判定関連の設定
	mHitRangeW = 70, mHitRangeH = 35;

	// 移動速度や攻撃力の設定
	mSpeed = 20.0f;
	mAttack = 1;

	// その他
	mExistingFrameCnt = 0;
	mIsBoss = false;
}


void EnemyBoar::Walk() {
	mX -= (int)mSpeed;

	// フレーム数に合わせて表示画像を変化させる
	int ix = mExistingFrameCnt % 20 / 10;	// 10フレーム毎に画像交代

	mHandleId = ix;
}