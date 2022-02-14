// @g¢3ihp1, Â¢ÎÌÊ, Uñ2ñj
#include "Enemy6.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy6::Enemy6(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 6), itemIdx, x, y) {
}


void Enemy6::Initialize() {
	EnemyMage::Initialize();

	// ½è»èÖAÌÝè
	mImgW = 225, mImgH = 190;

	// UâÌÍÌÝè
	mHp = 1;
	mAttack = 1;	// ÎÌÊÌUÍ

	// ÎÌÊÌ^CvÌÝè
	mFireType = 2;	// Â¢ÎÌÊ

	// ®ìñÌÝè
	mDeleteRoDoneNum = 3;
}