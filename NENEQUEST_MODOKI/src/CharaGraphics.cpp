#include "CharaGraphics.h"
#include "Dxlib.h"

int CharaGraphics::mPl1to3Handles[3][24];
int CharaGraphics::mPl4Handle[32];
int CharaGraphics::mEne1to2Handles[2][4];
int CharaGraphics::mEne3to7Handles[5][8];
int CharaGraphics::mEneBossHandle[24];


void CharaGraphics::Initialize() {	// ζΜΗέέ
	// Player1`3ΜζΜΗέέ
	LoadDivGraph("images/player1.png", 24, 2, 12, 500, 283, mPl1to3Handles[0]);
	LoadDivGraph("images/player2.png", 24, 2, 12, 500, 283, mPl1to3Handles[1]);
	LoadDivGraph("images/player3.png", 24, 2, 12, 500, 283, mPl1to3Handles[2]);

	// Player4ΜζΜΗέέ
	LoadDivGraph("images/player4.png", 32, 2, 16, 500, 283, mPl4Handle);

	// Enemy1`2ΜζΜΗέέ
	LoadDivGraph("images/enemy1.png", 4, 2, 2, 250, 177, mEne1to2Handles[0]);
	LoadDivGraph("images/enemy2.png", 4, 2, 2, 250, 177, mEne1to2Handles[1]);

	// Enemy3`7ΜζΜΗέέ
	LoadDivGraph("images/enemy3.png", 8, 2, 4, 393, 177, mEne3to7Handles[0]);
	LoadDivGraph("images/enemy4.png", 8, 2, 4, 225, 192, mEne3to7Handles[1]);
	LoadDivGraph("images/enemy5.png", 8, 2, 4, 225, 192, mEne3to7Handles[2]);
	LoadDivGraph("images/enemy6.png", 8, 2, 4, 225, 190, mEne3to7Handles[3]);
	LoadDivGraph("images/enemy7.png", 8, 2, 4, 303, 151, mEne3to7Handles[4]);

	// EnemyBossΜζΜΗέέ
	LoadDivGraph("images/enemyboss.png", 24, 2, 12, 958, 600, mEneBossHandle);
}


void CharaGraphics::Finalize() {	// ζΜν
	// Player1`3ΜζΜν
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 24; j++) {
			DeleteGraph(mPl1to3Handles[i][j]);
		}
	}

	// Player4ΜζΜν
	for (int i = 0; i < 32; i++) {
		DeleteGraph(mPl4Handle[i]);
	}

	// Enemy1`2ΜζΜν
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			DeleteGraph(mEne1to2Handles[i][j]);
		}
	}

	// Enemy3`7ΜζΜν
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			DeleteGraph(mEne3to7Handles[i][j]);
		}
	}

	// EnemyBossΜζΜν
	for (int i = 0; i < 24; i++) {
		DeleteGraph(mEneBossHandle[i]);
	}
}


int* CharaGraphics::GetGraHandle(const int type, const int charaId) {
	if (type == 0) {	// Player
		if (charaId != 4) {
			return mPl1to3Handles[charaId-1];
		}
		else {
			return mPl4Handle;
		}
	}
	else {	// Enemy
		if (charaId <= 2) {
			return mEne1to2Handles[charaId-1];
		}
		else if (charaId <= 7) {
			return mEne3to7Handles[charaId-3];
		}
		else {
			return mEneBossHandle;
		}
	}
}
