#pragma once

// �M2�i���CItem1�`7�������_���ŏo�Ă���j

#include "ItemBox.h"


class Item13 : public ItemBox {
public:
	Item13(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	void CreateBoxItem() override;	// ���̒�����o��item�����߁C�쐬����
};