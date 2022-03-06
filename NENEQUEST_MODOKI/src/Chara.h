#pragma once
/*
* Player��Enemy�̊��N���X
*/
#include "BasicFunc.h"


class Chara : public BasicFunc { 
protected:
	virtual void Walk() {};	// �ړ�
	virtual void UpdateHp() {};	// �̗͂̍X�V

	int mImgW, mImgH;	// �L�����N�^�[�̉摜�̉�(width)�A�c�̃T�C�Y(height)
	int mHandleId;	// �g�p���Ă���摜��id�ԍ�

	int mHp;	// chara��HP, Player��HP��6
	int mAttack;	/// chara�̍U����
	float mSpeed; // chara�̈ړ����x
	int mX, mY;	// chara�̒��S��x,y���W
	int mHitRangeW, mHitRangeH;	// chara�̓����蔻��̒��S���W����͈̔�(width, height)

	bool mIsAttacking;	// �U�����Ȃ��true
	bool mIsGod;	// �_���[�W���󂯂Ă���C���G�ɂȂ��Ă��邩�̔���Ŏg��
	int mGodFrameCnt;	// �_���[�W���󂯂����̓_�ŕ`��△�G���Ԃ̃J�E���g���Ɏg��
};