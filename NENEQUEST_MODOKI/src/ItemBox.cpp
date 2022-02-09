#include "ItemBox.h"
#include "Dxlib.h"


ItemBox::ItemBox(ItemChanger* changer, const int* graph, const int itemIdx, const int x, const int y) 
	: Item(changer, graph, itemIdx, x, y) {
}


void ItemBox::Initialize() {
	// 当たり判定関連の設定
	mPlIsHit = false;
	mPlAIsHit = false;

	// ItemBoxのみがもつ変数の設定
	mBoxItemEnum = eItemNULL;
	mBoxItemX = -1000, mBoxItemY = -1000;
	mJumpFrameCnt = 0;

	// その他の設定
	mSpeed = 2.0f;
	mHealPower = 0;
	mSpeedPower = 1.0f;
	mAttackPower = 1;
}


void ItemBox::Draw() {
	// 箱の描画
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, mIteHandle[mHandleNumber], TRUE);

	// 箱から飛び出したitemの描画
	if (mIsJumping) {
		DrawGraph(mBoxItemX - mBoxIteImgW / 2, mBoxItemY - mBoxIteImgH / 2, *mBoxItemHandle, TRUE);
	}
}


void ItemBox::Update() {
	if (mX < ITEM_DELETE_X) {	// 画面外に移動したとき
		mItemChanger->ChangeItem(mItemIdx, eItemNULL, -1000, -1000);	// -1000は適当に画面外の数値にしている
	}
	else if (mIsJumping) {	// 箱が割られて，itemが箱から飛び出しているとき
		if (mJumpFrameCnt == JUMP_FRAME_NUM) {	// 箱から飛び出したItemが着地したら
			mItemChanger->ChangeItem(mItemIdx, mBoxItemEnum, mBoxItemX, mBoxItemY);
		}
		else {
			Jump();
		}
	}
	else {
		if (mPlAIsHit) {	// Playerの攻撃が箱に当たったら
			// 割れている箱の画像を映すようにする
			mHandleNumber = 1;

			// Jumpに使用する変数の設定
			mIsJumping = true;
			mJumpFrameCnt = 0;

			mBoxItemX = mX;
			mBoxItemY = mY;
			mBoxItemYPrev = mBoxItemY;
			mBoxItemY = mBoxItemY - 17;

			// 箱から飛び出すitemを作成
			CreateBoxItem();
		}
		else {
			// 移動
			Move();
		}
	}
}


void ItemBox::Jump() {
	// x座標の更新
	mBoxItemX += 15;

	// y座標の更新
	int boxItemYTemp = mBoxItemY;
	mBoxItemY += (mBoxItemY - mBoxItemYPrev) + 1;
	mBoxItemYPrev = boxItemYTemp;

	mJumpFrameCnt++;
}