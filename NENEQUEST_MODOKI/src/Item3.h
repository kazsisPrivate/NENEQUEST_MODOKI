#pragma once
/*
* ����񂲁i�񕜌n�A�C�e���C�񕜗�4�j
*/
#include "Item.h"

class Item3 : public Item {
public:
	Item3(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};