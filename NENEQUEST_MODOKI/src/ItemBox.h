#pragma once

#include "Item.h"


class ItemBox : public Item {
public:
	ItemBox(ItemChanger* changer, const int* graph, const int itemIdx, const int x, const int y);
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

protected:
	virtual void CreateBoxItem() = 0;
	void Jump();	// �������ꂽ�Ƃ��ɔ������яo��item�̏����Ŏg�p����

	int mHandleNumber;	// ���̊���Ă��Ȃ��摜�Ɗ���Ă���摜�̐؂�ւ��Ŏg�p����
	int* mBoxItemHandle;	// �������яo����item�̉摜
	int mBoxItemX, mBoxItemY;	// �������яo����item��x, y���W
	int mBoxIteImgW, mBoxIteImgH;	// �������яo����item�̉摜�̃T�C�Y
	bool mIsJumping;	// �������яo����item���W�����v�����Ă���Ƃ�true
	int mBoxItemYPrev;	// �W�����v�̏����Ŏg�p����
	int mJumpFrameCnt;	// �W�����v���Ă���t���[�����̃J�E���g
	const int JUMP_FRAME_NUM = 33;	// �W�����v�Ɏg�p����t���[����
	EItem mBoxItemEnum;	// �������яo����Item
};
