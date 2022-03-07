#pragma once
/*
* •€i•Šíj
*/
#include "Item.h"


class Item10 : public Item {
public:
	Item10(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};