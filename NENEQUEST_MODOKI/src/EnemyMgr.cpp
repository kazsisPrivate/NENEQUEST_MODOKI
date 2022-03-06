#include "DxLib.h"
#include "Enemy.h"
#include "Enemy1.h"	// ��������C�m�V�V�n
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"	// �������疂�p�t�n
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"	// �������炻�̑�
#include "EnemyBoss.h"
#include "EnemyMgr.h"
#include <cmath>
#include <random>


EnemyMgr* EnemyMgr::mEnemyMgr;


EnemyMgr* EnemyMgr::GetInstance() {
	if (!EnemyMgr::mEnemyMgr) {
		EnemyMgr::mEnemyMgr = new EnemyMgr();
		EnemyMgr::mEnemyMgr->Initialize();
	}

	return EnemyMgr::mEnemyMgr;
}


void EnemyMgr::Initialize() {
	// Enemy�������Z�b�g����Ă��Ȃ���Ԃɏ�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEnemies[i] = NULL;
		mEnesNext[i] = eEnemyNone;

		mEnesNextX[i] = -3000;
		mEnesNextY[i] = -3000;
	}
	//mEnesNext[0] = eEnemyNone;	// �f�o�b�O�p
	//mEnesNext[1] = eEnemyNone;	// �f�o�b�O�p
	//mEnesNext[2] = eEnemyNone;	// �f�o�b�O�p

	mPlX = 0;
}


void EnemyMgr::Finalize() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->Finalize();
		}
	}

	delete mEnemyMgr;
	mEnemyMgr = NULL;
}


void EnemyMgr::Update() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnesNext[i] != eEnemyNone) {	// ����Enemy���Z�b�g����Ă���Ƃ�
			if (mEnemies[i]) {	// mEnemies[i]�̒���NULL�łȂ��Ƃ�
				// �I������������
				mEnemies[i]->Finalize();
				delete mEnemies[i];
			}

			// ����Enemy�ɕύX����
			switch (mEnesNext[i]) {
			case eEnemy1:
				mEnemies[i] = (Enemy*) new Enemy1(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy2:
				mEnemies[i] = (Enemy*) new Enemy2(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy3:
				mEnemies[i] = (Enemy*) new Enemy3(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy4:
				mEnemies[i] = (Enemy*) new Enemy4(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy5:
				mEnemies[i] = (Enemy*) new Enemy5(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy6:
				mEnemies[i] = (Enemy*) new Enemy6(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemy7:
				mEnemies[i] = (Enemy*) new Enemy7(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			case eEnemyBoss:
				mEnemies[i] = (Enemy*) new EnemyBoss(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;
			default:	// case eEnemyNULL
				mEnemies[i] = NULL;
				break;
			}

			mEnesNext[i] = eEnemyNone;

			if (mEnemies[i]) {
				mEnemies[i]->Initialize();
			}
		}
	}

	// �eEnemy�̍X�V����������
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->Update();
		}
	}
}


void EnemyMgr::Draw(const int eneIdx) {
	if (mEnemies[eneIdx]) {
		mEnemies[eneIdx]->Draw();
	}
}


void EnemyMgr::ChangeEnemy(const int eneIdx, EEnemy eneNext, const int eneNextX, const int eneNextY) {
	if (eneIdx == -1) {
		// mEnemies�ŋ󂢂Ă���Ƃ��낪����΃Z�b�g����
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!mEnemies[i]) {
				mEnesNext[i] = eneNext;

				mEnesNextX[i] = eneNextX;
				mEnesNextY[i] = eneNextY;

				break;
			}
		}
	}
	else {
		mEnesNext[eneIdx] = eneNext;

		mEnesNextX[eneIdx] = eneNextX;
		mEnesNextY[eneIdx] = eneNextY;
	}
	
}


void EnemyMgr::GetEneData(std::vector<std::map<std::string, int>>* eneIntDataMaps,
	std::vector<std::vector<std::map<std::string, int>>>* eneAXYMapVecs,
	std::vector<std::map<std::string, bool>>* eneBoolDataMaps, bool* isExistings) {
	// �eEnemy�̏���n��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->GetEneDataMap(&(*eneIntDataMaps).at(i), &(*eneAXYMapVecs).at(i), 
				&(*eneBoolDataMaps).at(i));
			isExistings[i] = true;
		}
		else {
			//iteDataMap1 = NULL;
			isExistings[i] = false;
		}
	}

}


