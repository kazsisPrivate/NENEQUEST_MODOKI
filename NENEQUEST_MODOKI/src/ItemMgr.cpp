#include "DxLib.h"
#include "Item.h"
#include "Item1.h" // ��������񕜌n
#include "Item2.h"
#include "Item3.h"
#include "Item4.h"
#include "Item5.h" // �������玩�����n
#include "Item6.h"
#include "Item7.h"
#include "Item8.h" // �������畐��n
#include "Item9.h" 
#include "Item10.h"
#include "Item11.h"
#include "Item12.h"	// �������甠�n
#include "Item13.h"
#include "Item14.h"
#include "ItemMgr.h"
#include <cmath>
#include <random>

ItemMgr* ItemMgr::mItemMgr;


ItemMgr* ItemMgr::GetInstance() {
	if (!ItemMgr::mItemMgr) {
		ItemMgr::mItemMgr = new ItemMgr();
		ItemMgr::mItemMgr->Initialize();
	}

	return ItemMgr::mItemMgr;
}


void ItemMgr::Initialize() {
	// Item�������Z�b�g����Ă��Ȃ���Ԃɏ�����
	for (int i = 0; i < ITEM_NUM; i++) {
		mItems[i] = NULL;
		mItesNext[i] = eItem1;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
		
		mItesNextX[i] = 1300 + 500 * i;
		mItesNextY[i] = 300 + 150 * i;
	}
	mItesNext[0] = eItemNone;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
	mItesNext[1] = eItemNone;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
}


void ItemMgr::Finalize() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->Finalize();
		}
	}

	delete mItemMgr;
	mItemMgr = NULL;
}


void ItemMgr::Update() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItesNext[i] != eItemNone) {	// ����Item���Z�b�g����Ă���Ƃ�
			if (mItems[i]) {	// mItems[i]�̒���NULL�łȂ��Ƃ�
				// �I������������
				mItems[i]->Finalize();
				delete mItems[i];
			}
			
			// ����Item�ɕύX����
			switch (mItesNext[i]) {
				case eItem1:
					mItems[i] = (Item*) new Item1(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem2:
					mItems[i] = (Item*) new Item2(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem3:
					mItems[i] = (Item*) new Item3(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem4:
					mItems[i] = (Item*) new Item4(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem5:
					mItems[i] = (Item*) new Item5(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem6:
					mItems[i] = (Item*) new Item6(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem7:
					mItems[i] = (Item*) new Item7(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem8:
					mItems[i] = (Item*) new Item8(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem9:
					mItems[i] = (Item*) new Item9(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem10:
					mItems[i] = (Item*) new Item10(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem11:
					mItems[i] = (Item*) new Item11(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem12:
					mItems[i] = (Item*) new Item12(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem13:
					mItems[i] = (Item*) new Item13(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				case eItem14:
					mItems[i] = (Item*) new Item14(this, i, mItesNextX[i], mItesNextY[i]);
					break;
				default:	// case eItemNULL
					mItems[i] = NULL;
					break;
			}

			mItesNext[i] = eItemNone;

			if (mItems[i]) {
				mItems[i]->Initialize();
			}
		}
	}

	// �eitem�̍X�V����������
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->Update();
		}
	}
}


void ItemMgr::Draw(const int itemIdx) {
	if (mItems[itemIdx]) {
		mItems[itemIdx]->Draw();
	}
}


void ItemMgr::ChangeItem(const int itemIdx, EItem itemNext, const int itemNextX, const int itemNextY) {
	mItesNext[itemIdx] = itemNext;
	
	mItesNextX[itemIdx] = itemNextX;
	mItesNextY[itemIdx] = itemNextY;
}


void ItemMgr::GetIteData(std::vector<std::map<std::string, float>>* iteIntDataMaps, std::vector<std::map<std::string, float>>* iteBoolDataMaps, bool* isExistings) {
	// �eItem�̏���n��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->GetIteDataMap(&(*iteIntDataMaps).at(i), &(*iteBoolDataMaps).at(i));
			isExistings[i] = true;
		}
		else {
			//iteDataMap1 = NULL;
			isExistings[i] = false;
		}
	}

}


void ItemMgr::SetIsHitMaps(std::vector<std::map<std::string, bool>>& isHitMaps) {
	// �eItem��Player�Ƃ̓����蔻�茋�ʂ�n��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->SetIsHits(isHitMaps);
		}
	}
}


void ItemMgr::CreateItem() {
	// mItems�̒���Item���Z�b�g����Ă��鐔�𐔂���
	int existingIteNum = 0;
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			existingIteNum++;
		}
	}

	// Item�̐����m���i0�`10000, 10000��100%�j�����߂�
	// Item���Z�b�g����Ă���΂���قǐ����m����������
	int creationProb = 3000 * std::pow(0.3, existingIteNum);
		
	// 1�`10000�̃����_���Ȑ��l�𐶐�
	std::random_device rnd;
	int randNum = rnd() % 10000 + 1;

	// Item�𐶐��i10000 - creationProb�̊m����Item�͐�������Ȃ��j
	for (int i = 0; i < ITEM_NUM; i++) {
		if (!mItems[i]) {
			if (randNum >= 10000 - creationProb) {	// Item�𐶐�����Ƃ�
				// ����Item��xy�����߂Ă���
				mItesNextX[i] = ITEM_FIRST_X;	// x���W�͌Œ�
				mItesNextY[i] = rnd() % (ITEM_FIRST_Y_MAX - ITEM_FIRST_Y_MIN) + ITEM_FIRST_Y_MIN;

				// randNum��1�`creationProb�͈̔͂ɂ����̂��C1�`100�͈̔͂̒l�ɐ��K������
				randNum = 10000 - randNum + 1;
				randNum = (randNum / (float)creationProb) * 100;

				if (randNum <= 20) {	// 20%�̊m����
					// �Ԃ��
					mItesNext[i] = eItem1;
				}
				else if (randNum <= 30) {	// 10%�̊m����
					// ���
					mItesNext[i] = eItem2;
				}
				else if (randNum <= 60) {	// 30%�̊m����
					// �M1
					mItesNext[i] = eItem12;
				}
				else if (randNum <= 75) {	// 15%�̊m����
					// �M2
					mItesNext[i] = eItem13;
				}
				else {	// 25%�̊m����
					// ���i���킪�o��j
					mItesNext[i] = eItem14;
				}

				break;
			}
		}
	}
}