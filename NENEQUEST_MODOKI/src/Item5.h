#pragma once

// �ԌC�i�������n�A�C�e���C�X�s�[�h2�{�j

#include "Item.h"


class Item5 : public Item {
public:
	Item5(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};