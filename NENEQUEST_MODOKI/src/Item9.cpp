// Œ•1i•Šíj
#include "Item9.h"
#include "DxLib.h"
#include "ItemGraphics.h"


Item9::Item9(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: Item(changer, ItemGraphics::GetGraHandle(9), itemIdx, x, y) {
}


void Item9::Initialize() {
	// “–‚½‚è”»’èŠÖ˜A‚Ìİ’è
	mImgW = 153, mImgH = 200;
	mHitRangeW = 12, mHitRangeH = 45;
	mPlIsHit = false;
	mPlAIsHit = false;
	mIsChangingItem = false;

	// ‚»‚Ì‘¼‚Ìİ’è
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
	mItemId = 9;	// •Ší•Ï‰»‚ ‚è
}
