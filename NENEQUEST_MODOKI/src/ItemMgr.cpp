#include "DxLib.h"
#include "Item.h"
#include "Item1.h" // ここから回復系
#include "Item2.h"
#include "Item3.h"
#include "Item4.h"
#include "Item5.h" // ここから自強化系
#include "Item6.h"
#include "Item7.h"
#include "Item8.h" // ここから武器系
#include "Item9.h" 
#include "Item10.h"
#include "Item11.h"
#include "Item12.h"	// ここから箱系
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
	// Itemが何もセットされていない状態に初期化
	for (int i = 0; i < ITEM_NUM; i++) {
		mItems[i] = NULL;
		mItemsNext[i] = eItem1;	// デバッグ用に入れいている
		
		mItemNextX[i] = 1300 + 500 * i;
		mItemNextY[i] = 300 + 150 * i;
	}
	mItemsNext[0] = eItem12;	// デバッグ用に入れいている
	mItemsNext[1] = eItem14;	// デバッグ用に入れいている

	/*ItemData::SetNextItem0(-1);

	count = 0;
	apcount = 0;*/
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
		if (mItemsNext[i] != eItemNone) {	// 次のItemがセットされているとき
			if (mItems[i]) {	// mItems[i]の中がNULLでないとき
				// 終了処理をする
				mItems[i]->Finalize();
				delete mItems[i];
			}
			
			// 次のItemに変更する
			switch (mItemsNext[i]) {
				case eItem1:
					mItems[i] = (Item*) new Item1(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem2:
					mItems[i] = (Item*) new Item2(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem3:
					mItems[i] = (Item*) new Item3(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem4:
					mItems[i] = (Item*) new Item4(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem5:
					mItems[i] = (Item*) new Item5(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem6:
					mItems[i] = (Item*) new Item6(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem7:
					mItems[i] = (Item*) new Item7(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem8:
					mItems[i] = (Item*) new Item8(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem9:
					mItems[i] = (Item*) new Item9(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem10:
					mItems[i] = (Item*) new Item10(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem11:
					mItems[i] = (Item*) new Item11(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem12:
					mItems[i] = (Item*) new Item12(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem13:
					mItems[i] = (Item*) new Item13(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItem14:
					mItems[i] = (Item*) new Item14(this, i, mItemNextX[i], mItemNextY[i]);
					break;
				case eItemNULL:
					mItems[i] = NULL;
					break;
			}

			mItemsNext[i] = eItemNone;

			if (mItems[i]) {
				mItems[i]->Initialize();
			}
		}
	}

	// 各itemの更新処理をする
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->Update();
		}
	}
}


//void ItemMgr::Draw() {
//	// 各Itemの描画
//	for (int i = 0; i < ITEM_NUM; i++) {
//		if (mItems[i]) {	// NULLが入っていなければ
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
	mItemsNext[itemIdx] = itemNext;
	
	mItemNextX[itemIdx] = itemNextX;
	mItemNextY[itemIdx] = itemNextY;
}


void ItemMgr::GetIteDataMaps(std::vector<std::map<std::string, float>>* iteDataMaps, bool* isExistings) {
	// 各Itemの情報を渡す
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItemsNext[i] == eItemNone && mItems[i]) {
			mItems[i]->GetIteDataMap(&(*iteDataMaps).at(i));
			isExistings[i] = true;
		}
		else {
			//iteDataMap1 = NULL;
			isExistings[i] = false;
		}
	}

}


void ItemMgr::SetIsHitMaps(std::vector<std::map<std::string, bool>>& isHitMap) {
	// 各ItemにPlayerとの当たり判定結果を渡す
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mItems[i]) {
			mItems[i]->SetIsHits(isHitMap);
		}
	}
}