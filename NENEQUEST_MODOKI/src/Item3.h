#pragma once
/*
* 黄りんご（回復系アイテム，回復量4）
*/
#include "Item.h"

class Item3 : public Item {
public:
	Item3(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};