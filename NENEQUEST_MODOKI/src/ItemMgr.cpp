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
	mItesNext[0] = eItem12;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
	mItesNext[1] = eItem14;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
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


//void ItemMgr::Draw() {
//	// �eItem�̕`��
//	for (int i = 0; i < ITEM_NUM; i++) {
//		if (mItems[i]) {	// NULL�������Ă��Ȃ����
//			mItems[i]->Draw();
//		}
//	}
//}


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


void ItemMgr::GetIteData(std::vector<std::map<std::string, float>>* iteDataMaps, bool* isExistings) {
	// �eItem�̏���n��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->GetIteDataMap(&(*iteDataMaps).at(i));
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