#pragma once

// �M1�i���CItem1�`2, 5�`7�������_���ŏo�Ă���j

#include "ItemBox.h"


class Item12 : public ItemBox {
public:
	Item12(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;

private:
	void CreateBoxItem() override;	// ���̒�����o��item�����߁C�쐬����
};