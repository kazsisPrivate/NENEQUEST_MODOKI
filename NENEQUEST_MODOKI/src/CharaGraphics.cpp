#include "CharaGraphics.h"
#include "Dxlib.h"

int CharaGraphics::mPl1to3Handle[3][24];
int CharaGraphics::mPl4Handle[32];
int CharaGraphics::mEne1to2Handle[2][4];
int CharaGraphics::mEne3to7Handle[5][8];
int CharaGraphics::mEneBossHandle[24];

//CharaGraphics::CharaGraphics() { //âÊëúÇÃì«Ç›çûÇ›ÇçsÇ§
//	LoadDivGraph("images/player_1-1-3.png", 24, 2, 12, 500, 283, mPl1to3Handle[0]); 
//	LoadDivGraph("images/player_2-1-1.png", 24, 2, 12, 500, 283, mPl1to3Handle[1]);
//	LoadDivGraph("images/player_3-1-1.png", 24, 2, 12, 500, 283, mPl1to3Handle[2]);
//	LoadDivGraph("images/player_4-1-3.png", 32, 2, 16, 500, 283, mPl4Handle);
//
//	LoadDivGraph("images/enemy_1.png", 4, 2, 2, 250, 177, mEne1to2Handle[0]);
//	LoadDivGraph("images/enemy_2.png", 4, 2, 2, 250, 177, mEne1to2Handle[1]);
//	LoadDivGraph("images/enemy_3.png", 8, 2, 4, 393, 177, mEne3to7Handle[0]);
//	LoadDivGraph("images/enemy_4-3.png", 8, 2, 4, 225, 192, mEne3to7Handle[1]);
//	LoadDivGraph("images/enemy_5-3.png", 8, 2, 4, 225, 192, mEne3to7Handle[2]);
//	LoadDivGraph("images/enemy_6.png", 8, 2, 4, 225, 190, mEne3to7Handle[3]);
//	LoadDivGraph("images/enemy_7-3.png", 8, 2, 4, 303, 151, mEne3to7Handle[4]);
//	LoadDivGraph("images/enemy_5-5.png", 24, 2, 12, 958, 600, mEneBossHandle);
//}


//CharaGraphics::~CharaGraphics() {
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 24; j++) {
//			DeleteGraph(mPl1to3Handle[i][j]);
//		}
//	}
//
//	for (int i = 0; i < 32; i++) {
//		DeleteGraph(mPl4Handle[i]);
//	}
//
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 4; j++) {
//			DeleteGraph(mEne1to2Handle[i][j]);
//		}
//	}
//
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 8; j++) {
//			DeleteGraph(mEne3to7Handle[i][j]);
//		}
//	}
//
//	for (int i = 0; i < 24; i++) {
//		DeleteGraph(mEneBossHandle[i]);
//	}
//}


void CharaGraphics::Initialize() {	//âÊëúÇÃì«Ç›çûÇ›
	LoadDivGraph("images/player_1-1-3.png", 24, 2, 12, 500, 283, mPl1to3Handle[0]);
	LoadDivGraph("images/player_2-1-1.png", 24, 2, 12, 500, 283, mPl1to3Handle[1]);
	LoadDivGraph("images/player_3-1-1.png", 24, 2, 12, 500, 283, mPl1to3Handle[2]);
	LoadDivGraph("images/player_4-1-3.png", 32, 2, 16, 500, 283, mPl4Handle);

	LoadDivGraph("images/enemy_1.png", 4, 2, 2, 250, 177, mEne1to2Handle[0]);
	LoadDivGraph("images/enemy_2.png", 4, 2, 2, 250, 177, mEne1to2Handle[1]);
	LoadDivGraph("images/enemy_3.png", 8, 2, 4, 393, 177, mEne3to7Handle[0]);
	LoadDivGraph("images/enemy_4-3.png", 8, 2, 4, 225, 192, mEne3to7Handle[1]);
	LoadDivGraph("images/enemy_5-3.png", 8, 2, 4, 225, 192, mEne3to7Handle[2]);
	LoadDivGraph("images/enemy_6.png", 8, 2, 4, 225, 190, mEne3to7Handle[3]);
	LoadDivGraph("images/enemy_7-3.png", 8, 2, 4, 303, 151, mEne3to7Handle[4]);
	LoadDivGraph("images/enemy_5-5.png", 24, 2, 12, 958, 600, mEneBossHandle);
}


void CharaGraphics::Finalize() {	// âÊëúÇÃçÌèú
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 24; j++) {
			DeleteGraph(mPl1to3Handle[i][j]);
		}
	}

	for (int i = 0; i < 32; i++) {
		DeleteGraph(mPl4Handle[i]);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			DeleteGraph(mEne1to2Handle[i][j]);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			DeleteGraph(mEne3to7Handle[i][j]);
		}
	}

	for (int i = 0; i < 24; i++) {
		DeleteGraph(mEneBossHandle[i]);
	}
}


const int* CharaGraphics::GetGraHandle(const int type, const int num) {

	if (type == 0) {
		if (num != 4) {
			return mPl1to3Handle[num-1];
		}
		else {
			return mPl4Handle;
		}
	}
	else {
		if (num < 3) {
			return mEne1to2Handle[num-1];
		}
		else if (num < 8) {
			return mEne3to7Handle[num-3];
		}
		else if (num == 8){
			return mEneBossHandle;
		}
		else {
			return 0;
		}
	}
}
