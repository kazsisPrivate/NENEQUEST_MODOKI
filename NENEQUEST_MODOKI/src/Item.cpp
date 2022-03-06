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
	if (mPlIsHit) {	// Player��Item���擾�i�j��j���ꂽ�Ƃ�
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);	// -1000�͓K���ɉ�ʊO�̐��l�ɂ��Ă���
		mIsDead = true;
	}
	else if (mX < ITEM_DELETE_X) {	// Item����ʊO�Ɉړ������Ƃ�
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);
	}

	// �ړ�
	Move();
}


void Item::Draw() {
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, *mIteHandle, TRUE);
}


void Item::Move() {
	mX -= mSpeed;
}


void Item::GetIteDataMap(std::map<std::string, float>* iteIntDataMap, std::map<std::string, float>* iteBoolDataMap) {
	if (mIsDead && mItemId < 12) {	// ���ɏ�����ior ���̃A�C�e���Ɍ�シ��j�Ƃ�
		// �����2��Ƃ�Ȃ��悤�ɂ��邽�߂Ɉʒu����ʊO�ɐݒ肷��
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