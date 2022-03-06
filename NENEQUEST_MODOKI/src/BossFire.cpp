#include "BossFire.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <random>
#include <vector>
#include <algorithm>


void BossFire::Initialize() {
	mFiresExist = false;
}


void BossFire::Finalize() {
	mFiresExist = false;
}


void BossFire::StartFire(const int bossX, const int bossY, const int fireType, const int attackType) {
	// �U���̎�ނ�����
	mAttackType = attackType;

	// EnemyBoss�̌��̈ʒu������
	mBossMouthX = bossX - 212;
	mBossMouthY = bossY - 130;
	
	if (mAttackType == 1) {	// �΂̋ʓf���o���U��
		// �΂̉摜�̓ǂݍ���
		if (fireType == 1) {	// �Ԃ��΂̋�
			mFireHandle = EffectGraphics::GetGraHandle(8);
		}
		else {	// ���΂̋�
			mFireHandle = EffectGraphics::GetGraHandle(9);
		}
		// �摜�T�C�Y�̐ݒ�
		mImgW = 208, mImgH = 208;
		// �摜id�̐ݒ�
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mBallHandleIds[i] = 0;
		}

		// �e�΂̋ʂ̈ʒu�̏�����
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			// EnemyBoss�̌��̈ʒu�ɏ�����
			mXs[i] = mBossMouthX;
			mYs[i] = mBossMouthY;
		}

		// �΂̋ʂ̑��x�̏������Ɏg�p����C�΂̋ʂɂ���đ��x���ς�邽�߁C���̕ϐ����g�p����
		float speedRate;
		if (fireType == 1) {	// �Ԃ��΂̋ʂ̂Ƃ�
			speedRate = 1.0f;
		}
		else {	// ���΂̋ʂ̂Ƃ�
			speedRate = 1.5f;	// �Ԃ��΂̋ʂ��1.5�{��
		}

		// �e�΂̋ʂ̑��x��ݒ�
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mDXs[i] = -1.5 * speedRate;
			mDYs[i] = 3 * speedRate;
		}

		// �΂̋ʂ̓����蔻���ݒ�
		mBallHitRangeW = 36, mBallHitRangeH = 36;

		// ���ꂼ��̉΂̋ʂ�f���o���t���[�����̐ݒ�
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mFireBallFrameNums[i] = (60 + 120 * i) / speedRate;
		}

		// �e�΂̋ʂ̉��ړ����n�߂�y���W�̐ݒ�
		std::vector<int> ballYs{ 300, 450, 600 };
		std::random_device rnd;
		std::shuffle(ballYs.begin(), ballYs.end(), rnd);
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			mFireBallYs[i] = ballYs.at(i);
		}
	}
	else {	// �u���X�U��
		// �΂̉摜�̓ǂݍ���
		if (fireType == 1) {	// �Ԃ��΂̋�
			mFireHandle = EffectGraphics::GetGraHandle(10);
		}
		else {	// ���΂̋�
			mFireHandle = EffectGraphics::GetGraHandle(11);
		}
		// �摜�T�C�Y�̐ݒ�
		mImgW = 104, mImgH = 104;

		// �e�΂̋ʂ̈ʒu�̏�����
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			// EnemyBoss�̌��̈ʒu�ɏ�����
			mXs[i] = mBossMouthX;
			mYs[i] = mBossMouthY;
		}

		// �e�΂̋ʂ̉����x�̐ݒ�
		int tmpNum = 0;
		int itrNum = BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM;
		for (int i = 0; i < itrNum; i++) {
			tmpNum += i + 1;
		}
		mDDX = 300 / (BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM);// (float)tmpNum;	// 250��EnemyBoss�̌�����ł��΂̋ʂ�������܂ł�x���W�̈ړ���
		mDDY = -230 / (float)tmpNum;	// 230��EnemyBoss�̌�����ł��΂̋ʂ�������܂ł�y���W�̈ړ���

		// �e�΂̋ʂ̈ړ����x�̏�����
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mDXs[i] = -mDDX;// *BREATHING_NEW_FIRE_FRAME_NUM* FIRE_BREATH_NUM;
			mDYs[i] = -mDDY * BREATHING_NEW_FIRE_FRAME_NUM * FIRE_BREATH_NUM;
		}

		// �e�΂̋ʂ̊g�嗦�̏�����
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mFireExpRates[i] = 0;
		}

		// �e�΂̋ʂ̓����蔻���ݒ�
		mOrigHitRangeW = 18, mOrigHitRangeH = 18;
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mBreathHitRangeWs[i] = 0;
			mBreathHitRangeHs[i] = 0;
		}

		// �e�΂̋ʂ�f���Ă��邩�ǂ����̏�����
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			mBreIsExistings[i] = false;
		}

		// �f���o���n�߂�΂̋ʂ�id�̐ݒ�
		mNextBreathId = 0;
	}

	mFrameCnt = 0;
	mFiresExist = true;
}


