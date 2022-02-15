// 魔法使い3（hp1, 青い火の玉, 攻撃回数2回）
#include "Enemy6.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy6::Enemy6(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 6), itemIdx, x, y) {
}


void Enemy6::Initialize() {
	EnemyMage::Initialize();

	// 当たり判定関連の設定
	mImgW = 225, mImgH = 190;

	// 攻撃や体力の設定
	mHp = 1;
	mAttack = 1;	// 火の玉の攻撃力

	// 火の玉のタイプの設定
	mFireType = 2;	// 青い火の玉

	// 動作回数の設定
	mDeleteRoDoneNum = 3;

	// 倒したら得られるスコアの設定
	mScore = 1000;
}