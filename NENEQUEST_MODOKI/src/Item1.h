#pragma once

// 赤りんご（回復系アイテム，回復量2）

#include "Item.h"


class Item1 : public Item {
public:
	Item1(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};