void BossFire::Update() {
	if (mAttackType == 1) {	// �΂̋ʓf���o���U��
		FireBall();
	}
	else {	// �u���X�U��
		FireBreath();
	}

	mFrameCnt++;
}


void BossFire::Draw() {
	if (mAttackType == 1) {	// �΂̋ʓf���o���U��
		// �e�΂̋ʂ̕`��
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			if (mFrameCnt >= mFireBallFrameNums[i]) {	// �΂̋ʂ�f���o���n�߂Ă�����
				DrawGraph((int)mXs[i] - mImgW / 2, (int)mYs[i] - mImgH / 2, mFireHandle[mBallHandleIds[i]], TRUE);
				DrawBox((int)mXs[i] - mBallHitRangeW, (int)mYs[i] - mBallHitRangeH,
					(int)mXs[i] + mBallHitRangeW, (int)mYs[i] + mBallHitRangeH, GetColor(255, 0, 0), FALSE);
			}
		}
	}
	else {	// �u���X�U��
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			if (mBreIsExistings[i]) {	// �΂̋ʂ����݂��Ă�����
				DrawRotaGraph((int)mXs[i], (int)mYs[i], (double)mFireExpRates[i], 0, *mFireHandle, TRUE);
				DrawBox((int)(mXs[i] - mBreathHitRangeWs[i]), (int)(mYs[i] - mBreathHitRangeHs[i]),
					(int)(mXs[i] + mBreathHitRangeWs[i]), (int)(mYs[i] + mBreathHitRangeHs[i]), GetColor(255, 0, 0), FALSE);
			}
		}
	}
}


void BossFire::FireBall() {
	// �e�΂̋ʂ���ʊO�ɍs���������m�F����
	bool isAtOutside = true;
	for (int i = 0; i < FIRE_BALL_NUM; i++) {
		if (mXs[i] > FIRE_DELETE_LX) {	// 1�̉΂̋ʂł���ʓ��ɂ����
			isAtOutside = false;
		}
	}

	if (isAtOutside) {	// 1�̉΂̋ʂł���ʊO�ɏo�Ă����� 
		Finalize();
	}
	else {
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			if (mFrameCnt >= mFireBallFrameNums[i]) {	 // �΂̋ʂ̓f���o�����n�߂�t���[�����𒴂��Ă�����
				// xy���W�̍X�V������
				mXs[i] += mDXs[i];
				mYs[i] += mDYs[i];

				if (mDYs[i] != 0 &&	// ���ړ����n�߂Ă��Ȃ���
					mYs[i] >= mFireBallYs[i]) {	// ���ړ����n�߂���W�𒴂��Ă�����
					// ���ړ����n�߂�����
					mDXs[i] *= 2;
					mDYs[i] = 0;
					mBallHandleIds[i] = 1;
				}
			}
		}
	}
}


