// Enemy4�`6�̖��@�g���̓G�̊��N���X
#include "Enemy7.h"
#include "DxLib.h"
#include "CharaGraphics.h"
#include <random>


Enemy7::Enemy7(EnemyChanger* changer, const int eneIdx, const int x, const int y)
	: Enemy(changer, CharaGraphics::GetGraHandle(1, 7), eneIdx, x, y) {
}


void Enemy7::Initialize() {
	Enemy::Initialize();

	// �ʒu�ɍ��킹���摜id�̐ݒ�
	if (mX > 600) {	// �E���ɂ���Ƃ�
		mHandleId = 0;
		mAttackDirec = -1;
	}
	else {	// �����ɂ���Ƃ�
		mHandleId = 2;
		mAttackDirec = 1;
	}

	// �����蔻��֘A�̐ݒ�
	mImgW = 303, mImgH = 151;
	mHitRangeW = 29, mHitRangeH = 64;

	// �̗͂ƍU���͂̐ݒ�
	mHp = 1;
	mAttack = 2;
	// �U���̐��̐ݒ�
	mEneANum = 1;	// �a���U���y�ѐ؂���U���ǂ���ɂ����Ă�����1

	// �a���U���Ŏg�p����N���X�̃I�u�W�F�N�g���擾����
	mSlash = new Slash();

	// ����񐔂̐ݒ�
	mDeleteRoDoneNum = 2;

	// ���̑�
	mIsFadingIn = true;	// �ŏ��̓t�F�[�h�C���œ����Ă��邽�߁Ctrue
	mIsFadingOut = false;
	mIsHiding = false;
	mAlphaValue = 0;	// �ŏ��͏����Ă��āC�t�F�[�h�C���œ����Ă��邽�߁C���l��0
	mHidingFrameCnt = 0;
	mAttackFrameCnt = 0;
	mRoutineDoneCnt = 0;
	mHasFinishedRos = false;
	mIsAttacking = false;
	mEne7IsDead = false;
	mIsBoss = false;

	// �|�����瓾����X�R�A�̐ݒ�
	mScore = 2000;
}


void Enemy7::Finalize() {
	delete mSlash;
}


void Enemy7::Update() {
	if (mEne7IsDead || mHasFinishedRos) {	// ���삪�I����Ă��邩�CEnemy7������ł���Ƃ�
		if (!mIsAttacking) {	// �΂̋ʍU�����I����Ă���Ƃ�
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -3000, -3000);	// -3000�͓K���ɉ�ʊO�̐��l�ɂ��Ă���
		}
	}

	// �a���U�����I����Ă��邩�ǂ������擾����
	mIsAttacking = mSlash->GetSlashExist();

	// �a���U���̍X�V���s��
	if (mIsAttacking) {	// �a���U������������
		mSlash->Update();
		std::tie(mAX, mAY) = mSlash->GetSlashXY();
	}

	// Enemy7�̈ʒu�ɍ��킹��Enemy7�̉摜id�̐ݒ�
	if (mAttackDirec == -1) {	// �����������Ă���Ƃ�
		mHandleId = 0;
	}
	else {	// �E�����ނ��Ă���Ƃ�
		mHandleId = 2;
	}

	// Enemy7���̂̍X�V���s��
	if (!mEne7IsDead && !mHasFinishedRos) {	// ��������I���Ă��Ȃ��āC����ł��Ȃ����
		// hp�̍X�V
		UpdateHp();

		if (mIsFadingIn) {	// �t�F�[�h�C�����Ă���Ƃ��i���쏇��1�j
			FadeIn();
		}
		else if (mIsFadingOut) {	// �t�F�[�h�A�E�g���Ă���Ƃ��i���쏇��3�j
			FadeOut();
		}
		else if (mIsHiding) {	// �p���B���Ă���Ƃ��i���쏇��4�j
			Hide();
		}
		else {	// �p�������Ă���Ƃ��i���쏇��2�j
			//if (mHp <= 0) {	// �̗͂�0�ȉ��ƂȂ����Ƃ�
			//	// ���񂾂��Ƃ�F�������邽�߂�10�t���[���̍d��
			//	if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			//		mEne7IsDead = true;
			//	}

			//	// �_���[�W������������Ƃ��킩��摜�ɂ���
			//	mHandleId += 4;

			//	mGodFrameCnt++;
			//}
			if (mRoutineDoneCnt == 0) {	// 1��ڂ̓���̂Ƃ��i����y���W�ړ����Ă���i�G��|�����߂̗P�\���ԁj�j
				if (mAttackFrameCnt == STOP_FRAME_NUM) {
					// �t�F�[�h�A�E�g���n�߂�
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					mAttackFrameCnt++;
				}
			}
			else {	// 2��ڈȍ~�̓���̂Ƃ��i�a���U������j
				if (mAttackFrameCnt == ATTACK_STATE_FRAME_NUM) {
					// �t�F�[�h�A�E�g���n�߂�
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					// �U������̉摜�ɂ���
					mHandleId += 1;

					mAttackFrameCnt++;
				}
			}
		}

		// ���G���Ԃ̍ۂ̉摜�̓_�ŏ���
		if (mIsGod) {
			if (mHp > 0) {	// hp > 0 �̂Ƃ�
				if (mGodFrameCnt == GOD_FRAME_NUM) {	// ���G���Ԃ��I�������
					mIsGod = false;
					mGodFrameCnt = 0;
				}
				else {	// ���G���Ԓ��Ȃ�
					// ���G���Ԃł��邱�Ƃ�\���摜�ɂ���
					if ((mGodFrameCnt / 20) % 2 == 0) {	// �_�ŏ���
						mHandleId += 4;
					}

					mGodFrameCnt++;
				}
			}
			else {	// hp��0�ȉ��ƂȂ����Ƃ�
					// ���񂾂��Ƃ�F�������邽�߂�10�t���[���̍d��
				if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
					mEne7IsDead = true;
				}
				else if (mGodFrameCnt == 0) {	// �|�����u�ԁC�X�R�A������悤�ɂ���
					mIsDead = true;
				}
				else {
					mIsDead = false;
				}

				// �_���[�W������������Ƃ��킩��摜�ɂ���
				mHandleId += 4;
				mAlphaValue = 255;

				mGodFrameCnt++;
			}
		}
	}
}


