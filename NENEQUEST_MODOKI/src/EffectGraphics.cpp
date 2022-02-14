#include "EffectGraphics.h"
#include "Dxlib.h"
#include <string>

int EffectGraphics::mEfe1to3Handles[3];
int EffectGraphics::mArrowHitHandle;
int EffectGraphics::mMgFireHandles[2];
int EffectGraphics::mSlashHandle[4];
int EffectGraphics::mBsFireHandles[2][2];
int EffectGraphics::mBsFireBreHandles[2];


void EffectGraphics::Initialize() {	// �摜�̓ǂݍ���
	// Effect1�`3�iItem5�`7�̌��ʁj�̉摜�̓ǂݍ���
	mEfe1to3Handles[0] = LoadGraph("images/effect1.png");
	mEfe1to3Handles[1] = LoadGraph("images/effect2.png");
	mEfe1to3Handles[2] = LoadGraph("images/effect3.png");

	// Arrow�����������Ƃ��̃G�t�F�N�g�̉摜�̓ǂݍ���
	mArrowHitHandle = LoadGraph("images/arrowhit.png");

	// Enemy4, 5, 6���g�p����΂̋ʁiEnemy4, 5�͐Ԃ��΂̋ʁCEnemy6�͐��΂̋ʁj�̉摜�̓ǂݍ���
	mMgFireHandles[0] = LoadGraph("images/fire1.png");
	mMgFireHandles[1] = LoadGraph("images/fire2.png");

	// Enemy7���g�p���銙�U���̃G�t�F�N�g�̉摜�̓ǂݍ���
	LoadDivGraph("images/slash.png", 4, 2, 2, 250, 150, mSlashHandle);
	
	// EnemyBoss���f���΂̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)�̉摜�̓ǂݍ���
	LoadDivGraph("images/bossfire1.png", 2, 1, 2, 208, 208, mBsFireHandles[0]);
	LoadDivGraph("images/bossfire2.png", 2, 1, 2, 208, 208, mBsFireHandles[1]);

	// EnemyBoss���f���΂̑��̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)�̉摜�̓ǂݍ���
	mBsFireBreHandles[0] = LoadGraph("images/bossfirebreath1.png");
	mBsFireBreHandles[1] = LoadGraph("images/bossfirebreath2.png");
}


void EffectGraphics::Finalize() {	// �摜�̍폜
	// Effect1�`3�iItem5�`7�̌��ʁj�̉摜�̍폜
	for (int i = 0; i < 3; i++) {
		DeleteGraph(mEfe1to3Handles[i]);
	}

	// Arrow�����������Ƃ��̃G�t�F�N�g�̉摜�̍폜
	DeleteGraph(mArrowHitHandle);

	// Enemy4, 5, 6���g�p����΂̋ʁiEnemy4, 5�͐Ԃ��΂̋ʁCEnemy6�͐��΂̋ʁj�̉摜�̍폜
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mSlashHandle[i]);
	}

	// Enemy7���g�p���銙�U���̃G�t�F�N�g�̉摜�̍폜
	for (int i = 0; i < 4; i++) {
		DeleteGraph(mEfe1to3Handles[i]);
	}

	// EnemyBoss���f���΂̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)�̉摜�̍폜
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DeleteGraph(mBsFireHandles[i][j]);
		}
	}

	// EnemyBoss���f���΂̑��̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)�̉摜�̍폜
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mBsFireBreHandles[i]);
	}
}


int* EffectGraphics::GetGraHandle(const int efeId) {
	if (efeId <= 3) {	// Effect1�`3�iItem5�`7�̌��ʁj
		return &mEfe1to3Handles[efeId - 1];
	}
	else if (efeId <= 4) {	// Arrow�����������Ƃ��̃G�t�F�N�g
		return &mArrowHitHandle;
	}
	else if (efeId <= 6) {	// Enemy4, 5, 6���g�p����΂̋ʁiEnemy4, 5�͐Ԃ��΂̋ʁCEnemy6�͐��΂̋ʁj
		return &mMgFireHandles[efeId - 5];
	}
	else if (efeId <= 7) {	// Enemy7���g�p���銙�U���̃G�t�F�N�g
		return mSlashHandle;
	}
	else if (efeId <= 9) {	// EnemyBoss���f���΂̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)
		return mBsFireHandles[efeId - 8];
	}
	else {	// EnemyBoss���f���΂̑��̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)
		return &mBsFireBreHandles[efeId - 10];
	}
}
