// �C�m�V�V3�ihp1, �p�˂��o���U������j
#include "Enemy3.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy3::Enemy3(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyBoar(changer, CharaGraphics::GetGraHandle(1, 3), itemIdx, x, y) {
}


void Enemy3::Initialize() {
	EnemyBoar::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 393, mImgH = 177;
	mHitRangeAW = 60, mHitRangeAH = 35;

	// �U����̗͂̐ݒ�
	mAX = mX - 124, mAY = mY;
	mEneANum = 1;	// �̓����肷�邾��������0
	mHp = 1;
}


void Enemy3::Update() {
	if (mHp > 0 && mX >= ENE_BOAR_DELETE_X) {	// �����Ă��āC��ʓ��ɂ���Ƃ��̏���
		// hp�̍X�V
		UpdateHp();

		Walk();

		Attack();

		if (mIsGod) {	// �U�����󂯂���̖��G���Ԃ̂Ƃ�
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

		mExistingFrameCnt++;
	}
	else {	// ��ʊO�ɍs�����C���񂾂Ƃ��̏����i���񂾂Ƃ��͎��񂾂��Ƃ�F�������邽�߂�10�t���[���̍d�����s���j
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM || mX < ENE_BOAR_DELETE_X) {
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -1000, -1000);	// -1000�͓K���ɉ�ʊO�̐��l�ɂ��Ă���
		}

		// �_���[�W������������Ƃ��킩��摜�ɂ���
		if (mGodFrameCnt == 0) {	// else�̒����ŏ��ɒʂ����Ƃ��ɐݒ肷��
			mHandleId += 4;
		}

		mGodFrameCnt++;
	}
}


void Enemy3::Draw() {
	DrawGraph(mX - mImgW / 2 - 72, mY - mImgH / 2, mEneHandle[mHandleId], TRUE);
}


void Enemy3::Attack() {
	// �U���̍��W�̍X�V
	mAX = mX - 124;
	mAY = mY;

	if (mIsAttacking) {	// �p�U�����Ȃ�
		// �p�U���̉摜�ɂ���
		mHandleId += 2;
	}
	else if ((mX > mPlX) && (mX < mPlX + 400)
		&& (mY > mPlY - 100) && (mY < mPlY + 100)) {	// Enemy3��Player�̋߂��ɋ߂Â����Ƃ�
		// �p��L�΂�����Ԃɂ���
		mIsAttacking = true;
	}
}


void Enemy3::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	(*eneAXYMapVec).at(0)["ax"] = mAX;
	(*eneAXYMapVec).at(0)["ay"] = mAY;
	(*eneAXYMapVec).at(0)["hitRangeAW"] = mHitRangeAW;
	(*eneAXYMapVec).at(0)["hitRangeAH"] = mHitRangeAH;
}