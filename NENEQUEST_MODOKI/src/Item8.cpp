// ��1�i����j
#include "Item8.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item8::Item8(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(8), itemIdx, x, y) {
}


void Item8::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 121, mImgH = 205;
	mHitRangeW = 13, mHitRangeH = 50;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsChangingItem = false;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;	
	mItemId = 8;	// ����ω�����
}
