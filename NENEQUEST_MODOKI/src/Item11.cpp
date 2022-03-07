// 弓（武器）
#include "Item11.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item11::Item11(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(11), itemIdx, x, y) {
}


void Item11::Initialize() {
	// 当たり判定関連の設定
	mImgW = 130, mImgH = 147;
	mHitRangeW = 30, mHitRangeH = 30;
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
	mItemId = 11;	// 武器変化あり
}
