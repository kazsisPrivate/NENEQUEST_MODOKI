#include "EnemyBoss.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <random>
//#include <math.h>


EnemyBoss::EnemyBoss(EnemyChanger* changer, const int eneIdx, const int x, const int y)
	: Enemy(changer, CharaGraphics::GetGraHandle(1, 8), eneIdx, x, y) {
}


void EnemyBoss::Initialize() {
	Enemy::Initialize();

	// �����蔻��֘A�̐ݒ�
	mHitRangeW = 78, mHitRangeH = 220;

	// �ŏ��̕\���摜��id�̐ݒ�
	mHandleId = 0;

	// �̗͂ƍU���͂̐ݒ�
	mHp = 45;
	mAttack = 1;	// �{���Ԃ̑O�̍U����
	// �U���̐��̐ݒ�
	mEneANum = 0;	// �U���̎�ނɂ���ĕω�����iFireBall: 3, FireBreath: 5, SummonItem: 1�j

	// �U���̓����蔻��֘A�̐ݒ�
	for (int i = 0; i < ENEBOSS_ATTACK_NUM_MAX; i++) {
		mAXs.push_back(0);
		mAYs.push_back(0);
		mHitRangeAWs.push_back(0);
		mHitRangeAHs.push_back(0);
	}

	// �ړ����x�֘A�̐ݒ�
	mSpeed = 2.0f;
	mDirecX = 1;

	// �΂̋ʍU���Ŏg�p����N���X�̃I�u�W�F�N�g���擾����
	mBossFire = new BossFire();

	// ���̑�
	mAlphaValue = 255;
	mWatingFrameCnt = 0;
	mAFrameCnt = 0;
	mIsAttacking = false;
	mIsFireAttacking = false;
	mIsSummoningEne = false;
	mIsDroppingIteB = false;
	mIsJumping = false;
	mIteBHandle = NULL;
	mIsCreatingIteB = false;
	mCreIteBFrameCnt = 0;
	mIsChangingSt = true;	// EnemyBoss���쐬�����̂�BossStage�ւ̈ڍs���Ȃ̂�true
	mIsBoss = true;	// EnemyBoss�Ȃ̂�true

	// �X�R�A�̐ݒ�
	mScore = 10000;
}


void EnemyBoss::Finalize() {

}


void EnemyBoss::Update() {
	if (mIsChangingSt) {	// BossStage�ւ̈ڍs����������
		// ��ʊO�E������K��̈ʒu�܂ł̈ړ�
		if (mX > ENEBOSS_FIRST_X) {	// �K��̈ʒu�ɂ��Ă��Ȃ����
			mX -= 1;
		}
		else {	// �K��̈ʒu�ւ̈ړ����I�������
			// BossStage���n�߂�
			mIsChangingSt = false;
		}
	}
	else {
		// �x�[�X�̉摜�̐ݒ�
		if (mHp > HP_ANGRY) {	// �ʏ탂�[�h�̂Ƃ�
			mHandleId = 0;
		}
		else {	// �{�胂�[�h�̂Ƃ�
			mHandleId = 12;
		}

		// hp�̍X�V
		UpdateHp();

		// �U���͂ƈړ����x�̍X�V
		UpdateSAP();

		if (mIsAttacking) {	// �U�����̂Ƃ�
			Attack();
		}
		else {	// �U�����łȂ��Ƃ�
			// �ړ�
			Walk();

			// �U�������邩�ǂ��������߂�
			if (mWatingFrameCnt % ATTACK_FRAME_NUM == 0 && mWatingFrameCnt != 0) {
				// �s���U�������߂�
				SelectAttack();
			}

			mWatingFrameCnt++;
		}


		if (mIsGod) {	// �U�����󂯂���̖��G���Ԃ̂Ƃ�
			if (mGodFrameCnt == GOD_FRAME_NUM) {	// ���G���Ԃ��I�������
				mIsGod = false;
				mGodFrameCnt = 0;
			}
			else {	// ���G���Ԓ��Ȃ�
				// ���G���Ԃł��邱�Ƃ�\���摜�ɂ���
				if ((mGodFrameCnt / 20) % 2 == 0) {	// �_�ŏ���
					mHandleId += 6;
				}

				mGodFrameCnt++;
			}
		}
	}
}


