#include "MageFire.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <math.h>


#define PI 3.14159265358979323846


void MageFire::Initialize() {
	mFiresExist = false;
}


void MageFire::Finalize() {
	mFiresExist = false;
}


void MageFire::StartFire(const int eneX, const int eneY, const int fireType, const int attackType) {
	// �΂̉摜�̓ǂݍ���
	if (fireType == 1) {	// �Ԃ��΂̋�
		mFireHandle = EffectGraphics::GetGraHandle(5);
	}
	else {	// ���΂̋�
		mFireHandle = EffectGraphics::GetGraHandle(6);
	}

	// �U���̎�ނ�����
	mAttackType = attackType;

	// �U���̕������Z�b�g����
	if (eneX > 600) {	// �������̍U��
		mDirec = -1;
	}
	else {	// �E�����̍U��
		mDirec = 1;
	}

	// �΂̋ʂ̑��x�̏������Ɏg�p����C�΂̋ʂɂ���đ��x���ς�邽�߁C���̕ϐ����g�p����
	float speedRate;
	if (fireType == 1) {	// �Ԃ��΂̋ʂ̂Ƃ�
		speedRate = 1.0f;
	}
	else {	// ���΂̋ʂ̂Ƃ�
		speedRate = 1.4f;	// �Ԃ��΂̋ʂ��1.4�{��
	}

	// �U���ɍ��킹�����������s��
	if (mAttackType == 1) {	// �W�O�U�O�U��
		// �e�΂̋ʂ�xy���W
		for (int i = 0; i < FIRE_NUM; i++) {
			mXs[i] = eneX + mDirec * 62;
			mYs[i] = eneY - 62;
		}

		// 1�t���[���������xy���W�̑����ʂ̐ݒ�
		mDX = mDirec * speedRate * 6;
		if (eneY < 450) {	// enemy���㑤�ɂ�����
			for (int i = 0; i < FIRE_NUM; i++) {
				mDYs[i] = speedRate * (-15);
			}
		}
		else {	// enemy�������ɂ�����
			for (int i = 0; i < FIRE_NUM; i++) {
				mDYs[i] = speedRate * 15;
			}
		}
	}
	else {	// ��]�U��
		// ��]�U���̉~�̒��S���W
		mCX = eneX;
		mCY = eneY;

		// ��]�U���̉~�̒��S�_����e�΂̋ʂ̋����i�~�̔��a�j
		mRadius = 60.0f;

		// �e�΂̋ʂ̒��S�ʒu����̉�]�p
		for (int i = 0; i < FIRE_NUM; i++) {
			mThetas[i] = PI * 2 * i / 3;
		}

		// �e�΂̋ʂ�xy���W
		UpdateRotatedFiresXYs();

		// 1�t���[���������x���W���]�p�̑����ʂ̐ݒ�
		mDX = mDirec * speedRate * 4;
		mDTh = mDirec * speedRate * (float)PI * (float)2/180;
		mDR = speedRate * 0.5f;
	}

	mFrameCnt = 0;
	mFiresExist = true;
}


void MageFire::Update() {
	// �e�΂̋ʂ���ʊO�ɍs���������m�F����
	bool isAtOutside = true;
	for (int i = 0; i < FIRE_NUM; i++) {
		if (mXs[i] > FIRE_DELETE_LX && mXs[i] < FIRE_DELETE_RX) {	// 1�̉΂̋ʂł���ʓ��ɂ����
			isAtOutside = false;
		}
	}

	if (isAtOutside) {	// 1�̉΂̋ʂł���ʊO�ɏo�Ă����� 
		Finalize();
	}
	else {
		if (mFrameCnt >= FIRE_FIRST_STOP_FRAME_NUM) {	// �΂̋ʂ��v���C���[�ɔF��������܂ł̌Œ莞�Ԍ�Ɉړ����n�߂�
			Move();
		}

		mFrameCnt++;
	}
}

void MageFire::Draw() {
	// �e�΂̋ʂ�`��
	for (int i = 0; i < 3; i++) {
		if (mFrameCnt >= FIRES_DISAPPEAR_FRAME_NUMS[i]) {
			DrawGraph((int)mXs[i] - IMG_W / 2, (int)mYs[i] - IMG_H / 2, *mFireHandle, TRUE);
		}
	}
}

void MageFire::Move() {
	if (mAttackType == 1) {	// �W�O�U�O�U��
		// �e�΂̋ʂ�xy���W���X�V
		for (int i = 0; i < FIRE_NUM; i++) {
			if (mFrameCnt >= FIRES_STOP_FRAME_NUMS[i]) {
				if (mYs[i] > SCREEN_BOTTOM_Y || mYs[i] < SCREEN_TOP_Y) {	// �΂̋ʂ�y���W���㉺�̂ǂ��炩�̒[�ɍs������
					// y���̐i�s�����𔽓]����
					mDYs[i] *= -1;
				}

				// xy���W�̍X�V
				mXs[i] += mDX;
				mYs[i] += mDYs[i];
			}
		}
	}
	else {	// ��]�U��
		// ���ꂼ��̉΂̋ʂ̉�]�p���X�V
		for (int i = 0; i < FIRE_NUM; i++) {
			mThetas[i] += mDTh;
		}

		// ���ꂼ��̉΂̋ʂ�xy���W���X�V
		UpdateRotatedFiresXYs();

		// �΂̋ʂ̉�]�̉~�̒��S�_��x���W�Ɖ~�̔��a���X�V
		if (mFrameCnt >= FIRES_STOP_FRAME_NUM) {
			mCX += mDX;
			mRadius += mDR;
		}
	}
}


void MageFire::UpdateRotatedFiresXYs() {
	// ��]�p���l�����āA�e�΂̋ʂ�xy���W���X�V
	for (int i = 0; i < FIRE_NUM; i++) {
		mXs[i] = -(-mRadius) * sin(-mThetas[i]) + mCX;
		mYs[i] = ((-mRadius) * cos(-mThetas[i]) + mCY);
	}
}


int MageFire::GetFireNum() const {
	return FIRE_NUM;
}


int MageFire::GetFireStopFrameNum(const int attackType) const {
	if (attackType == 1) {	// �W�O�U�O�U��
		return FIRES_STOP_FRAME_NUMS[0];
	}
	else {	// ��]�U��
		return FIRES_STOP_FRAME_NUM;
	}
}


std::pair<int, int> MageFire::GetFiresHitRange() {
	// �΂̋ʂ̓����蔻��͈̔�
	int hitRangeW = IMG_W / 2 - 30;
	int hitRangeH = IMG_H / 2 - 30;

	return { hitRangeW, hitRangeH };
}


bool MageFire::GetFiresExist() const {
	return mFiresExist;
}


void MageFire::MakeFiresExistFalse() {
	mFiresExist = false;
}


void MageFire::GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys) {
	// �e�΂̋ʂ�xy���W������
	for (int i = 0; i < FIRE_NUM; i++) {
		xs.at(i) = mXs[i];
		ys.at(i) = mYs[i];
	}
}

