// 箱（箱，Item8～11（武器）がランダムで出てくる）
#include "Item14.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <random>


Item14::Item14(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: ItemBox(changer, ItemGraphics::GetGraHandle(14), itemIdx, x, y) {
}


void Item14::Initialize() {
	ItemBox::Initialize();

	// 当たり判定関連の設定
	mImgW = 164, mImgH = 160;
	mHitRangeW = 35, mHitRangeH = 35;

	// 得られるスコア
	mScore = 100;

	// その他の設定
	mItemId = 13;
}


void Item14::CreateBoxItem() {
	// 1～100のランダムな数値を生成
	std::random_device rnd;
	int randNum = rnd() % 100 + 1;

	if (randNum <= 25) {	// 25%の確率で
		// 剣1（Item8）
		mBoxItemEnum = eItem8;
		mBoxItemHandle = ItemGraphics::GetGraHandle(8);
		mBoxIteImgW = 121, mBoxIteImgH = 205;
	}
	else if (randNum <= 50) {	// 25%の確率で
		// 剣2（Item9）
		mBoxItemEnum = eItem9;
		mBoxItemHandle = ItemGraphics::GetGraHandle(9);
		mBoxIteImgW = 153, mBoxIteImgH = 200;
	}
	else if (randNum <= 75) {	// 25%の確率で
		// 斧（Item10）
		mBoxItemEnum = eItem10;
		mBoxItemHandle = ItemGraphics::GetGraHandle(10);
		mBoxIteImgW = 144, mBoxIteImgH = 200;
	}
	else {	// 25%の確率で
		// 弓（Item11）
		mBoxItemEnum = eItem11;
		mBoxItemHandle = ItemGraphics::GetGraHandle(11);
		mBoxIteImgW = 130, mBoxIteImgH = 147;
	}
}