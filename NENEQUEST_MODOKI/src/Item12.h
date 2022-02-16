#pragma once

// 樽1（箱，Item1～2, 5～7がランダムで出てくる）

#include "ItemBox.h"


class Item12 : public ItemBox {
public:
	Item12(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;

private:
	void CreateBoxItem() override;	// 箱の中から出すitemを決め，作成する
};