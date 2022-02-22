#pragma once

// ���g��
#include "Enemy.h"
#include "Slash.h"
#include <vector>


class Enemy7 : public Enemy {
public:
	Enemy7(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemy�̃f�[�^��n�����߂Ɏg�p����

protected:
	//virtual void Walk() override;
	//virtual void Attack();	// �΂̋ʂ̍U��
	virtual void FadeIn();	// �o�����y�сC�΂̋ʍU���̑O�̃t�F�[�h�C��
	virtual void FadeOut();	// �΂̋ʍU���̌�̃t�F�[�h�A�E�g
	virtual void Hide();	// �t�F�[�h�A�E�g�ƃt�F�[�h�C���̊Ԃ̎p���B���Ă��鎞�̏���

	Slash* mSlash;
	int mAX, mAY;	// �a����xy���W
	int mHitRangeAW, mHitRangeAH;	// �a���̓����蔻��͈�
	int mAlphaValue;	// Enemy7�̓����x�CFadeIn, FadeOut�œ����邽�߂Ɏg�p����
	int DELTA_ALPHA = 9;	// �t�F�[�h�C���ƃt�F�[�h�A�E�g�̍ۂ̃��l��1�t���[��������̑���/������
	int mRoutineDoneCnt;	// ������I�����񐔁C����̉񐔏I��点����Ɏ����I�ɏ����悤�ɂ��邽�߂Ɏg�p����
							// ����Ƃ́C�i�t�F�[�h�C�� �� �΂̋ʍU�� �� �t�F�[�h�A�E�g�j�̃Z�b�g��1��ƃJ�E���g����
							// �������C�ŏ��̈��ڂ́C�i�t�F�[�h�C�� �� ��u�Œ藧�� �� �t�F�[�h�A�E�g�j�̃Z�b�g�Ƃ���
	int mDeleteRoDoneNum;	// ���̉񐔂̓����������́C�����I�ɏ����悤�ɂ���
	bool mHasFinishedRos;	// �����mDeleteRoDoneNum�̐��܂ł���炵���Ƃ���true�ƂȂ�
	bool mIsFadingIn;	// �t�F�[�h�C�����Ă���Ƃ�true
	bool mIsFadingOut;	// �t�F�[�h�A�E�g���Ă���Ƃ�true
	bool mIsHiding;	// ����̊ԂɎp���B���Ă���i�����Ă���j�Ƃ�true
	int mHidingFrameCnt;	// �t�F�[�h�C���ƃt�F�[�h�A�E�g�̊ԂɎp���B���Ă���i�����Ă���j�t���[�����̃J�E���g
	const int HIDING_FRAME_NUM_MIN = 60;	// �ň��ł��̃t���[�������C�t�F�[�h�C���ƃt�F�[�h�A�E�g�̊ԂɎp���B���Ă���i�����Ă���j
	bool mEne7IsDead;	// mHp��0�C�������Ă����Ƃ��i���񂾂��Ƃ�F�������邽�߂̌Œ莞�Ԍ�Ȃǁj��true�ɂȂ�
	int mAttackFrameCnt;	// �U�������Ă���ہi�΂̋ʂ��o���n�߂Ă���j�̃t���[�������J�E���g����C�t�F�[�h�A�E�g�̊J�n�ȂǂŎg�p����
	const int STOP_FRAME_NUM = 150;	// �t�F�[�h�C���œ����Ă��Ă���Œ藧�����Ă��鎞�ԁi1��ڂ̓���̎��̂ݎg�p�j
	const int ATTACK_STATE_FRAME_NUM = 60;	// �U�������Ă���i�΂̋ʂ��o���n�߂Ă���j�C�t�F�[�h�A�E�g���n�߂�܂ł̃t���[�����i2��ڈȍ~�̓���̎��g�p�j
	int mAttackDirec;	// �a���U���̕������i-1: �������C1: �E�����j
	int mAttackType;	// �a���U���̎�ށi1: �Œ�ʒu�̎a���U���C2: ��΂��a���U���j
};

