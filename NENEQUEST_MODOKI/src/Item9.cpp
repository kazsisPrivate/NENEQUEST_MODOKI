// 剣1（武器）
#include "Item9.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item9::Item9(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(9), itemIdx, x, y) {
}


void Item9::Initialize() {
	// 当たり判定関連の設定
	mImgW = 153, mImgH = 200;
	mHitRangeW = 12, mHitRangeH = 45;
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
	mItemId = 9;	// 武器変化あり
}
