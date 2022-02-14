// �C�m�V�V2�ihp2�j
#include "Enemy2.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy2::Enemy2(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyBoar(changer, CharaGraphics::GetGraHandle(1, 2), itemIdx, x, y) {
}


void Enemy2::Initialize() {
	EnemyBoar::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 250, mImgH = 177;

	// �U����̗͂̐ݒ�
	mEneANum = 0;	// �̓����肷�邾��������0
	mHp = 2;
}


void Enemy2::Update() {
	if (mHp > 0 && mX >= ENE_BOAR_DELETE_X) {	// �����Ă��āC��ʓ��ɂ���Ƃ��̏���
		// hp�̍X�V
		UpdateHp();

		Walk();

		if (mIsGod) {	// �U�����󂯂���̖��G���Ԃ̂Ƃ�
			if (mGodFrameCnt == GOD_FRAME_NUM) {	// ���G���Ԃ��I�������
				mIsGod = false;
				mGodFrameCnt = 0;
			}
			else {	// ���G���Ԓ��Ȃ�
				// ���G���Ԃł��邱�Ƃ�\���摜�ɂ���
				if ((mGodFrameCnt / 20) % 2 == 0) {	// �_�ŏ���
					mHandleId += 2;
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
		mHandleId = 2;

		mGodFrameCnt++;
	}
}


void Enemy2::Draw() {
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, mEneHandle[mHandleId], TRUE);
}

