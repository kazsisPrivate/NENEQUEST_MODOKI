#pragma once
/*
* ���@�g���̓G�iEnemy4�`6�j�̊��N���X
*/
#include "Enemy.h"
#include "MageFire.h"
#include <vector>


class EnemyMage : public Enemy {
public:
	EnemyMage(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemy�̃f�[�^��n�����߂Ɏg�p����

protected:
	virtual void Walk() override;
	virtual void FadeIn();	// �o�����y�сC�΂̋ʍU���̑O�̃t�F�[�h�C��
	virtual void FadeOut();	// �΂̋ʍU���̌�̃t�F�[�h�A�E�g
	virtual void Hide();	// �t�F�[�h�A�E�g�ƃt�F�[�h�C���̊Ԃ̎p���B���Ă��鎞�̏���

	MageFire* mMageFire;
	int mFireType;	// �g�p����΂̋ʂ̎�ށi1: �Ԃ��΂̋ʁi���x���ʁj�C2: ���΂̋ʁi���x�����j�j
	int mFireNum;	// �g�p����΂̋ʂ̐��iMageFire�N���X����󂯎��j
	int mFireStopFrameNum;	// �΂̋ʍU���������n�߂�܂ł̎��ԁi�U���������ԁC�΂̋ʂ���ʂɌ����Ă͂���j

	std::vector<int> mAXs;	// �e�΂̋ʂ�x���W
	std::vector<int> mAYs;	// �e�΂̋ʂ�y���W
	int mHitRangeAW, mHitRangeAH;	// �΂̋ʂ̓����蔻��͈�
	int mDirecY;	// EnemyMage��Walk�̍ۂ�y���W�̈ړ��̌�������Ɏg�p����
	const int ENE_MAGE_Y_MAX = 610;	// EnemyMage��Walk�̍ۂ�y���W�̈ړ��͈́i�ő�j
	const int ENE_MAGE_Y_MIN = 290;	// EnemyMage��Walk�̍ۂ�y���W�̈ړ��͈́i�ŏ��j
	int mAlphaValue;	// EnemyMage�̓����x�CFadeIn, FadeOut�œ����邽�߂Ɏg�p����
	int DELTA_ALPHA = 7;	// �t�F�[�h�C���ƃt�F�[�h�A�E�g�̍ۂ̃��l��1�t���[��������̑���/������

	int mRoutineDoneCnt;	// ������I�����񐔁C����̉񐔏I��点����Ɏ����I�ɏ����悤�ɂ��邽�߂Ɏg�p����
							// ����Ƃ́C�i�t�F�[�h�C�� �� �΂̋ʍU�� �� �t�F�[�h�A�E�g�j�̃Z�b�g��1��ƃJ�E���g����
							// �������C�ŏ��̈��ڂ́C�i�t�F�[�h�C�� �� ���s �� �t�F�[�h�A�E�g�j�̃Z�b�g�Ƃ���
	int mDeleteRoDoneNum;	// ���̉񐔂̓����������́C�����I�ɏ����悤�ɂ���

	bool mIsFadingIn;	// �t�F�[�h�C�����Ă���Ƃ�true
	bool mIsFadingOut;	// �t�F�[�h�A�E�g���Ă���Ƃ�true
	bool mIsHiding;	// ����̊ԂɎp���B���Ă���i�����Ă���j�Ƃ�true
	int mHidingFrameCnt;	// �t�F�[�h�C���ƃt�F�[�h�A�E�g�̊ԂɎp���B���Ă���i�����Ă���j�t���[�����̃J�E���g
	const int HIDING_FRAME_NUM_MIN = 60;	// �ň��ł��̃t���[�������C�t�F�[�h�C���ƃt�F�[�h�A�E�g�̊ԂɎp���B���Ă���i�����Ă���j
	bool mMageIsDead;	// mHp��0�C����EnemyMage���̂������Ă����Ƃ��i���񂾂��Ƃ�F�������邽�߂̌Œ莞�Ԍ�Ȃǁj��true�ɂȂ�
	bool mHasFinishedRos;	// �����mDeleteRoDoneNum�̐��܂ł���炵���Ƃ���true�ƂȂ�
	int mAttackFrameCnt;	// �U�������Ă���ہi�΂̋ʂ��o���n�߂Ă���j�̃t���[�������J�E���g����C�t�F�[�h�A�E�g�̊J�n�ȂǂŎg�p����
	const int WALK_FRAME_NUM = 120;	// �t�F�[�h�C���œ����Ă��Ă���ړ����Ă��鎞�ԁi1��ڂ̓���̎��̂ݎg�p�j
	const int ATTACK_STATE_FRAME_NUM = 300;	// �U�������Ă���i�΂̋ʂ��o���n�߂Ă���j�C�t�F�[�h�A�E�g���n�߂�܂ł̃t���[�����i2��ڈȍ~�̓���̎��g�p�j
};

