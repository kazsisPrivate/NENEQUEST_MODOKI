// @g¢1ihp1, Ô¢ÎÌÊ, Uñ1ñj
#include "Enemy4.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy4::Enemy4(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 4), itemIdx, x, y) {
}


void Enemy4::Initialize() {
	EnemyMage::Initialize();

	// ½è»èÖAÌÝè
	mImgW = 225, mImgH = 192;

	// UâÌÍÌÝè
	mHp = 1;
	mAttack = 1;	// ÎÌÊÌUÍ

	// ÎÌÊÌ^CvÌÝè
	mFireType = 1;	// Ô¢ÎÌÊ

	// ®ìñÌÝè
	mDeleteRoDoneNum = 2;
}