#pragma once

#include "BasicFunc.h"
#include <utility>
#include <vector>


class Slash : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartSlash(const int eneX, const int eneY, const int direc, const int attackType);	// �a���U�����n�߂�ۂ̕ϐ��ݒ�
																							// attackType(1: �Œ�ʒu�̎a���U���C2: ��΂��a���U��)
	std::pair<int, int> GetSlashHitRange();	// �΂̋ʂ̓����蔻��͈̔͂�Ԃ��CEnemy���Ŕc��������̂Ɏg�p����
	bool GetSlashExist() const;	// �΂̋ʂ��c���Ă��邩�ǂ����C3�̉΂̋ʂ̂���1�ł���ʓ��Ɏc���Ă����true��Ԃ�
	std::pair<int, int> GetSlashXY();	// �e�΂̋ʂ�xy���W��Ԃ��CEnemy���Ŕc��������̂Ɏg�p����

private:
	void Move();	// �a���̈ړ��i��΂��a���U���݂̂Ŏg�p�j

	int* mSlashHandle;
	int mHandleId;	// �g�p���Ă���a���̉摜��id
	int mX, mY;	// �a����xy���W
	int mHitRangeW, mHitRangeH;	// �a���̓����蔻��
	const int IMG_W = 250, IMG_H = 150;	// �a���̉摜�̑傫��
	int mDirec;	// �U���̕�����\���C�������Ȃ�-1�C�E�����Ȃ�1�������Ă���
	int mAttackType;	// �a���̓����̃p�^�[��(1: �Œ�ʒu�̎a���U���C2: ��΂��a���U��)
	float mDX;	// x���W��1�t���[��������̑������i��΂��a���U���݂̂Ŏg�p�j
	const int SLASH_DELETE_LX = -250;	// ���̍��W�܂ł��ׂẲ΂̋ʂ��ړ������Ƃ��C�����I�ɏ����悤�ɂ���(����)
	const int SLASH_DELETE_RX = 1450;	// ���̍��W�܂ł��ׂẲ΂̋ʂ��ړ������Ƃ��C�����I�ɏ����悤�ɂ���(�E��)
	bool mSlashExist;	// �a�����c���Ă��邩�ǂ����C��ʓ��Ɏc���Ă����true
	int mFrameCnt;	// �t���[�����̃J�E���g�C�Œ�ʒu�̎a���U���̐���̂��߂Ɏg�p����
	const int SLASH_DELETE_FRAME_NUM = 60;	// ���̃t���[�����𒴂�����a���������i�Œ�ʒu�̎a���U���݂̂Ŏg�p�j
};