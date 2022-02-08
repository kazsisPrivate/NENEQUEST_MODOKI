#pragma once

static class CharaGraphics {	// 画像の読み込み時間削減のためのクラス
public:
	static const int* GetGraHandle(const int type, const int charaId);	// type==0 ならPlayer，type==1ならEnemy．charaIdは各キャラのファイル名にある番号(Bossは8, Noneは9)
	static void Initialize();
	static void Finalize();

private:
    static int mPl1to3Handles[3][24];	// Player1～3
	static int mPl4Handle[32];	// Player4
	static int mEne1to2Handles[2][4];	// Enemy1～2
	static int mEne3to7Handles[5][8];	// Enemy3～7
	static int mEneBossHandle[24];	// EnemyBoss
};