void BossFire::FireBreath() {
	if (mFrameCnt > PREPARING_BRE_FRAME_NUM) {	// �΂̋ʂ�f���o���n�߂�t���[�����𒴂��Ă���Ƃ�
		if (mFrameCnt % BREATHING_NEW_FIRE_FRAME_NUM == 0) {	// �V�����΂̋ʂ�f���o���n�߂�t���[������������
			// �΂̋ʂ�EnemyBoss�̌����̍��W�ɂ���i�߂��j
			mXs[mNextBreathId] = mBossMouthX;
			mYs[mNextBreathId] = mBossMouthY;

			// �g�嗦��0�ɂ���i�߂��j
			mFireExpRates[mNextBreathId] = 0;

			// �΂̋ʂ̈ړ����x��ݒ肷��i�߂��j
			mDXs[mNextBreathId] = -mDDX;// *BREATHING_NEW_FIRE_FRAME_NUM* FIRE_BREATH_NUM;
			mDYs[mNextBreathId] = 26;

			if (mFrameCnt >= BREATHING_FRAME_NUM) {	// �΂̋ʂ�f���o���I����t���[�����𒴂��Ă�����
				// �΂�����
				mBreIsExistings[mNextBreathId] = false;
			}
			else {
				// �΂��o��
				mBreIsExistings[mNextBreathId] = true;
			}

			mNextBreathId = (mNextBreathId + 1) % FIRE_BREATH_NUM;
		}
	}

	for (int i = 0; i < FIRE_BREATH_NUM; i++) {
		if (mBreIsExistings[i]) {
			// ���W�Ɗg�嗦���X�V����
			mXs[i] += mDXs[i];
			mYs[i] = CalcBreathY(mXs[i]);// mDYs[i];
			mFireExpRates[i] += 0.06f;

			// �����蔻��͈̔͂��X�V����
			mBreathHitRangeWs[i] = mOrigHitRangeW * mFireExpRates[i];
			mBreathHitRangeHs[i] = mOrigHitRangeH * mFireExpRates[i];

			// x, y�̑����ʂ��X�V����
			//mDXs[i] += mDDX;
			mDYs[i] += 0.5f;
		}
	}

	if (mFrameCnt >= BREATHING_FRAME_NUM) {	// �΂̋ʂ�f���o���I����t���[�����𒴂��Ă���Ƃ�
		// �΂̋ʂ����ׂď����I����Ă��邩�ǂ����m�F����
		bool hasDeleted = true;
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {
			if (mBreIsExistings[i]) {	// 1�ł��΂������I����Ă��Ȃ�������
				hasDeleted = false;
			}
		}

		if (hasDeleted) {	// ���ׂẲ΂̋ʂ������I����Ă�����
			Finalize();
		}
	}
}


float BossFire::CalcBreathY(const float x) {
	/*float y = -260 / (float)90000 * 
		std::pow(x - mBossMouthX + 300, 2) + 530;*/
	float y = 520 / (1 + exp(0.02 * (x - mBossMouthX))) + 10;
	// y = (260 * 2) / (1 + exp(0.05 * (x - mBossMouthX))) + (270 - 260)

	return y;
}


int BossFire::GetFireNum(const int attackType) const {
	if (attackType == 1) {	// �΂̋ʓf���o���U��
		return FIRE_BALL_NUM;
	}
	else {	// �u���X�U��
		return FIRE_BREATH_NUM;
	}
}


bool BossFire::GetFiresExist() const {
	return mFiresExist;
}


void BossFire::GetFiresXYs(std::vector<int>& xs, std::vector<int>& ys) {
	// �e�΂̋ʂ�xy���W������
	if (mAttackType == 1) {	// �΂̋ʓf���o���U���̂Ƃ�
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			xs.at(i) = mXs[i];
			ys.at(i) = mYs[i];
		}
	}
	else {
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {	// �u���X�U���̂Ƃ�
			xs.at(i) = mXs[i];
			ys.at(i) = mYs[i];
		}
	}
}


void BossFire::GetFiresHitRangeWHs(std::vector<int>& hitRangeWs, std::vector<int>& hitRangeHs) {
	// �e�΂̋ʂ�xy���W������
	if (mAttackType == 1) {	// �΂̋ʓf���o���U���̂Ƃ�
		for (int i = 0; i < FIRE_BALL_NUM; i++) {
			hitRangeWs.at(i) = mBallHitRangeW;
			hitRangeHs.at(i) = mBallHitRangeH;
		}
	}
	else {
		for (int i = 0; i < FIRE_BREATH_NUM; i++) {	// �u���X�U���̂Ƃ�
			hitRangeWs.at(i) = mBreathHitRangeWs[i];
			hitRangeHs.at(i) = mBreathHitRangeHs[i];
		}
	}
}