#pragma once

// �Ԃ�񂲁i�񕜌n�A�C�e���C�񕜗�2�j

#include "Item.h"


class Item1 : public Item {
public:
	Item1(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};