#pragma once

// 箱（箱，Item8～11（武器）がランダムで出てくる）

#include "ItemBox.h"


class Item14 : public ItemBox {
public:
	Item14(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	void CreateBoxItem() override;	// 箱の中から出すitemを決め，作成する
};