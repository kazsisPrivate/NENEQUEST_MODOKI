#pragma once

#include "BasicFunc.h"
#include <tuple>


class Arrow : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void StartArrow(const int x, const int y, const int moveType);
	bool GetArrowExists() const;
	bool GetIsMoving() const;	// �|������Ă���Ƃ����ǂ�����n���C�U���̓����蔻��Ŏg�p����
	std::tuple<int, int> GetArrowXY();	// �U���̓����蔻����m�F�����邽�߂ɋ|��̍��W��n��
	void SetIsHit(const bool isHit);	// Arrow�������ɂ����������ǂ���������

private:
	void Move();	//	�|��̈ړ�
	void UpdateHit();	//	�|��̓����蔻��ƓG�ɋ|������������ǂ����̔���
	int* mArrowHandle;	// �|��̉摜
	int* mHitEffectHandle;	// �|����������u�Ԃɏo�铖�������G�t�F�N�g�̉摜
	int mX, mY;	// �|���x,y���W�i����[�j
	int mXCenter, mYCenter; // �|��̉�]�̒��S��x,y���W
	int mDX;	// x���W��1�t���[��������̑����ʁC���������キ�����ŕω�����
	const int HIT_RANGE_W = 11;	// �|��̓����蔻��͈̔�(Width)
	const int HIT_RANGE_H = 10;	// �|��̓����蔻��͈̔�(Height)
	int mYPrev, mYStart;	// �|��̎��R�����̏����Ŏg�p����
	int mDYFirst;	// y���W��1�t���[��������̑����ʂ̍ŏ��̒l�C���������キ�����ŕω�����
	const int IMG_W = 70;	// Arrow�̉摜�̑傫���iWidth�j
	const int IMG_H = 64;	// Arrow�̉摜�̑傫���iHeight�j
	int mAExistingFrameCnt;	// �|�������Ă���̃t���[�����C�|��̓����̐���̂��߂̎��Ԍv���Ɏg��
	const int A_EXISTING_FRAME_NUM = 80;	// �|�������Ă���|��������܂ł̃t���[����
	int mHitFrameCnt;	// �|��G��Item�ɓ������Ă���o�߂����t���[����
	const int HIT_FRAME_NUM = 20;	// �|��G��Item�ɂ������Ă���|��������܂ł̃t���[����
	int mType;	// �|��̓����̃^�C�v�i1�F�E�����̎ア�|��C2�F�������̎ア�|��C3�F�E�����̋����|��C4�F�������̋����|��j
	float mTheta;	// mXCenter, mYCenter�𒆐S�Ƃ����|��̉�]�p
	float mDTh;	// mTheta��1�t���[��������̑�����
	bool mArrowExists;	// �|����݂��Ă����true�CPlayer_4�̂ق���Update��Draw�������邩�̔��f�̂��߂ɂ���
	bool mIsMoving; //	������Ă���ԁi���ɂ��������Ă��Ȃ��ԁj��ture
	bool mIsHit;	// �G��Item�ɖ�����������ǂ����̔���Ɏg�p����
};