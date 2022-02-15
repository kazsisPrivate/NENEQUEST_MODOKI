// �r�i�������n�A�C�e���C�U����2�{�j
#include "Item7.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item7::Item7(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(7), itemIdx, x, y) {
}


void Item7::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 122, mImgH = 102;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// ������X�R�A
	mScore = 100;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;	
	mAttackPower = 2;	// �U���̓A�b�v���ʂ���
	mItemId = 7;
}