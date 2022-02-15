// �M1�i���CItem1�`2, 5�`7�������_���ŏo�Ă���j
#include "Item12.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <time.h>


Item12::Item12(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: ItemBox(changer, ItemGraphics::GetGraHandle(12), itemIdx, x, y) {
}


void Item12::Initialize() {
	ItemBox::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 162, mImgH = 160;
	mHitRangeW = 35, mHitRangeH = 35;

	// ������X�R�A
	mScore = 100;

	// ���̑��̐ݒ�
	mItemId = 12;
}


void Item12::Draw() {
	ItemBox::Draw();
}


void Item12::Update() {
	ItemBox::Update();
}


void Item12::CreateBoxItem() {
	// 1�`100�̃����_���Ȑ��l�𐶐�
	srand((unsigned int)time(NULL));
	int randNum = rand() % 100 + 1;	

	if (randNum <= 30) {	// 30%�̊m����
		// �Ԃ�񂲁iItem1�j
		mBoxItemEnum = eItem1;
		mBoxItemHandle = ItemGraphics::GetGraHandle(1);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 50) {	// 20%�̊m����
		// ��񂲁iItem2�j
		mBoxItemEnum = eItem2;
		mBoxItemHandle = ItemGraphics::GetGraHandle(2);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 70) {	// 20%�̊m����
		// �ԌC�iItem5�j
		mBoxItemEnum = eItem5;
		mBoxItemHandle = ItemGraphics::GetGraHandle(5);
		mBoxIteImgW = 128, mBoxIteImgH = 100;
	}
	else if (randNum <= 80) {	// 10%�̊m����
		// �C�iItem6�j
		mBoxItemEnum = eItem6;
		mBoxItemHandle = ItemGraphics::GetGraHandle(6);
		mBoxIteImgW = 128, mBoxIteImgH = 100;
	}
	else {	// 20%�̊m����
		// �r�iItem7�j
		mBoxItemEnum = eItem7;
		mBoxItemHandle = ItemGraphics::GetGraHandle(7);
		mBoxIteImgW = 122, mBoxIteImgH = 102;
	}
}