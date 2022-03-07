#pragma once
/*
* 青靴（自強化系アイテム，スピード0.5倍）
*/
#include "Item.h"


class Item6 : public Item {
public:
	Item6(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};