#pragma once
/*
* 紫りんご（回復系アイテム，回復量-3）
*/
#include "Item.h"


class Item4 : public Item {
public:
	Item4(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};