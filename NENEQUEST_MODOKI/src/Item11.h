#pragma once

// �|�i����j

#include "Item.h"


class Item11 : public Item {
public:
	Item11(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};