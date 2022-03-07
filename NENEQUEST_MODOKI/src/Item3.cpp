// 黄りんご（回復系アイテム，回復量4）
#include "Item3.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item3::Item3(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(3), itemIdx, x, y) {
}


void Item3::Initialize() {
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
	mHealPower = 4;	// 回復効果あり
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 3;
}
