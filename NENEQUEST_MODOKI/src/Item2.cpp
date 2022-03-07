// 青りんご（回復系アイテム，回復量-1）
#include "Item2.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item2::Item2(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(2), itemIdx, x, y) {
}


void Item2::Initialize() {
	// 当たり判定関連の設定
	mImgW = 100, mImgH = 90;
	mHitRangeW = 23, mHitRangeH = 15;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// 得られるスコア
	mScore = 300;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = -1;	// 回復効果あり
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 2;
}
