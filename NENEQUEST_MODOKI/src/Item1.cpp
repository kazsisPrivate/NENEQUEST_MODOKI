// �Ԃ�񂲁i�񕜌n�A�C�e���C�񕜗�2�j
#include "Item1.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item1::Item1(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(1), itemIdx, x, y) {
}


void Item1::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 100, mImgH = 90;
	mHitRangeW = 23, mHitRangeH = 15;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsChangingItem = false;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 2;	// �񕜌��ʂ���
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 1;
}