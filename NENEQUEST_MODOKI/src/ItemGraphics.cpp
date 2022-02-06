#include "ItemGraphics.h"
#include "Dxlib.h"
#include <string>

int ItemGraphics::mIte1to11Handle[11];
int ItemGraphics::mIte12to15Handle[4][2];
int ItemGraphics::mArrowHandle[2];


void ItemGraphics::Initialize() {	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	// Item1`11‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ
	mIte1to11Handle[0] = LoadGraph("images/item1.png");
	mIte1to11Handle[1] = LoadGraph("images/item2.png");
	mIte1to11Handle[2] = LoadGraph("images/item3.png");
	mIte1to11Handle[3] = LoadGraph("images/item4.png");
	mIte1to11Handle[4] = LoadGraph("images/item5.png");
	mIte1to11Handle[5] = LoadGraph("images/item6.png");
	mIte1to11Handle[6] = LoadGraph("images/item7.png");
	mIte1to11Handle[7] = LoadGraph("images/item8.png");
	mIte1to11Handle[8] = LoadGraph("images/item9.png");
	mIte1to11Handle[9] = LoadGraph("images/item10.png");
	mIte1to11Handle[10] = LoadGraph("images/item11.png");

	// Item12`15‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ
	LoadDivGraph("images/item12.png", 2, 2, 1, 162, 160, mIte12to15Handle[0]);
	LoadDivGraph("images/item13.png", 2, 2, 1, 162, 160, mIte12to15Handle[1]);
	LoadDivGraph("images/item14.png", 2, 2, 1, 164, 160, mIte12to15Handle[2]);
	LoadDivGraph("images/item15.png", 2, 2, 1, 164, 160, mIte12to15Handle[3]);

	// Arrow‚Ì‰æ‘œ‚Ì“Ç‚İ‚İ
	mArrowHandle[0] = LoadGraph("images/arrow1.png");
	mArrowHandle[1] = LoadGraph("images/arrow2.png");
}


void ItemGraphics::Finalize() {	// ‰æ‘œ‚Ìíœ
	// Item1`11‚Ì‰æ‘œ‚Ìíœ
	for (int i = 0; i < 11; i++) {
		DeleteGraph(mIte1to11Handle[i]);
	}

	// Item12`15‚Ì‰æ‘œ‚Ìíœ
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			DeleteGraph(mIte12to15Handle[i][j]);
		}
	}

	// Arrow‚Ì‰æ‘œ‚Ìíœ
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mArrowHandle[i]);
	}
}


int* ItemGraphics::GetGraHandle(const int charaId) {
	if (charaId <= 11) {	// Item1`11
		return &mIte1to11Handle[charaId-1];
	}
	else if (charaId <= 15) {	// Item12`15
		return mIte12to15Handle[charaId-12];
	}
	else {	// Arrow
		return &mArrowHandle[charaId - 16];
	}
}
