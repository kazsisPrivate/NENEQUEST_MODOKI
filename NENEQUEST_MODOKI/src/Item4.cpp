// 紫りんご（回復系アイテム，回復量-3）
#include "Item4.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item4::Item4(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(4), itemIdx, x, y) {
}


void Item4::Initialize() {
	// 当たり判定関連の設定
	mImgW = 100, mImgH = 90;
	mHitRangeW = 23, mHitRangeH = 15;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsChangingItem = false;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = -3;	// 回復効果あり
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 4;
}
