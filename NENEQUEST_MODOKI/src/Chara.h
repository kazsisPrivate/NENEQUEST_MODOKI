#pragma once

#include "BasicFunc.h"

class Chara : public BasicFunc { 
public:
	virtual void Walk() {};	// �ړ�
	virtual void Jump() {};	// �W�����v
	virtual void Attack() {};	// �U��
	virtual void UpdateSAP() {};	// �ړ����x�ƍU���͂̍X�V
	virtual void UpdateHit() {};	// �����蔻��̍X�V

protected:
	int mHp;	// chara��HP, Player��HP��6
	int mAttack;	/// chara�̍U����
	float mSpeed; // chara�̈ړ����x
	int mX, mY;	// chara�̒��S��x,y���W
	int mAX, mAY;	// chara�̍U���̒��S��xy���W
	int mImgW, mImgH;	// charaHandle[]�̉摜�̉�(width)�A�c�̃T�C�Y(height)
	int mHitRangeW, mHitRangeH;	// chara�̓����蔻��̒��S���W����͈̔�(width, height)
	int mHitRangeAW, mHitRangeAH; //chara�̍U���̓����蔻��̒��S���W����͈̔�(width, height)
	long long mFrameCnt; //���Ԃ̌o�߂��v��
	//int ix, iy;
	int mHandleId;	// charaHandle[]��[]�̔ԍ�
	int mAFrameCnt;	// �U���������ƁC���ɍU���ł���悤�ɂȂ�܂ł̃C���^�[�o���Ƃ��Ďg�p����
	int mYStart, mYPrev;	// �W�����v�����Ŏg�p����B�ȑO��y���W��\��
	int mGodFrameCnt;	// �_���[�W���󂯂����̓_�ŕ`��△�G���Ԃ̃J�E���g���Ɏg��
	bool mIsJumping;	// �W�����v���Ȃ��true
	bool mIsAttacking;	// �U�����Ȃ��true
	bool mIsGod;	// �_���[�W���󂯂Ă���C���G�ɂȂ��Ă��邩�̔���Ŏg��
	bool mIsDead;	// mHp��0�C�������Ă����Ƃ��i���񂾂��Ƃ�F�������邽�߂̌Œ莞�Ԍ�Ȃǁj��true�ɂȂ�
};