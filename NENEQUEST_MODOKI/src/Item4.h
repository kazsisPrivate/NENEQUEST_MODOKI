#pragma once
/*
* ����񂲁i�񕜌n�A�C�e���C�񕜗�-3�j
*/
#include "Item.h"


class Item4 : public Item {
public:
	Item4(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};