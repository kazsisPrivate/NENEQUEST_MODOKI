#include "DxLib.h"
#include "Item.h"
#include "ItemMgr.h"


Item::Item(ItemChanger* changer, const int* graph, const int itemIdx, const int x, const int y) : mIteHandle(graph) {
	mItemChanger = changer;
	mItemIdx = itemIdx;
	mX = x;
	mY = y;

	mItemMgr = ItemMgr::GetInstance();
}


void Item::Update() {
	if (mPlIsHit || mX < ITEM_DELETE_X) {
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);	// -1000ÇÕìKìñÇ…âÊñ äOÇÃêîílÇ…ÇµÇƒÇ¢ÇÈ
	}

	// à⁄ìÆ
	Move();

	// ìñÇΩÇËîªíËÇÃèàóù
	//UpdateHit();
}


void Item::Draw() {
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, *mIteHandle, TRUE);
}


void Item::Move() {
	mX -= mSpeed;
}


//void Item::UpdateHit() {
//	if (mItNum == 0) {
//		if (plJudge == true) {
//			HitJudge0::SetIRange(-3000, -3000, 0, 0);
//		}
//		else {
//			HitJudge0::SetIRange(x, y, hitRangeX, hitRangeY);
//			plJudge = HitJudge0::PIJudge();
//		}
//	}
//	else {
//		if (plJudge == true) {
//			HitJudge1::SetIRange(-3000, -3000, 0, 0);
//		}
//		else {
//			HitJudge1::SetIRange(x, y, hitRangeX, hitRangeY);
//			plJudge = HitJudge1::PIJudge();
//		}
//	}
//
//}


void Item::GetIteDataMap(std::map<std::string, float>* iteDataMap) {
	/*mIteIntDataMap["x"] = mX;
	mIteIntDataMap["y"] = mY;
	mIteIntDataMap["hitRangeW"] = mHitRangeW;
	mIteIntDataMap["hitRangeH"] = mHitRangeH;
	mIteIntDataMap["healPower"] = mHealPower;
	mIteIntDataMap["speedPower"] = mSpeedPower;
	mIteIntDataMap["attackPower"] = mAttackPower;
	mIteIntDataMap["itemKind"] = mItemKind;*/

	//iteDataMap = &mIteIntDataMap;

	(*iteDataMap)["x"] = mX;
	(*iteDataMap)["y"] = mY;
	(*iteDataMap)["hitRangeW"] = mHitRangeW;
	(*iteDataMap)["hitRangeH"] = mHitRangeH;
	(*iteDataMap)["healPower"] = mHealPower;
	(*iteDataMap)["speedPower"] = mSpeedPower;
	(*iteDataMap)["attackPower"] = mAttackPower;
	(*iteDataMap)["itemId"] = mItemId;
}


void Item::SetIsHits(std::vector<std::map<std::string, bool>>& isHitMap) {
	mPlIsHit = isHitMap.at(mItemIdx)["player"];
	mPlAIsHit = isHitMap.at(mItemIdx)["playerAttack"];
}