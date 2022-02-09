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
	void Jump();	// 箱が割れたときに箱から飛び出すitemの処理で使用する

	int mHandleNumber;	// 箱の割れていない画像と割れている画像の切り替えで使用する
	int* mBoxItemHandle;	// 箱から飛び出したitemの画像
	int mBoxItemX, mBoxItemY;	// 箱から飛び出したitemのx, y座標
	int mBoxIteImgW, mBoxIteImgH;	// 箱から飛び出したitemの画像のサイズ
	bool mIsJumping;	// 箱から飛び出したitemがジャンプをしているときtrue
	int mBoxItemYPrev;	// ジャンプの処理で使用する
	int mJumpFrameCnt;	// ジャンプしているフレーム数のカウント
	const int JUMP_FRAME_NUM = 33;	// ジャンプに使用するフレーム数
	EItem mBoxItemEnum;	// 箱から飛び出したItem
};