void Enemy7::Draw() {
	// Enemy7�̕`��
	if (!mEne7IsDead && !mHasFinishedRos) {	// ��������I���Ă��Ȃ��āC����ł��Ȃ����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
		DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 11, mEneHandle[mHandleId], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// �a���U���̕`��
	if (mIsAttacking) {	// �a���U�������Ă���Ƃ�
		mSlash->Draw();
	}
}


void Enemy7::FadeIn() {
	// ���l�̍X�V
	if (mAlphaValue < 255) {
		mAlphaValue += DELTA_ALPHA;
	}

	if (mAlphaValue > 255) {
		mAlphaValue = 255;
	}

	if (mAlphaValue == 255) {
		// �t�F�[�h�C�����I������
		mIsFadingIn = false;

		if (mRoutineDoneCnt >= 1) {	// 2��ڂ̓���ȍ~
			// �a���U�����n�߂�
			// (1: �Œ�ʒu�̎a���U���C2: ��΂��a���U��)
			mSlash->StartSlash(mX, mY, mAttackDirec, mAttackType);

			// �a���̓����蔻��͈͂��󂯎��
			std::tie(mHitRangeAW, mHitRangeAH) = mSlash->GetSlashHitRange();
		}
	}
}


void Enemy7::FadeOut() {
	// ���l�̍X�V
	if (mAlphaValue > 0) {
		mAlphaValue -= DELTA_ALPHA;
	}

	if (mAlphaValue < 0) {
		mAlphaValue = 0;
	}

	if (mAlphaValue == 0) {
		// �t�F�[�h�A�E�g���I������
		mIsFadingOut = false;

		// ������I�����񐔂𑝂₷
		mRoutineDoneCnt++;

		if (mRoutineDoneCnt < mDeleteRoDoneNum) {	// ����̉񐔂��I���񐔂ɒB���Ă��Ȃ�������
			// ������n�߂�O�̎p�������Ă��鎞�Ԃ��n�߂�
			mIsHiding = true;
		}
		else {	// ����̉񐔂��I���񐔂ɒB���Ă�����
			// ������I�������Ƃɂ���
			mHasFinishedRos = true;
		}
	}
}


void Enemy7::Hide() {
	if (!mIsAttacking && mHidingFrameCnt >= HIDING_FRAME_NUM_MIN) {	// �a���U�����I����Ă��āC������̎��Ԉȏ�B��Ă�����
		// �B���̂��I������
		mIsHiding = false;
		mHidingFrameCnt = 0;

		// �����̃V�[�h�l���X�V
		std::random_device rnd;

		// ���̍U���̎�ނ����߂�
		for (int i = 0; i < mEneIdx + 1; i++) {	// for���͓����t���[���ɂ�����rand()�̒l������mIdx��Enemy�ƈ�v���Ȃ��悤�ɂ��邽��
			mAttackType = rnd() % 2 * (-2) + 1;	// 1��-1������
		}
		
		// ����xy���W�����߂�
		int xNext, yNext;
		if (mAttackType == 1) {	// �Œ�ʒu�̎a���U���iPlayer�̖ڑO�Ɍ���؂����j
			// �U���̌��������߂�
			mAttackDirec = rnd() % 2 * (-2) + 1;	// 1��-1������

			xNext = mPlX - 150 * mAttackDirec;	// Player�̍������E���Ɍ����
			yNext = mPlY;
		}
		else {	// ��΂��a���U��
			// Player���牓������x���W�ɂ���
			if (mPlX > 600) {	// �E���ɂ�����
				xNext = rnd() % (150 + 1) + 80;
				yNext = mPlY + 50;
				mAttackDirec = 1;
			}
			else {	// �����ɂ�����
				xNext = rnd() % (150 + 1) + 1000;
				yNext = mPlY + 50;
				mAttackDirec = -1;
			}
		}
		
		// �V����xy���W���Z�b�g����
		mX = xNext;
		mY = yNext;

		// �t�F�[�h�C�����n�߂�
		mIsFadingIn = true;
	}
	else {
		mHidingFrameCnt++;
	}
}


void Enemy7::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// �t�F�[�h�A�E�g���Ă���Ƃ��Ǝp�������Ă���Ƃ��C
	// ������I�����Ƃ��CEnemy7�͎���ł���Ƃ��i�������a���͎c���Ă���Ƃ��j��
	// �G�̓����蔻��͉�ʊO�ɐݒ肷��
	if (mIsFadingOut || mIsHiding || mEne7IsDead || mHasFinishedRos) {
		(*eneIntDataMap)["x"] = -3000;
		(*eneIntDataMap)["y"] = -3000;
	}
	
	// �e�a���̓����蔻��֘A�̏���n��
	if (mIsAttacking) {	// �U�����̂Ƃ�
		for (int i = 0; i < mEneANum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAX;
			(*eneAXYMapVec).at(i)["ay"] = mAY;
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAW;
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAH;
		}
	}
}


