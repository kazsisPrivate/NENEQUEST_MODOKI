#pragma once
/*
* Œ•1i•Šíj
*/
#include "Item.h"


class Item8 : public Item {
public:
	Item8(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};