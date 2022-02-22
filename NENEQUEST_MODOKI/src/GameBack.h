#pragma once

#include "BasicFunc.h"

class GameBack : BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void UpdateNormalBack();	// BossStage�ɓ���܂ł̔w�i�̍X�V����
	void UpdateBossBack();	// BossStage�ɓ�������̔w�i�̍X�V����
	void StartChangingSt();	// BossStage�ւ̈ڍs���n�߂�ۂ̏����CGameScene������Ăт���
	int GetBsStX();	// BossStage��x���W��Ԃ��CEnemyBoss�̍쐬�̍�(BossStage�ւ̈ڍs���n�߂��)��GameScene������Ăт���
	bool GetIsAtBsSt();	// BossStage�ɓ��������ǂ�����Ԃ�

private:
	const int BACK_X_MIN = -1280, BACK_X_MAX = 1280;	// �w�i�摜�̈ړ��͈͂̍��[�ƉE�[��x���W
	const int STAGE_IMG_W = 1280, STAGE_IMG_H = 720;	// NormalStage��BackStage�̉摜�̃T�C�Y
	int mNorStHandles[2];	// NormalStage�̉摜
	int mCloudHandles[2];	// �_�̉摜
	int mBsStHandle; // BossStage�̉摜
	int mNorStXs[2];	// �eNormalStage�̉摜�̍��[��x���W
	float mCloudXs[2];	// �e�_�̉摜�̍��[��x���W
	int mBsStX;	// BossStage�̉摜�̍��[��x���W
	const int BRIDGE_LX = 690;	// BossStage�̔w�i�摜���̋��̍��[��x���W
	//const int UPDATE_FRAME_NUM = 3;	// �X�V���s���^�C�~���O�iUPDATE_CNT_NUM��2�Ȃ��2�t���[�����ɍX�V����j
	//int mUpdFraCnt;	// �X�V�t���[�����̃J�E���g�CUPDATE_FRAME_NUM�ɂȂ�����0�ɖ߂�
	//int mBackChCnt; //�i�F������ւ�����񐔁A�܂�mountainHandle��-1280�ɓ��B���邲�Ƃ�1�����Ă����A�{�X�o�g���ɓ������Ƃ��̌i�F�̕ύX�Aplayer�Ƀ{�X�o�g���ɓ������Ƃ����̂�m�点��̂Ɏg��
	bool mIsChangingSt;	// BossStage�֕ύX���ł�������true
	bool mIsMovingNorSts[2];	// BossStage�ւ̕ύX���̂Ƃ��C�eNormalStage�𓮂����Ă���Ƃ�true
	//bool mIsMovingBsSt;	// BossStage�ւ̕ύX���̂Ƃ��CBossStage�𓮂����Ă���Ƃ�true
	bool mIsAtBsSt;	// BossStage�ɂ�����true
};