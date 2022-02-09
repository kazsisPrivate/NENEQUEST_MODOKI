// �ԌC�i�������n�A�C�e���C�X�s�[�h2�{�j
#include "Item5.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item5::Item5(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(5), itemIdx, x, y) {
}


void Item5::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 128, mImgH = 100;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;	
	mSpeedPower = 2.0f;	// �X�s�[�h�A�b�v���ʂ���
	mAttackPower = 1;
	mItemId = 5;
}