#pragma once

typedef enum {
	eItem1,
	eItem2,
	eItem3,
	eItem4,
	eItem5,
	eItem6,
	eItem7,
	eItem8, 
	eItem9,
	eItem10,
	eItem11,
	eItem12,
	eItem13,
	eItem14,
	eItemNULL,
	eItemNone
} EItem;

class ItemChanger {
public:
	virtual void ChangeItem(const int itemIdx, EItem itemNext, 
		const int itemNextX, const int itemNextY) = 0;	// �w�肵���C���f�b�N�X�ԍ���Item�ϐ��Ɏ��ɃZ�b�g����悤�ɂ���(���W���w��)
};
