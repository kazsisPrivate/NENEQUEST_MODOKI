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
	if (mPlIsHit) {	// PlayerにItemを取得（破壊）されたとき
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);	// -1000は適当に画面外の数値にしている
		mIsDead = true;
	}
	else if (mX < ITEM_DELETE_X) {	// Itemが画面外に移動したとき
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);
	}

	// 移動
	Move();
}


void Item::Draw() {
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, *mIteHandle, TRUE);
}


void Item::Move() {
	mX -= mSpeed;
}


void Item::GetIteDataMap(std::map<std::string, float>* iteIntDataMap, std::map<std::string, float>* iteBoolDataMap) {
	if (mIsDead && mItemId < 12) {	// 次に消える（or 他のアイテムに交代する）とき
		// 判定を2回とらないようにするために位置を画面外に設定する
		(*iteIntDataMap)["x"] = -1000;
		(*iteIntDataMap)["y"] = -1000;
	}
	else {
		(*iteIntDataMap)["x"] = mX;
		(*iteIntDataMap)["y"] = mY;
	}
	
	(*iteIntDataMap)["hitRangeW"] = mHitRangeW;
	(*iteIntDataMap)["hitRangeH"] = mHitRangeH;
	(*iteIntDataMap)["healPower"] = mHealPower;
	(*iteIntDataMap)["speedPower"] = mSpeedPower;
	(*iteIntDataMap)["attackPower"] = mAttackPower;
	(*iteIntDataMap)["itemId"] = mItemId;
	(*iteIntDataMap)["score"] = mScore;

	(*iteBoolDataMap)["isDead"] = mIsDead;
}


void Item::SetIsHits(std::vector<std::map<std::string, bool>>& isHitMap) {
	mPlIsHit = isHitMap.at(mItemIdx)["player"];
	mPlAIsHit = isHitMap.at(mItemIdx)["playerAttack"];
}