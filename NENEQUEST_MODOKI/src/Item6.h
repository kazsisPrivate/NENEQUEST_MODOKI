#pragma once
/*
* �C�i�������n�A�C�e���C�X�s�[�h0.5�{�j
*/
#include "Item.h"


class Item6 : public Item {
public:
	Item6(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};