void EnemyBoss::Draw() {
	// �����x�̐ݒ�
	if (mHp <= 0) { //�|���ꂽ�Ƃ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
	}

	// EnemyBoss�̉摜�̕`��
	DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mEneHandle[mHandleId], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(mX - mHitRangeW, mY - mHitRangeH, mX + mHitRangeW, mY + mHitRangeH, GetColor(255, 0, 0), FALSE);

	// DropItemBox�ōs��ItemBox���Ƃ��U����ItemBox�̉摜�̕`��
	if (mIteBHandle) {	// �`�悷��ItemBox���Z�b�g����Ă�����
		DrawGraph(mIteBX - mIteBImgW / 2, mIteBY - mIteBImgH / 2, mIteBHandle[0], TRUE);
		DrawBox(mIteBX - mIteBHitRangeW, mIteBY - mIteBHitRangeH,
			mIteBX + mIteBHitRangeW, mIteBY + mIteBHitRangeH, GetColor(255, 0, 0), FALSE);
	}

	// �΂̋ʍU���̉摜�̕`��
	if (mIsFireAttacking) {	// �΂̋ʍU�����̂Ƃ�
		mBossFire->Draw();
	}
}


void EnemyBoss::UpdateSAP() {
	if (mHp > HP_ANGRY) {	// �ʏ탂�[�h�̂Ƃ�
		mSpeed = 2.0f;
		mAttack = 1;
	}
	else {	// �{�胂�[�h�̂Ƃ�
		mSpeed = 3.0f;
		mAttack = 2;
	}
}


void EnemyBoss::Walk() {
	// x���W�̍X�V
	mX -= (int)(mSpeed * mDirecX);

	if (mX < ENEBOSS_X_MIN || mX > ENEBOSS_X_MAX) {	// �ړ��͈͂𒴂�����
		// �����؂�ւ�
		mDirecX *= -1;
	}

	int ix = abs(mX) % 40 / 20;
	mHandleId += ix;
}


void EnemyBoss::Attack() {
	if (mIsSummoningEne) {	// Enemy�Ăяo���U�����̂Ƃ�
		SummonEnemy();
	}
	else if (mIsDroppingIteB) {	// ItemBox���Ƃ��U�����̂Ƃ�
		DropItemBox();
	}
	else {	// �΂̋ʍU�����̂Ƃ�
		FireAttack();
	}
}


void EnemyBoss::SelectAttack() {
	// �s���U����I������
	// �����U��������m���i0�`10000, 10000��100%�j�����߂�
	int attackProb = 10000 - std::pow(5000, ATTACK_FRAME_NUM/ mWatingFrameCnt);

	// 1�`10000�̃����_���Ȑ��l�𐶐�
	std::random_device rnd;
	int randNum = rnd() % 10000 + 1;

	// �s���U����I���i10000 - attackProb�̊m���ōU�������Ȃ��j
	if (randNum >= 10000 - attackProb) {	// �����U��������Ƃ�
		// randNum��1�`attackProb�͈̔͂ɂ����̂��C1�`100�͈̔͂̒l�ɐ��K������
		randNum = 10000 - randNum + 1;
		randNum = (randNum / (float)attackProb) * 100;

		if (randNum <= 25) {	// 50%�̊m����
			// Enemy�Ăяo���U��
			mIsSummoningEne = true;
			mEneANum = 0;
		}
		else if (randNum <= 50) {	// 50%�̊m����
			// ItemBox���Ƃ��U��
			mIsDroppingIteB = true;
			mEneANum = 1;
		}
		else {	// 50%�̊m����
			// �΂̋ʍU��
			int fireType;
			if (mHp > HP_ANGRY) {	// �ʏ탂�[�h�̂Ƃ�
				// �Ԃ��΂̋�
				fireType = 1;
			}
			else {	// �{�胂�[�h�̂Ƃ�
				// ���΂̋�
				fireType = 2;
			}
			if (randNum <= 75) {	// 25%�̊m����
				// �΂̋ʓf���o���U��
				mBossFire->StartFire(mX, mY, fireType, 1);
				mEneANum = mBossFire->GetFireNum(1);
			}
			else {	// 25%�̊m����
				// �u���X�U��
				mBossFire->StartFire(mX, mY, fireType, 2);
				mEneANum = mBossFire->GetFireNum(2);
			}
			
			mIsFireAttacking = true;
		}

		mIsAttacking = true;
		mWatingFrameCnt = 0;
	}
}


