// 樽2（箱，Item1～7がランダムで出てくる）
#include "Item13.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <time.h>


Item13::Item13(ItemChanger* changer, const int itemIdx, const int x, const int y)
	: ItemBox(changer, ItemGraphics::GetGraHandle(13), itemIdx, x, y) {
}


void Item13::Initialize() {
	ItemBox::Initialize();

	// 当たり判定関連の設定
	mImgW = 162, mImgH = 160;
	mHitRangeW = 35, mHitRangeH = 35;

	// 得られるスコア
	mScore = 100;

	// その他の設定
	mItemId = 13;
}


void Item13::Draw() {
	ItemBox::Draw();
}


void Item13::Update() {
	ItemBox::Update();
}


void Item13::CreateBoxItem() {
	// 1～100のランダムな数値を生成
	srand((unsigned int)time(NULL));
	int randNum = rand() % 100 + 1;

	if (randNum <= 10) {	// 10%の確率で
		// 赤りんご（Item1）
		mBoxItemEnum = eItem1;
		mBoxItemHandle = ItemGraphics::GetGraHandle(1);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 20) {	// 10%の確率で
		// 青りんご（Item2）
		mBoxItemEnum = eItem2;
		mBoxItemHandle = ItemGraphics::GetGraHandle(2);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 45) {	// 25%の確率で
		// 黄りんご（Item3）
		mBoxItemEnum = eItem3;
		mBoxItemHandle = ItemGraphics::GetGraHandle(3);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 70) {	// 25%の確率で
		// 紫りんご（Item4）
		mBoxItemEnum = eItem4;
		mBoxItemHandle = ItemGraphics::GetGraHandle(4);
		mBoxIteImgW = 100, mBoxIteImgH = 90;
	}
	else if (randNum <= 80) {	// 10%の確率で
		// 赤靴（Item5）
		mBoxItemEnum = eItem5;
		mBoxItemHandle = ItemGraphics::GetGraHandle(5);
		mBoxIteImgW = 128, mBoxIteImgH = 100;
	}
	else if (randNum <= 90) {	// 10%の確率で
		// 青靴（Item6）
		mBoxItemEnum = eItem6;
		mBoxItemHandle = ItemGraphics::GetGraHandle(6);
		mBoxIteImgW = 128, mBoxIteImgH = 100;
	}
	else {	// 10%の確率で
		// 腕（Item7）
		mBoxItemEnum = eItem7;
		mBoxItemHandle = ItemGraphics::GetGraHandle(7);
		mBoxIteImgW = 122, mBoxIteImgH = 102;
	}
}