#pragma once

// 赤靴（自強化系アイテム，スピード2倍）

#include "Item.h"


class Item5 : public Item {
public:
	Item5(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
};