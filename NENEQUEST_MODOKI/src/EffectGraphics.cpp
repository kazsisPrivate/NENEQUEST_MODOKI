#include "EffectGraphics.h"
#include "Dxlib.h"
#include <string>

int EffectGraphics::mEfe1to3Handles[3];
int EffectGraphics::mArrowHitHandle;
int EffectGraphics::mMgFireHandles[2];
int EffectGraphics::mSlashHandle[4];
int EffectGraphics::mBsFireHandles[2][2];
int EffectGraphics::mBsFireBreHandles[2];


void EffectGraphics::Initialize() {	// 画像の読み込み
	// Effect1～3（Item5～7の効果）の画像の読み込み
	mEfe1to3Handles[0] = LoadGraph("images/effect1.png");
	mEfe1to3Handles[1] = LoadGraph("images/effect2.png");
	mEfe1to3Handles[2] = LoadGraph("images/effect3.png");

	// Arrowが当たったときのエフェクトの画像の読み込み
	mArrowHitHandle = LoadGraph("images/arrowhit.png");

	// Enemy4, 5, 6が使用する火の玉（Enemy4, 5は赤い火の玉，Enemy6は青い火の玉）の画像の読み込み
	mMgFireHandles[0] = LoadGraph("images/fire1.png");
	mMgFireHandles[1] = LoadGraph("images/fire2.png");

	// Enemy7が使用する鎌攻撃のエフェクトの画像の読み込み
	LoadDivGraph("images/slash.png", 4, 2, 2, 250, 150, mSlashHandle);
	
	// EnemyBossが吐く火の玉(通常モードの火の玉と怒りモードの火の玉)の画像の読み込み
	LoadDivGraph("images/bossfire1.png", 2, 1, 2, 208, 208, mBsFireHandles[0]);
	LoadDivGraph("images/bossfire2.png", 2, 1, 2, 208, 208, mBsFireHandles[1]);

	// EnemyBossが吐く火の息の玉(通常モードの火の玉と怒りモードの火の玉)の画像の読み込み
	mBsFireBreHandles[0] = LoadGraph("images/bossfirebreath1.png");
	mBsFireBreHandles[1] = LoadGraph("images/bossfirebreath2.png");
}


void EffectGraphics::Finalize() {	// 画像の削除
	// Effect1～3（Item5～7の効果）の画像の削除
	for (int i = 0; i < 3; i++) {
		DeleteGraph(mEfe1to3Handles[i]);
	}

	// Arrowが当たったときのエフェクトの画像の削除
	DeleteGraph(mArrowHitHandle);

	// Enemy4, 5, 6が使用する火の玉（Enemy4, 5は赤い火の玉，Enemy6は青い火の玉）の画像の削除
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mSlashHandle[i]);
	}

	// Enemy7が使用する鎌攻撃のエフェクトの画像の削除
	for (int i = 0; i < 4; i++) {
		DeleteGraph(mEfe1to3Handles[i]);
	}

	// EnemyBossが吐く火の玉(通常モードの火の玉と怒りモードの火の玉)の画像の削除
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DeleteGraph(mBsFireHandles[i][j]);
		}
	}

	// EnemyBossが吐く火の息の玉(通常モードの火の玉と怒りモードの火の玉)の画像の削除
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mBsFireBreHandles[i]);
	}
}


int* EffectGraphics::GetGraHandle(const int efeId) {
	if (efeId <= 3) {	// Effect1～3（Item5～7の効果）
		return &mEfe1to3Handles[efeId - 1];
	}
	else if (efeId <= 4) {	// Arrowが当たったときのエフェクト
		return &mArrowHitHandle;
	}
	else if (efeId <= 6) {	// Enemy4, 5, 6が使用する火の玉（Enemy4, 5は赤い火の玉，Enemy6は青い火の玉）
		return &mMgFireHandles[efeId - 5];
	}
	else if (efeId <= 7) {	// Enemy7が使用する鎌攻撃のエフェクト
		return mSlashHandle;
	}
	else if (efeId <= 9) {	// EnemyBossが吐く火の玉(通常モードの火の玉と怒りモードの火の玉)
		return mBsFireHandles[efeId - 8];
	}
	else {	// EnemyBossが吐く火の息の玉(通常モードの火の玉と怒りモードの火の玉)
		return &mBsFireBreHandles[efeId - 10];
	}
}
