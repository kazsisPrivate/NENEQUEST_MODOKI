// 腕（自強化系アイテム，攻撃力2倍）
#include "Item7.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item7::Item7(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(7), itemIdx, x, y) {
}


void Item7::Initialize() {
	// 当たり判定関連の設定
	mImgW = 122, mImgH = 102;
	mHitRangeW = 25, mHitRangeH = 20;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsDead = false;

	// 得られるスコア
	mScore = 100;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;	
	mAttackPower = 2;	// 攻撃力アップ効果あり
	mItemId = 7;
}