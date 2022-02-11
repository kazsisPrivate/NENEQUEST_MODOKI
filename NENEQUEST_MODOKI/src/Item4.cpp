// ����񂲁i�񕜌n�A�C�e���C�񕜗�-3�j
#include "Item4.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item4::Item4(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(4), itemIdx, x, y) {
}


void Item4::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 100, mImgH = 90;
	mHitRangeW = 23, mHitRangeH = 15;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsChangingItem = false;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = -3;	// �񕜌��ʂ���
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 4;
}