void EnemyBoss::SummonEnemy() {
	if (mAFrameCnt == 300) {
		// ���̍U�����ł���悤�ɂ���
		mIsAttacking = false;
		mIsSummoningEne = false;
		mAFrameCnt = 0;
	}
	else if (mAFrameCnt >= 30 && mAFrameCnt <= 90) {	// �Ăт����Ă���Ƃ�
		// �Ăяo�������Ă���摜�ɂ���
		mHandleId += 4;

		// Enemy���Z�b�g����
		if (mAFrameCnt == 90) {
			CreateEnemy();
		}

		mAFrameCnt++;
	}
	else {	// �G���Ăт����O�ƌĂяo����ɏ����Î~������Ƃ�
		mAFrameCnt++;
	}
}


void EnemyBoss::CreateEnemy() {
	std::random_device rnd;

	int eneX, eneY;	// ��������G��xy���W
	eneY = rnd() % (ENEMY_FIRST_Y_MAX - ENEMY_FIRST_Y_MIN) + ENEMY_FIRST_Y_MIN;
	
	// �Ăт����G�̎�ނ����߂�
	EEnemy eneKind;
	int randNum = rnd() % 100 + 1;	// 1�`100�̗���
	if (mHp > HP_ANGRY) {	// �ʏ탂�[�h�̂Ƃ�
		if (randNum <= 60) {	// 60%�̊m����
			// �C�m�V�V�̓G
			eneX = 1400;

			if (randNum <= 30) {	// 30%�̊m����
				// Enemy1
				eneKind = eEnemy1;
			}
			else if (randNum <= 50) {	// 20%�̊m����
				// Enemy2
				eneKind = eEnemy2;
			}
			else {	// 10%�̊m����
				// Enemy3
				eneKind = eEnemy3;
			}
		}
		else {	// 40%�̊m����
			// ���@�g���̓G
			// x���W��Player���痣�ꂽ�ʒu�ɂ���
			if (mPlX > 600) {	// Player���E���ɂ�����
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Player�������ɂ�����
				eneX = rand() % (150 + 1) + 1000;
			}
			
			if (randNum <= 90) {	// 30%�̊m����
				// Enemy4
				eneKind = eEnemy4;
			}
			else {	// 10%�̊m����
				// Enemy5
				eneKind = eEnemy5;
			}
		}
	}
	else {	// �{�胂�[�h�̂Ƃ�
		if (randNum <= 30) {	// 30%�̊m����
			// �C�m�V�V�̓G
			eneX = 1400;

			// Enemy3
			eneKind = eEnemy3;
		}
		else if (randNum <= 60) {	// 30%�̊m����
			// ���@�g���̓G
			// x���W��Player���痣�ꂽ�ʒu�ɂ���
			if (mPlX > 600) {	// Player���E���ɂ�����
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Player�������ɂ�����
				eneX = rand() % (150 + 1) + 1000;
			}

			// Enemy6
			eneKind = eEnemy6;
		}
		else {	// 40%�̊m����
			// ���g��
			// x���W��Player���痣�ꂽ�ʒu�ɂ���
			if (mPlX > 600) {	// Player���E���ɂ�����
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Player�������ɂ�����
				eneX = rand() % (150 + 1) + 1000;
			}

			// Enemy7
			eneKind = eEnemy7;
		}
	}

	// �G�𐶐�����
	mEnemyChanger->ChangeEnemy(-1, eneKind, eneX, eneY);
}


