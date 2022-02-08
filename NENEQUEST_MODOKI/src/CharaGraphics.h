#pragma once

static class CharaGraphics {	// �摜�̓ǂݍ��ݎ��ԍ팸�̂��߂̃N���X
public:
	static const int* GetGraHandle(const int type, const int charaId);	// type==0 �Ȃ�Player�Ctype==1�Ȃ�Enemy�DcharaId�͊e�L�����̃t�@�C�����ɂ���ԍ�(Boss��8, None��9)
	static void Initialize();
	static void Finalize();

private:
    static int mPl1to3Handles[3][24];	// Player1�`3
	static int mPl4Handle[32];	// Player4
	static int mEne1to2Handles[2][4];	// Enemy1�`2
	static int mEne3to7Handles[5][8];	// Enemy3�`7
	static int mEneBossHandle[24];	// EnemyBoss
};