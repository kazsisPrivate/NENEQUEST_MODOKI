#pragma once

// ���i���CItem8�`11�i����j�������_���ŏo�Ă���j

#include "ItemBox.h"


class Item14 : public ItemBox {
public:
	Item14(ItemChanger* changer, const int itemIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	void CreateBoxItem() override;	// ���̒�����o��item�����߁C�쐬����
};