void EnemyBoss::DropItemBox() {
	if (mAFrameCnt == 0) {	// �ŏ��ɒʂ����Ƃ�
		std::random_device rnd;

		// ����������ItemBox��xy���W
		mIteBX = rnd() % (ITEMBOX_FIRST_X_MAX - ITEMBOX_FIRST_X_MIN) + ITEMBOX_FIRST_X_MIN;
		mIteBY = -100;

		// �U���̍��W���Z�b�g���Ă���
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		// �������x�̏������i��ɏ��X�ɉ������Ă����j
		mIteBDY = 1;

		// ����������ItemBox�����߂�
		int randNum = rnd() % 100 + 1;	// 1�`100�̗���
		if (randNum <= 50) {	// 50%�̊m����
			// Item12�i�M1�j
			mIteBKind = eItem12;

			mIteBHandle = ItemGraphics::GetGraHandle(12);
			mIteBImgW = 162, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
			
		}
		else if (randNum <= 30) {	// 30%�̊m����
			// Item13�i�M2�j
			mIteBKind = eItem13;

			mIteBHandle = ItemGraphics::GetGraHandle(13);
			mIteBImgW = 162, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
		}
		else {	// 20%�̊m����
			// Item14�i���j
			mIteBKind = eItem14;

			mIteBHandle = ItemGraphics::GetGraHandle(14);
			mIteBImgW = 164, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
		}

		// �����蔻��̍X�V
		mHitRangeAWs.at(0) = mIteBHitRangeW;
		mHitRangeAHs.at(0) = mIteBHitRangeH;

		// ItemBox�𗎉�������A�N�V�����̃W�����v���n�߂�
		mIsJumping = true;
		mYStart = mY;
		mYPrev = mY;
		mY = mY - 17;

		mAFrameCnt++;
	}
	else if (mIsJumping) {	// �W�����v����������
		Jump();

		// �U���̍��W���Z�b�g���Ă���
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
	}
	else if (mIteBY < 500) {
		// ItemBox�𗎉�������
		mIteBY += mIteBDY;
		mIteBDY++;

		// �U���̍��W���Z�b�g���Ă���
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
	}
	else if (mCreIteBFrameCnt <= 1) {	// ItemBox�𗎉������I�������
		if (mCreIteBFrameCnt == 0) {
			// ItemMgr�𗎉��������ʒu��ItemMgr�̕��Ŏ��ۂ�ItemBox���쐬����(2�t���[���K�v)
			mIsCreatingIteB = true;
		}
		else {
			mIsCreatingIteB = false;
		}

		// �U���̍��W���Z�b�g���Ă���
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
		mCreIteBFrameCnt++;
	}
	else {	// ItemMgr�̕���ItemBox���쐬���Ă��������
		mCreIteBFrameCnt = 0;
		mIteBHandle = NULL;

		// �U���̍��W����ʊO�ɂ��Ă���
		mAXs[0] = 3000;	// �K���ȉ�ʊO
		mAYs[0] = 3000;
		
		// ���̍U�����ł���悤�ɂ���
		mIsAttacking = false;
		mIsDroppingIteB = false;
		mAFrameCnt = 0;
	}
}


void EnemyBoss::Jump() {
	int yTemp = mY;
	mY += (mY - mYPrev) + 1;
	mYPrev = yTemp;

	if (mY == mYStart) {
		mIsJumping = false;
	}
}


void EnemyBoss::FireAttack() {
	// �΂̋ʍU�����I����Ă��邩�m�F����
	mIsFireAttacking = mBossFire->GetFiresExist();

	if (mIsFireAttacking) {	// �΂̋ʍU�����Ȃ�
		// �����J���Ă���摜�ɂ���
		mHandleId += 2;

		// �΂̋ʂ��X�V����
		mBossFire->Update();

		// �΂̋ʂ̓����蔻����擾����
		mBossFire->GetFiresXYs(mAXs, mAYs);
		mBossFire->GetFiresHitRangeWHs(mHitRangeAWs, mHitRangeAHs);
	}
	else {	// �΂̋ʍU�����I����Ă�����
		// �U���̍��W����ʊO�ɂ��Ă���
		for (int i = 0; i < ENEBOSS_ATTACK_NUM_MAX; i++) {
			mAXs[i] = 3000;
			mAYs[i] = 3000;
		}
		
		mIsAttacking = false;
	}
}


void EnemyBoss::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, 
	std::vector<std::map<std::string, int>>* eneAXYMapVec, std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// DropItemBox�Ő�������ItemBox�̐������߂̃Z�b�g
	(*eneBoolDataMap)["isCreatingIteB"] = mIsCreatingIteB;
	if (mIsCreatingIteB) {	// ItemMgr��ItemBox�������Ăق����Ƃ�
		(*eneIntDataMap)["itemBoxKind"] = mIteBKind;
		(*eneIntDataMap)["itemBoxX"] = mIteBX;
		(*eneIntDataMap)["itemBoxY"] = mIteBY;
	}

	// �U���̓����蔻��֘A
	if (mIsAttacking) {	// �U�����̂Ƃ�
		for (int i = 0; i < mEneANum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAXs.at(i);
			(*eneAXYMapVec).at(i)["ay"] = mAYs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAWs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAHs.at(i);
		}
	}
}