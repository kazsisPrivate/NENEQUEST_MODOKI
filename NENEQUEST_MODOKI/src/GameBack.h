#pragma once
/*
* GameScene�ɂ�����C�w�i�̃N���X
*/
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
	const int STAGE_IMG_W = 1280, STAGE_IMG_H = 720;	// NormalStage��BackStage�̉摜�̃T�C�Y
	int mNorStHandles[2];	// NormalStage�̉摜
	int mCloudHandles[2];	// �_�̉摜
	int mBsStHandle; // BossStage�̉摜

	const int BACK_X_MIN = -1280, BACK_X_MAX = 1280;	// �w�i�摜�̈ړ��͈͂̍��[�ƉE�[��x���W
	int mNorStXs[2];	// �eNormalStage�̉摜�̍��[��x���W
	float mCloudXs[2];	// �e�_�̉摜�̍��[��x���W
	int mBsStX;	// BossStage�̉摜�̍��[��x���W
	const int BRIDGE_LX = 690;	// BossStage�̔w�i�摜���̋��̍��[��x���W

	bool mIsChangingSt;	// BossStage�֕ύX���ł�������true
	bool mIsMovingNorSts[2];	// BossStage�ւ̕ύX���̂Ƃ��C�eNormalStage�𓮂����Ă���Ƃ�true
	bool mIsAtBsSt;	// BossStage�ɂ�����true

	int mStrFontHandle;	// BossStage�ւ̈ڍs����"!BossStage!"�Ƃ����\��������ۂɎg�p����t�H���g
};