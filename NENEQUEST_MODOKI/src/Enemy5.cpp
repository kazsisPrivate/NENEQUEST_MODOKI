// 魔法使い2（hp2, 赤い火の玉, 攻撃回数1回）
#include "Enemy5.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy5::Enemy5(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 5), itemIdx, x, y) {
}


void Enemy5::Initialize() {
	EnemyMage::Initialize();

	// 当たり判定関連の設定
	mImgW = 225, mImgH = 192;

	// 攻撃や体力の設定
	mHp = 2;
	mAttack = 1;	// 火の玉の攻撃力

	// 火の玉のタイプの設定
	mFireType = 1;	// 赤い火の玉

	// 動作回数の設定
	mDeleteRoDoneNum = 2;

	// 倒したら得られるスコアの設定
	mScore = 1000;
}