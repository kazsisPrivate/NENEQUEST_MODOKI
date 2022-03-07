// ��1�i����j
#include "Item9.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item9::Item9(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(9), itemIdx, x, y) {
}


void Item9::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 153, mImgH = 200;
	mHitRangeW = 12, mHitRangeH = 45;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// ������X�R�A
	mScore = 0;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 9;	// ����ω�����
}
