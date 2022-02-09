#include "ItemBox.h"
#include "Dxlib.h"


ItemBox::ItemBox(ItemChanger* changer, const int* graph, const int itemIdx, const int x, const int y) 
	: Item(changer, graph, itemIdx, x, y) {
}


void ItemBox::Initialize() {
	// �����蔻��֘A�̐ݒ�
	mPlIsHit = false;
	mPlAIsHit = false;

	// ItemBox�݂̂����ϐ��̐ݒ�
	mBoxItemEnum = eItemNULL;
	mBoxItemX = -1000, mBoxItemY = -1000;
	mJumpFrameCnt = 0;

	// ���̑��̐ݒ�
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
}


void ItemBox::Draw() {
	// ���̕`��
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, mIteHandle[mHandleNumber], TRUE);

	// �������яo����item�̕`��
	if (mIsJumping) {
		DrawGraph(mBoxItemX - mBoxIteImgW / 2, mBoxItemY - mBoxIteImgH / 2, *mBoxItemHandle, TRUE);
	}
}


void ItemBox::Update() {
	if (mX < ITEM_DELETE_X) {	// ��ʊO�Ɉړ������Ƃ�
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);	// -1000�͓K���ɉ�ʊO�̐��l�ɂ��Ă���
	}
	else if (mIsJumping) {	// ���������āCitem���������яo���Ă���Ƃ�
		if (mJumpFrameCnt == JUMP_FRAME_NUM) {	// �������яo����Item�����n������
			mItemChanger->ChangeItem(mItemIdx, mBoxItemEnum, mBoxItemX, mBoxItemY);
		}
		else {
			Jump();
		}
	}
	else {
		if (mPlAIsHit) {	// Player�̍U�������ɓ���������
			// ����Ă��锠�̉摜���f���悤�ɂ���
			mHandleNumber = 1;

			// Jump�Ɏg�p����ϐ��̐ݒ�
			mIsJumping = true;
			mJumpFrameCnt = 0;

			mBoxItemX = mX;
			mBoxItemY = mY;
			mBoxItemYPrev = mBoxItemY;
			mBoxItemY = mBoxItemY - 17;

			// �������яo��item���쐬
			CreateBoxItem();
		}
		else {
			// �ړ�
			Move();
		}
	}
}


void ItemBox::Jump() {
	// x���W�̍X�V
	mBoxItemX += 15;

	// y���W�̍X�V
	int boxItemYTemp = mBoxItemY;
	mBoxItemY += (mBoxItemY - mBoxItemYPrev) + 1;
	mBoxItemYPrev = boxItemYTemp;

	mJumpFrameCnt++;
}