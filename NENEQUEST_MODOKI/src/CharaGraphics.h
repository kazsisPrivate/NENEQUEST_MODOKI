#pragma once

static class CharaGraphics { //このクラスは読み込み時間がかかってしまい、画面が固まるのを防ぐためのクラスであるため、Player,Enemy以外の画像はない。
public:
	/*CharaGraphics();
	~CharaGraphics();*/
	static const int* GetGraHandle(const int type, const int num); //type==0 ならPlayer、type==1ならEnemy。numは_の後ろの数字(Bossは8, Noneは9)。
	static void Initialize();
	static void Finalize();

//private:
    static int mPl1to3Handle[3][24]; //Player_1～3
	static int mPl4Handle[32]; //Player_4
	static int mEne1to2Handle[2][4]; //Enemy_1～2
	static int mEne3to7Handle[5][8]; //Enemy_3～7
	static int mEneBossHandle[24]; //Enemy_Boss
};