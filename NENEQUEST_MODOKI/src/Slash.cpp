#include "Slash.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <math.h>


#define PI 3.14159265358979323846


void Slash::Initialize() {
	mSlashExist = false;
}


void Slash::Finalize() {
	mSlashExist = false;
}


void Slash::StartSlash(const int eneX, const int eneY, const int direc, const int attackType) {
	// �a���摜�̓ǂݍ���
	mSlashHandle = EffectGraphics::GetGraHandle(7);

	// �U���̎�ނ�����
	mAttackType = attackType;

	// �U���̕������Z�b�g����
	mDirec = direc;	// �E�����Ȃ�1, �������Ȃ�-1

	// �U���ɍ��킹�����������s��
	if (mAttackType == 1) {	// �Œ�ʒu�̎a���U��
		// �a����xy���W
		mX = eneX + mDirec * 100;
		mY = eneY;

		// �a���̓����蔻��
		mHitRangeW = 63;
		mHitRangeH = 50;

		// �a���̉摜id
		mHandleId = 1 + mDirec * 0.5;	// �������Ȃ�0������C�E�����Ȃ�1������
	}
	else {	// ��]�U��
		// �a����xy���W
		mX = eneX + mDirec * 100;
		mY = eneY;

		// �a���̓����蔻��
		mHitRangeW = 63;
		mHitRangeH = 50;

		// �a����x���W�̑�����
		mDX = mDirec * 40;

		// �a���̉摜id
		mHandleId = 3 + mDirec * 0.5;	// �������Ȃ�0������C�E�����Ȃ�1������
	}

	mFrameCnt = 0;
	mSlashExist = true;
}


void Slash::Update() {
	if (mAttackType == 1) {	// �Œ�ʒu�̎a���U���̂Ƃ�
		if (mFrameCnt == SLASH_DELETE_FRAME_NUM) {	// ����̃t���[�����ɂȂ�����
			Finalize();
		}
		else {
			mFrameCnt++;
		}
	}
	else {	// ��΂��a���U���̂Ƃ�
		if (mX < SLASH_DELETE_LX || mX > SLASH_DELETE_RX) {	// �a������ʊO�ɏo�Ă����� 
			Finalize();
		}
		else {
			Move();

			mFrameCnt++;
		}
	}
}


void Slash::Draw() {
	DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mSlashHandle[mHandleId], TRUE);
}


void Slash::Move() {
	mX += mDX;
}


std::pair<int, int> Slash::GetSlashHitRange() {
	return { mHitRangeW, mHitRangeH };
}


bool Slash::GetSlashExist() const {
	return mSlashExist;
}


std::pair<int, int> Slash::GetSlashXY() {
	return { mX, mY };
}
