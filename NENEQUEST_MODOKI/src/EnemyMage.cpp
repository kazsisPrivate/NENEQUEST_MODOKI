// Enemy4�`6�̖��@�g���̓G�̊��N���X
#include "EnemyMage.h"
#include "DxLib.h"
#include <time.h>


EnemyMage::EnemyMage(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y)
	: Enemy(changer, graph, eneIdx, x, y) {
}


void EnemyMage::Initialize() {
	Enemy::Initialize();

	// �ʒu�ɍ��킹���摜id�̐ݒ�
	if (mX > 600) {	// �E���ɂ���Ƃ�
		mHandleId = 0;
	}
	else {	// �����ɂ���Ƃ�
		mHandleId = 2;
	}

	// �����蔻��֘A�̐ݒ�
	mHitRangeW = 29, mHitRangeH = 64;

	// �ړ����x��U���͂̐ݒ�
	mSpeed = 3.0f;
	mDirecY = 1;

	// �΂̋ʍU���Ŏg�p����N���X�̃I�u�W�F�N�g���擾����
	mMageFire = new MageFire();
	// �΂̋ʂ̐����󂯎��
	mFireNum = mMageFire->GetFireNum();
	mEneANum = mFireNum;
	// �e�΂̋ʂ�xy���W������vector������������
	for (int i = 0; i < mFireNum; i++) {
		mAXs.push_back(0);
		mAYs.push_back(0);
	}
	// �΂̋ʂ̓����蔻��͈͂��󂯎��
	std::tie(mHitRangeAW, mHitRangeAH) = mMageFire->GetFiresHitRange();

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
	mMageIsDead = false;
}


void EnemyMage::Finalize() {
	delete mMageFire;
}


void EnemyMage::Update() {
	if (mMageIsDead || mHasFinishedRos) {	// ���삪�I����Ă��邩�CEnemyMage������ł���Ƃ�
		if (!mIsAttacking) {	// �΂̋ʍU�����I����Ă���Ƃ�
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -3000, -3000);	// -3000�͓K���ɉ�ʊO�̐��l�ɂ��Ă���
		}	
	}

	// �΂̋ʍU�����I����Ă��邩�ǂ������擾����
	mIsAttacking = mMageFire->GetFiresExist();

	// �΂̋ʍU���̍X�V���s��
	if (mIsAttacking) {	// �΂̋ʍU������������
		mMageFire->Update();
		mMageFire->GetFiresXYs(mAXs, mAYs);
	}

	// EnemyMage�̈ʒu�ɍ��킹��EnemyMage�̉摜id�̐ݒ�
	if (mX > 600) {	// �E���ɂ���Ƃ�
		mHandleId = 0;
	}
	else {	// �����ɂ���Ƃ�
		mHandleId = 2;
	}

	// EnemyMage���̂̍X�V���s��
	if (!mMageIsDead && !mHasFinishedRos) {	// ��������I���Ă��Ȃ��āC����ł��Ȃ����
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
			//		mMageIsDead = true;
			//	}

			//	// �_���[�W������������Ƃ��킩��摜�ɂ���
			//	mHandleId += 4;

			//	mGodFrameCnt++;
			//}
			if (mRoutineDoneCnt == 0) {	// 1��ڂ̓���̂Ƃ��i����y���W�ړ����Ă���i�G��|�����߂̗P�\���ԁj�j
				if (mAttackFrameCnt == WALK_FRAME_NUM) {
					// �t�F�[�h�A�E�g���n�߂�
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					// y���W�̈ړ�������
					Walk();

					mAttackFrameCnt++;
				}
			}
			else {	// 2��ڈȍ~�̓���̂Ƃ��i�΂̋ʍU������j
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
					mMageIsDead = true;
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


void EnemyMage::Draw() {
	// EnemyMage�̕`��
	if (!mMageIsDead && !mHasFinishedRos) {	// ��������I���Ă��Ȃ��āC����ł��Ȃ����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
		DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 11, mEneHandle[mHandleId], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	//DrawBox(x - hitRangeX, y - hitRangeY, x + hitRangeX, y + hitRangeY, GetColor(0, 0, 0), TRUE);
	//DrawFormatString(800, 300, GetColor(255, 255, 255), "px = %d", count);

	// �΂̋ʍU���̕`��
	if (mIsAttacking) {	// �΂̋ʍU�������Ă���Ƃ��i��ʓ���1�ł��΂̋ʂ�����Ƃ��j
		mMageFire->Draw();
	}
}


void EnemyMage::Walk() {
	if (mY > ENE_MAGE_Y_MAX || mY < ENE_MAGE_Y_MIN) {	// �͈͊O�Ɉړ�������
		// �ړ������𔽓]����
		mDirecY *= -1;
	}

	// y���W�̍X�V
	mY += (int)(mDirecY * mSpeed);
}


void EnemyMage::FadeIn() {
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
			// �g�p����΂̋ʍU���̎�ނ����߂�
			// (1: �W�O�U�O�U���C2: ��]�U��)
			// 1�`2�̃����_���Ȑ��l�𐶐�
			srand((unsigned int)time(NULL));
			int attackType;
			for (int i = 0; i < mEneIdx + 1; i++) {
				attackType = rand() % 2 + 1;
			}

			// �΂̋ʍU�����n�߂�
			mMageFire->StartFire(mX, mY, mFireType, attackType);
		}
	}
}


void EnemyMage::FadeOut() {
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


void EnemyMage::Hide() {
	if (!mIsAttacking && mHidingFrameCnt >= HIDING_FRAME_NUM_MIN) {	// �΂̋ʍU�����I����Ă��āC������̎��Ԉȏ�B��Ă�����
		// �B���̂��I������
		mIsHiding = false;
		mHidingFrameCnt = 0;

		// ����xy���W�����߂�
		srand((unsigned int)time(NULL));
		
		int xNext, yNext;
		// Player���牓������x���W�ɂ���
		if (mPlX > 600) {	// �E���ɂ�����
			for (int i = 0; i < mEneIdx + 1; i++) {	// for���͓����t���[���ɂ�����rand()�̒l������mIdx��Enemy�ƈ�v���Ȃ��悤�ɂ��邽��
				xNext = rand() % (150 + 1) + 80;
				yNext = rand() % (ENE_MAGE_Y_MAX - ENE_MAGE_Y_MIN + 1) + ENE_MAGE_Y_MIN;
			}
		}
		else {	// �����ɂ�����
			for (int i = 0; i < mEneIdx + 1; i++) {
				xNext = rand() % (150 + 1) + 1000;
				yNext = rand() % (ENE_MAGE_Y_MAX - ENE_MAGE_Y_MIN + 1) + ENE_MAGE_Y_MIN;
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


void EnemyMage::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// �t�F�[�h�A�E�g���Ă���Ƃ��Ǝp�������Ă���Ƃ��C
	// ������I�����Ƃ��CEnemyMage�͎���ł���Ƃ��i�������΂̋ʂ͎c���Ă���Ƃ��j��
	// �G�̓����蔻��͉�ʊO�ɐݒ肷��
	if (mIsFadingOut || mIsHiding || mMageIsDead || mHasFinishedRos) {
		(*eneIntDataMap)["x"] = -3000;
		(*eneIntDataMap)["y"] = -3000;
	}
	
	// �e�΂̋ʂ̓����蔻��֘A�̏���n��
	if (mIsAttacking) {	// �U�����̂Ƃ�
		for (int i = 0; i < mFireNum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAXs.at(i);
			(*eneAXYMapVec).at(i)["ay"] = mAYs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAW;
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAH;
		}
	}
}


