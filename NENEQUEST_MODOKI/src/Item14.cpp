// ���i���CItem8�`11�i����j�������_���ŏo�Ă���j
#include "Item14.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <random>


Item14::Item14(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: ItemBox(changer, ItemGraphics::GetGraHandle(14), itemIdx, x, y) {
}


void Item14::Initialize() {
	ItemBox::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 164, mImgH = 160;
	mHitRangeW = 35, mHitRangeH = 35;

	// ������X�R�A
	mScore = 100;

	// ���̑��̐ݒ�
	mItemId = 13;
}


void Item14::CreateBoxItem() {
	// 1�`100�̃����_���Ȑ��l�𐶐�
	std::random_device rnd;
	int randNum = rnd() % 100 + 1;

	if (randNum <= 25) {	// 25%�̊m����
		// ��1�iItem8�j
		mBoxItemEnum = eItem8;
		mBoxItemHandle = ItemGraphics::GetGraHandle(8);
		mBoxIteImgW = 121, mBoxIteImgH = 205;
	}
	else if (randNum <= 50) {	// 25%�̊m����
		// ��2�iItem9�j
		mBoxItemEnum = eItem9;
		mBoxItemHandle = ItemGraphics::GetGraHandle(9);
		mBoxIteImgW = 153, mBoxIteImgH = 200;
	}
	else if (randNum <= 75) {	// 25%�̊m����
		// ���iItem10�j
		mBoxItemEnum = eItem10;
		mBoxItemHandle = ItemGraphics::GetGraHandle(10);
		mBoxIteImgW = 144, mBoxIteImgH = 200;
	}
	else {	// 25%�̊m����
		// �|�iItem11�j
		mBoxItemEnum = eItem11;
		mBoxItemHandle = ItemGraphics::GetGraHandle(11);
		mBoxIteImgW = 130, mBoxIteImgH = 147;
	}
}