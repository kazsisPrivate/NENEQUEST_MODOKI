#pragma once

static class EffectGraphics {	// �摜�̓ǂݍ��ݎ��ԍ팸�̂��߂̃N���X
public:
	static int* GetGraHandle(const int efeId);
	static void Initialize();
	static void Finalize();

private:
    static int mEfe1to3Handles[3];	// Effect1�`3�iItem5�`7�̌��ʁj
	static int mArrowHitHandle;	// Arrow�����������Ƃ��̃G�t�F�N�g
	static int mFireHandles[2];	// Enemy4, 5, 6���g�p����΂̋ʁiEnemy4, 5�͐Ԃ��΂̋ʁCEnemy6�͐��΂̋ʁj
	static int mSlashHandle[4];	// Enemy7���g�p���銙�U���̃G�t�F�N�g
	static int mBsFireHandles[2][2];	// EnemyBoss���f���΂̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)
	static int mBsFireBreHandles[2];	// EnemyBoss���f���΂̑��̋�(�ʏ탂�[�h�̉΂̋ʂƓ{�胂�[�h�̉΂̋�)
};