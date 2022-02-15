// ��񂲁i�񕜌n�A�C�e���C�񕜗�-1�j
#include "Item2.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item2::Item2(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(2), itemIdx, x, y) {
}


void Item2::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 100, mImgH = 90;
	mHitRangeW = 23, mHitRangeH = 15;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// ������X�R�A
	mScore = 300;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = -1;	// �񕜌��ʂ���
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 2;
}
