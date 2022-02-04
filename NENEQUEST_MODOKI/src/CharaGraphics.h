#pragma once

static class CharaGraphics { //���̃N���X�͓ǂݍ��ݎ��Ԃ��������Ă��܂��A��ʂ��ł܂�̂�h�����߂̃N���X�ł��邽�߁APlayer,Enemy�ȊO�̉摜�͂Ȃ��B
public:
	/*CharaGraphics();
	~CharaGraphics();*/
	static const int* GetGraHandle(const int type, const int num); //type==0 �Ȃ�Player�Atype==1�Ȃ�Enemy�Bnum��_�̌��̐���(Boss��8, None��9)�B
	static void Initialize();
	static void Finalize();

//private:
    static int mPl1to3Handle[3][24]; //Player_1�`3
	static int mPl4Handle[32]; //Player_4
	static int mEne1to2Handle[2][4]; //Enemy_1�`2
	static int mEne3to7Handle[5][8]; //Enemy_3�`7
	static int mEneBossHandle[24]; //Enemy_Boss
};