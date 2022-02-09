// �|�i����j
#include "Item11.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item11::Item11(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(11), itemIdx, x, y) {
}


void Item11::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 130, mImgH = 147;
	mHitRangeW = 30, mHitRangeH = 30;
	mPlIsHit = false;
	mPlAIsHit = false;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 11;	// ����ω�����
}
