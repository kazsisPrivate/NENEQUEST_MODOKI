#pragma once
/*
* �r�i�������n�A�C�e���C�U����2�{�j
*/
#include "Item.h"


class Item7 : public Item {
public:
	Item7(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};