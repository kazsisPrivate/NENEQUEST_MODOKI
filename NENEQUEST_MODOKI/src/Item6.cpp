// 青靴（自強化系アイテム，スピード0.5倍）
#include "Item6.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item6::Item6(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(6), itemIdx, x, y) {
}


void Item6::Initialize() {
	// 当たり判定関連の設定
	mImgW = 128, mImgH = 100;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// 得られるスコア
	mScore = 1000;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 0.5f;	// スピードダウン効果あり
	mAttackPower = 1;
	mItemId = 6;
}