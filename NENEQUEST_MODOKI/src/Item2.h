#pragma once

// ��񂲁i�񕜌n�A�C�e���C�񕜗�-1�j

#include "Item.h"


class Item2 : public Item {
public:
	Item2(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};