#include "DxLib.h"
#include "Enemy.h"
#include "Enemy1.h"	// ここからイノシシ系
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"	// ここから魔術師系
#include "Enemy5.h"
#include "Enemy6.h"
//#include "Enemy7.h"	// ここからその他
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
	// Enemyが何もセットされていない状態に初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEnemies[i] = NULL;
		mEnesNext[i] = eEnemy1;	// デバッグ用に入れいている

		mEnesNextX[i] = 1200;//1300 + 500 * i;
		mEnesNextY[i] = 300 + 150 * i;
	}
	mEnesNext[0] = eEnemy4;	// デバッグ用に入れいている
	mEnesNext[1] = eEnemy5;	// デバッグ用に入れいている
	mEnesNext[2] = eEnemy6;	// デバッグ用に入れいている
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
		if (mEnesNext[i] != eEnemyNone) {	// 次のEnemyがセットされているとき
			if (mEnemies[i]) {	// mEnemies[i]の中がNULLでないとき
				// 終了処理をする
				mEnemies[i]->Finalize();
				delete mEnemies[i];
			}

			// 次のEnemyに変更する
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

	// 各Enemyの更新処理をする
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->Update();
		}
	}
}


//void EnemyMgr::Draw() {
//	// 各Enemyの描画
//	for (int i = 0; i < ENEMY_NUM; i++) {
//		if (mEnemies[i]) {	// NULLが入っていなければ
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
	// 各Enemyの情報を渡す
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
	// 各EnemyにPlayerの攻撃との当たり判定結果を渡す
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->SetIsHit(isHits[i]);
		}
	}
}


void EnemyMgr::SetPlDataMap(std::map<std::string, int>* plDataMap) {
	// 各EnemyにPlayerの攻撃力を渡す
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			mEnemies[i]->SetPlParams(plDataMap);
		}
	}
}