#pragma once
/*
* 樽2（箱，Item1〜7がランダムで出てくる）
*/
#include "ItemBox.h"


class Item13 : public ItemBox {
public:
	Item13(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;

private:
	void CreateBoxItem() override;	// 箱の中から出すitemを決め，作成する
};