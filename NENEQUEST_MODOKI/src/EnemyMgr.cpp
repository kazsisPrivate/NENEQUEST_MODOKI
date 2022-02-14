#include "DxLib.h"
#include "Enemy.h"
#include "Enemy1.h"	// ��������C�m�V�V�n
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"	// �������疂�p�t�n
#include "Enemy5.h"
#include "Enemy6.h"
//#include "Enemy7.h"	// �������炻�̑�
//#include "EnemyBoss.h"
#include "EnemyMgr.h"


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
		mEnesNext[i] = eEnemy1;	// �f�o�b�O�p�ɓ��ꂢ�Ă���

		mEnesNextX[i] = 1200;//1300 + 500 * i;
		mEnesNextY[i] = 300 + 150 * i;
	}
	mEnesNext[0] = eEnemy4;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
	mEnesNext[1] = eEnemy5;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
	mEnesNext[2] = eEnemy6;	// �f�o�b�O�p�ɓ��ꂢ�Ă���
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
			/*case eEnemy7:
				mEnemies[i] = (Enemy*) new Enemy7(this, i, mEnesNextX[i], mEnesNextY[i]);
				break;*/
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


//void EnemyMgr::Draw() {
//	// �eEnemy�̕`��
//	for (int i = 0; i < ENEMY_NUM; i++) {
//		if (mEnemies[i]) {	// NULL�������Ă��Ȃ����
//			mEnemies[i]->Draw();
//		}
//	}
//}


void EnemyMgr::Draw(const int eneIdx) {
	if (mEnemies[eneIdx]) {
		mEnemies[eneIdx]->Draw();
	}
}


void EnemyMgr::ChangeEnemy(const int eneIdx, EEnemy eneNext, const int eneNextX, const int eneNextY) {
	mEnesNext[eneIdx] = eneNext;

	mEnesNextX[eneIdx] = eneNextX;
	mEnesNextY[eneIdx] = eneNextY;
}


void EnemyMgr::GetEneData(std::vector<std::map<std::string, int>>* eneIntDataMaps,
	std::vector<std::vector<std::map<std::string, int>>>* eneAXYMapVecs,
	std::vector<std::map<std::string, bool>>* eneBoolDataMaps, bool* isExistings) {
	// �eEnemy�̏���n��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnesNext[i] == eEnemyNone && mEnemies[i]) {
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
}