void EnemyMgr::SetIsHits(const bool* const isHits) {
	// �eEnemy��Player�̍U���Ƃ̓����蔻�茋�ʂ�n��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->SetIsHit(isHits[i]);
		}
	}
}


void EnemyMgr::SetPlDataMap(std::map<std::string, int>* plDataMap) {
	// �eEnemy��Player�̍U���͂�n��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->SetPlParams(plDataMap);
		}
	}

	// CreateEnemy�Ŏg��Player��x���W�����Ă���
	mPlX = (*plDataMap)["x"];
}


void EnemyMgr::CreateEnemy() {
	// mEnemies�̒���Enemy���Z�b�g����Ă��鐔�𐔂���
	int existingEneNum = 0;
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			existingEneNum++;
		}
	}

	// Enemy�̐����m���i0�`10000, 10000��100%�j�����߂�
	// Enemy���Z�b�g����Ă���΂���قǐ����m����������
	int creationProb = 4000 * std::pow(0.1, existingEneNum);

	// 1�`10000�̃����_���Ȑ��l�𐶐�
	std::random_device rnd;
	int randNum = rnd() % 10000 + 1;

	// Enemy�𐶐��i10000 - creationProb�̊m����Enemy�͐�������Ȃ��j
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!mEnemies[i]) {
			if (randNum >= 10000 - creationProb) {	// Enemy�𐶐�����Ƃ�
				// ����Enemy��y���W�����߂Ă���
				mEnesNextY[i] = rnd() % (ENEMY_FIRST_Y_MAX - ENEMY_FIRST_Y_MIN) + ENEMY_FIRST_Y_MIN;

				// randNum��1�`creationProb�͈̔͂ɂ����̂��C1�`100�͈̔͂̒l�ɐ��K������
				randNum = 10000 - randNum + 1;
				randNum = (randNum / (float)creationProb) * 100;

				if (randNum <= 50) {	// 50%�̊m����
					// �C�m�V�V�̓G
					// x���W�����߂Ă���
					mEnesNextX[i] = 1400;

					if (randNum <= 30) {	// 30%�̊m����
						// Enemy1
						mEnesNext[i] = eEnemy1;
					}
					else if (randNum <= 40) {	// 10%�̊m����
						// Enemy2
						mEnesNext[i] = eEnemy2;
					}
					else {	// 10%�̊m����
						// Enemy3
						mEnesNext[i] = eEnemy3;
					}
				}
				else if (randNum <= 90) {	// 40%�̊m����
					// ���@�g��
					// x���W�����߂Ă���(Player���痣�ꂽ�ʒu�ɏo��������)
					if (mPlX > 600) {	// Player���E���ɂ�����
						mEnesNextX[i] = rand() % (150 + 1) + 80;
					}
					else {	// Player�������ɂ�����
						mEnesNextX[i] = rand() % (150 + 1) + 1000;
					}

					if (randNum <= 70) {	// 20%�̊m����
						// Enemy4
						mEnesNext[i] = eEnemy4;
					}
					else if (randNum <= 80) {	// 10%�̊m����
						// Enemy5
						mEnesNext[i] = eEnemy5;
					}
					else {	// 10%�̊m����
						// Enemy6
						mEnesNext[i] = eEnemy6;
					}
				}
				else {	// 10%�̊m����
					// ���g���iEnemy7�j
					// x���W�����߂Ă���(Player���痣�ꂽ�ʒu�ɏo��������)
					if (mPlX > 600) {	// Player���E���ɂ�����
						mEnesNextX[i] = rand() % (150 + 1) + 80;
					}
					else {	// Player�������ɂ�����
						mEnesNextX[i] = rand() % (150 + 1) + 1000;
					}
					
					mEnesNext[i] = eEnemy7;
				}

				break;
			}
		}
	}
}


void EnemyMgr::CreateEnemyBoss(const int bossBackX) {
	mEnesNext[0] = eEnemyBoss;
	mEnesNextX[0] = bossBackX + 1160;
	mEnesNextY[0] = 400;
}