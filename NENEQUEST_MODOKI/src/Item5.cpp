// 赤靴（自強化系アイテム，スピード2倍）
#include "Item5.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item5::Item5(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(5), itemIdx, x, y) {
}


void Item5::Initialize() {
	// 当たり判定関連の設定
	mImgW = 128, mImgH = 100;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = 0;	
	mSpeedPower = 2.0f;	// スピードアップ効果あり
	mAttackPower = 1;
	mItemId = 5;
}