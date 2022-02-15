// 斧（武器）
#include "Item10.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item10::Item10(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(10), itemIdx, x, y) {
}


void Item10::Initialize() {
	// 当たり判定関連の設定
	mImgW = 144, mImgH = 200;
	mHitRangeW = 20, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// 得られるスコア
	mScore = 0;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 10;	// 武器変化あり
}
