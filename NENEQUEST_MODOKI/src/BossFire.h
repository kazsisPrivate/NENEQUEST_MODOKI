#pragma once

#include "BasicFunc.h"
#include <vector>

class BossFire : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override; 
	void Update() override;
	void Draw() override;
	void StartFire(const int bossX, const int bossY, const int fireType, const int attackType);	// �΂̋ʍU�����n�߂�ۂ̕ϐ��ݒ�
																								// fireType(1: �Ԃ��΂̋ʁi���x���ʁj�C2: ���΂̋ʁi���x�����j)
																								// attackType(1: �΂̋ʓf���o���U���C2: �u���X�U��)
	int GetFireNum(const int attackType) const;	// �΂̋ʂ̐���Ԃ��CEnemy���Ɏg�p����΂̋ʂ�c��������̂Ɏg�p����
	bool GetFiresExist() const;	// �΂̋ʂ��c���Ă��邩�ǂ����C1�ł��c���Ă����true��Ԃ�
	void GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys);	// �e�΂̋ʂ�xy���W��Ԃ��CEnemy���Ŕc��������̂Ɏg�p����
	void GetFiresHitRangeWHs(std::vector<int>& hitRangeWs, std::vector<int>& hitRangeHs);	// �e�΂̋ʂ̓����蔻���Ԃ��CEnemy���Ŕc��������̂Ɏg�p����
	

private:
	void FireBall();	// �΂̋ʓf���o���U��
	void FireBreath();	// �u���X�U��
	float CalcBreathY(const float x);	// x���W����u���X�U����y���W�����߂�

	int* mFireHandle;
	const int FIRE_BALL_NUM = 3;	// �΂̋ʓf���o���U���Ŏg�p����΂̋ʂ̐�
	const int FIRE_BREATH_NUM = 5;	// �u���X�U���Ŏg�p����΂̋ʂ̐�
	int mBallHandleIds[3]; // �΂̋ʓf���o���U���Ŏg�p����C���ꂼ��̉΂̋ʂ��΂߂������Ă���摜�����������Ă���摜���g��������
	float mXs[5], mYs[5];	// ���ꂼ��̉΂̋ʂ�xy���W
	float mDXs[5], mDYs[5]; // x, y��1�t���[��������̑����i�����j��
	float mDDX, mDDY;	// x, y��1�t���[��������̉����x�C�u���X�U���̉΂̋ʂ̈ړ����x�����X�ɏグ�Ă����̂Ɏg�p����
	int mBossMouthX, mBossMouthY;	// EnemyBoss�̌��̈ʒu�C�΂̋ʂ̓f���o���n�߂̍��W�Ƃ��Ďg�p����
	int mBallHitRangeW, mBallHitRangeH;	// �΂̋ʓf���o���U���Ŏg�p����΂̋ʂ̓����蔻��͈̔�
	int mOrigHitRangeW, mOrigHitRangeH;	// �u���X�U���Ŏg�p����΂̋ʂ̌��摜�̌��̓����蔻��͈̔́i�g�嗦�ɂ���ĕω�������O�̓����蔻��͈̔́j
	float mBreathHitRangeWs[5];	// �u���X�U���Ŏg�p����΂̋ʂ̓����蔻��͈̔́i���j�C���ꂼ��̉΂̋ʂ̓����蔻��̑傫���͈قȂ�C�ω�����
	float mBreathHitRangeHs[5];	// �u���X�U���Ŏg�p����΂̋ʂ̓����蔻��͈̔́i�����j�C���ꂼ��̉΂̋ʂ̓����蔻��̑傫���͈قȂ�C�ω����� 
	int mImgW, mImgH;	// �΂̋ʂ̉摜�̑傫��
	float mFireExpRates[5];	// �΂̋ʂ̉摜�̕\���ɗp����g�嗦�C�u���X�U���̎��Ɏg�p����
	int mAttackType;	// �΂̋ʂ̓����̃p�^�[��(1: �΂̋ʓf���o���U���C2: �u���X�U��)
	bool mFiresExist;	// �΂̋ʂ��c���Ă��邩�ǂ����C1�ł��c���Ă����true
	int mFrameCnt;	// �t���[�����̃J�E���g�C�΂̋ʂ̌ʐ���̂��߂Ɏg�p����
	int mFireBallFrameNums[3];	// �΂̋ʓf���o���U���ŉ΂̋ʂ����ɓf���o���Ă������o�Ŏg�p�C���ꂼ��̉΂̋ʂ�f���o���t���[����
	//const int FIRE_BALLS_FRAME_NUMS[3] = { 60, 180, 300 };	// �΂̋ʑ|���o���U���ŉ΂̋ʂ����ɓf���o���Ă������o�Ŏg�p�C���ꂼ��̉΂̋ʂ�f���o���t���[����
	const int FIRE_DELETE_LX = -250;	// �΂̋ʓf���o���U���ɂ����āC���̍��W�܂ł��ׂẲ΂̋ʂ��ړ������Ƃ��C�����I�ɏ����悤�ɂ���(����)
	int mFireBallYs[3];	// �΂̋ʓf���o���U���ɂ����Ă��ꂼ��̉΂̋ʂ̉��ړ����n�߂�y���W�i�f���o���U���ł͎΂߉��ɓf���o���Ă��牡�ړ����n�߂�j
	const int PREPARING_BRE_FRAME_NUM = 60;	// �u���X�U�������n�߂�܂őҋ@���Ă���t���[�����C���̃t���[�����𒴂�����u���X�U�������n�߂�
	const int BREATHING_FRAME_NUM = 360;	// �u���X�U�������Ă���t���[�����C���̃t���[�����𒴂�����u���X�U���Ŏg�p���Ă���΂̋ʂ������n�߂� 
	const int BREATHING_NEW_FIRE_FRAME_NUM = 10;	// �u���X�U���̍ۂɑO�Ɍ�����΂̋ʂ��o�����ォ��C�V����������΂̋ʂ��o���܂ł̃t���[����
	int mNextBreathId;	// �u���X�U���Ŏ��ɓf���o���΂̋ʂ�id�ԍ��i0 �` (FIRE_BREATH_NUM - 1)�j
	bool mBreIsExistings[5];	// �u���X�U���ŉ΂̋ʂ��g�p���i�f���o���Ă���Ƃ��j��������true
};