// �C�i�������n�A�C�e���C�X�s�[�h0.5�{�j
#include "Item6.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item6::Item6(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(6), itemIdx, x, y) {
}


void Item6::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mImgW = 128, mImgH = 100;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// ������X�R�A
	mScore = 1000;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 0.5f;	// �X�s�[�h�_�E�����ʂ���
	mAttackPower = 1;
	mItemId = 6;
}