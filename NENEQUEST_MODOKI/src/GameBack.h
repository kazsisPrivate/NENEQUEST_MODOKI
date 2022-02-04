#pragma once

#include "BasicFunc.h"

class GameBack : BasicFunc {
public:
	GameBack();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void UpdateNormal();	// boss�ɓ���܂ł̔w�i�̍X�V����
	void UpdateBoss();	//boss�ɓ�������̔w�i�̍X�V����

private:
	const int END_LEFT_X = -1280, END_RIGHT_X = 1280;
	int mMo1Handle, mMo2Handle;	// �R�̉摜
	int mCl1Handle, mCl2Handle;	// �_�̉摜
	int mBoStHandle; // bossStage�̉摜
	int mMountain1X, mMountain2X;	// �R�̉摜�̍��[��x���W
	float mClouds1X, mClouds2X;	// �_�̉摜�̍��[��x���W
	int mBoStX;	// bossStage�̉摜�̍��[��x���W
	const int UPDATE_FRAME_NUM = 3;	// �X�V���s���^�C�~���O�iUPDATE_CNT_NUM��2�Ȃ��2�t���[�����ɍX�V����j
	int mUpdFraCnt;	// �X�V�t���[�����̃J�E���g�CUPDATE_FRAME_NUM�ɂȂ�����0�ɖ߂�
	int mBackChCnt; //�i�F������ւ�����񐔁A�܂�mountainHandle��-1280�ɓ��B���邲�Ƃ�1�����Ă����A�{�X�o�g���ɓ������Ƃ��̌i�F�̕ύX�Aplayer�Ƀ{�X�o�g���ɓ������Ƃ����̂�m�点��̂Ɏg��
	bool mIsBossStage; //bossStage�ɓ������Ƃ�true�ɂȂ�
};