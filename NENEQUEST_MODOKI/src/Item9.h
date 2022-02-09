#pragma once

// Œ•2i•Šíj

#include "Item.h"


class Item9 : public Item {
public:
	Item9(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};