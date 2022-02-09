#pragma once

// 青りんご（回復系アイテム，回復量-1）

#include "Item.h"


class Item2 : public Item {
public:
	Item2(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};