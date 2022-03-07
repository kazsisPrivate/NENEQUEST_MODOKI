// 魔法使い1（hp1, 赤い火の玉, 攻撃回数1回）
#include "Enemy4.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy4::Enemy4(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 4), itemIdx, x, y) {
}


void Enemy4::Initialize() {
	EnemyMage::Initialize();

	// 当たり判定関連の設定
	mImgW = 225, mImgH = 192;

	// 攻撃や体力の設定
	mHp = 1;
	mAttack = 1;	// 火の玉の攻撃力

	// 火の玉のタイプの設定
	mFireType = 1;	// 赤い火の玉

	// 動作回数の設定
	mDeleteRoDoneNum = 2;

	// 倒したら得られるスコアの設定
	mScore = 600;
}