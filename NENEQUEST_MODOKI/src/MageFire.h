#pragma once
/*
* ���@�g���̓G�iEnemyMage�j���g�p����΂̋ʂ̐�����s���N���X
*/
#include "BasicFunc.h"
#include <utility>
#include <vector>


class MageFire : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartFire(const int eneX, const int eneY, const int fireType, const int attackType);	// �΂̋ʍU�����n�߂�ۂ̕ϐ��ݒ�
																								// fireType(1: �Ԃ��΂̋ʁi���x���ʁj�C2: ���΂̋ʁi���x�����j)
																								// attackType(1: �W�O�U�O�U���C2: ��]�U��)
	int GetFireNum() const;	// �΂̋ʂ̐���Ԃ��CEnemy���Ɏg�p����΂̋ʂ�c��������̂Ɏg�p����
	int GetFireStopFrameNum(const int attackType) const;	// �΂̋ʂ������o���O�̎��Ԃ�Ԃ�
	std::pair<int, int> GetFiresHitRange();	// �΂̋ʂ̓����蔻��͈̔͂�Ԃ��CEnemy���Ŕc��������̂Ɏg�p����
	bool GetFiresExist() const;	// �΂̋ʂ��c���Ă��邩�ǂ����C3�̉΂̋ʂ̂���1�ł���ʓ��Ɏc���Ă����true��Ԃ�
	void MakeFiresExistFalse();	// �΂̋ʂ��������߂Ɏg�p����, EnemyMage���U������O�ɂ��ꂽ��Ăт���
	void GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys);	// �e�΂̋ʂ�xy���W��Ԃ��CEnemy���Ŕc��������̂Ɏg�p����

private:
	void Move();	// �΂̋ʂ̈ړ�
	void UpdateRotatedFiresXYs(); // �΂̋ʂ̉�]�p���l������xy���W�ɍX�V�C��]�U���Ŏg�p�C�Ăт������ۂ�mXs, mYs, mRadius, mThetas�𗘗p���čX�V����

	int* mFireHandle;
	const int FIRE_NUM = 3;	// �΂̋ʂ̐�
	float mXs[3];	// ���ꂼ��̉΂̋ʂ�x���W
	float mYs[3];	// ���ꂼ��̉΂̋ʂ�y���W
	float mCX, mCY; // �΂̋ʂ̉�]�U���Ɏg�p����e�΂̋ʂ̉�]�̒��S�_���W(��]�U���Ŏg�p)
	float mRadius;	// �΂̋ʂ̉�]�U���̍ۂ̊e�΂̋ʂ̉�]�̉~�̔��a(��]�U���Ŏg�p)
	float mThetas[3];	// �e�΂̋ʂ̉�]�p(��]�U���Ŏg�p)
	const int IMG_W = 120, IMG_H = 108;	// �΂̋ʂ̉摜�̑傫��
	//int count; //�΂̋ʂ̓����̐���̂��߂̎��Ԍv���Ɏg��
	int mDirec;	// �U���̕�����\���C�������Ȃ�-1�C�E�����Ȃ�1�������Ă���
	int mAttackType;	// �΂̋ʂ̓����̃p�^�[��(1: �W�O�U�O�U���C2: ��]�U��)
	float mDX;	// x���W��1�t���[��������̑�����, �W�O�U�O�U���ł͊e�΂̋ʂ�x���W�C��]�U���ł͉�]�̉~�̒��S�_��x���W
	float mDYs[3];	// ���ꂼ��̉΂̋ʂ�y���W��1�t���[��������̑�����
	float mDTh;	// ��]�p��1�t���[��������̑�����
	float mDR;	// ��]�U���̍ۂɎg�p����~�̔��a��1�t���[��������̑�����
	const int FIRES_DISAPPEAR_FRAME_NUMS[3] = { 0, 15, 30 };	// ��]�U�����n�߂�ۂ̉΂̋ʂ����ɕ\�����Ă������o�Ŏg�p�C���ꂼ��̉΂̋ʂ������t���[����
	const int FIRES_STOP_FRAME_NUMS[3] = { 30, 35, 40 };	// �W�O�U�O�U�����n�߂�ۂ̂��ꂼ��̉΂̋ʂ̓����o��(�����o���܂łɎ~�܂��Ă���)�t���[�����C1���������Ă���
	const int FIRES_STOP_FRAME_NUM = 90;	// ��]�U�����n�߂�ۂ̉΂̋ʂ̓����o��(�����o���܂łɎ~�܂��Ă���)�t���[����
	const int FIRE_DELETE_LX = -250;	// ���̍��W�܂ł��ׂẲ΂̋ʂ��ړ������Ƃ��C�����I�ɏ����悤�ɂ���(����)
	const int FIRE_DELETE_RX = 1450;	// ���̍��W�܂ł��ׂẲ΂̋ʂ��ړ������Ƃ��C�����I�ɏ����悤�ɂ���(�E��)
	const int SCREEN_TOP_Y = 50;	// ��ʂ̏�̍��W�C�W�O�U�O�U���̋ʂ̒��˕Ԃ�Ŏg�p����
	const int SCREEN_BOTTOM_Y = 650;	// ��ʂ̉��̍��W�C�W�O�U�O�U���̋ʂ̒��˕Ԃ�Ŏg�p����
	const int FIRE_FIRST_STOP_FRAME_NUM = 30;	// �ŏ��ɉ΂̋ʂ�\�������ē����o���܂ł̎��ԁC�΂̋ʍU�������邼�Ƃ������Ƃ�F�������邽�߂ɉ΂̋ʂ𓮂��Ȃ���Ԃŕ\�����鎞��
	bool mFiresExist;	// �΂̋ʂ��c���Ă��邩�ǂ����C3�̉΂̋ʂ̂���1�ł���ʓ��Ɏc���Ă����true
	int mFrameCnt;	// �t���[�����̃J�E���g�C�΂̋ʂ̌ʐ���̂��߂Ɏg�p����
};