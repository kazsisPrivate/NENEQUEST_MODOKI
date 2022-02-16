#include "DxLib.h"
#include "Enemy.h"
#include "Enemy1.h"	// ここからイノシシ系
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"	// ここから魔術師系
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"	// ここからその他
//#include "EnemyBoss.h"
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
	// Enemyが何もセットされていない状態に初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEnemies[i] = NULL;
		mEnesNext[i] = eEnemy1;	// デバッグ用に入れいている

		mEnesNextX[i] = 100;//1200;//1300 + 500 * i;
		mEnesNextY[i] = 300 + 150 * i;
	}
	mEnesNext[0] = eEnemyNone;	// デバッグ用に入れいている
	mEnesNext[1] = eEnemyNone;	// デバッグ用に入れいている
	mEnesNext[2] = eEnemyNone;	// デバッグ用に入れいている

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
			case eEnemy7:
				mEnemies[i] = (Enemy*) new Enemy7(this, i, mEnesNextX[i], mEnesNextY[i]);
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

	// 各Enemyの更新処理をする
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
	mEnesNext[eneIdx] = eneNext;

	mEnesNextX[eneIdx] = eneNextX;
	mEnesNextY[eneIdx] = eneNextY;
}


void EnemyMgr::GetEneData(std::vector<std::map<std::string, int>>* eneIntDataMaps,
	std::vector<std::vector<std::map<std::string, int>>>* eneAXYMapVecs,
	std::vector<std::map<std::string, bool>>* eneBoolDataMaps, bool* isExistings) {
	// 各Enemyの情報を渡す
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

	// CreateEnemyで使うPlayerのx座標を入れておく
	mPlX = (*plDataMap)["x"];
}


void EnemyMgr::CreateEnemy() {
	// mEnemiesの中にEnemyがセットされている数を数える
	int existingEneNum = 0;
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEnemies[i]) {
			existingEneNum++;
		}
	}

	// Enemyの生成確率（0〜10000, 10000で100%）を求める
	// Enemyがセットされていればいるほど生成確立が下がる
	int creationProb = 2000 * std::pow(0.3, existingEneNum);

	// 1〜10000のランダムな数値を生成
	std::random_device rnd;
	int randNum = rnd() % 10000 + 1;

	// Enemyを生成（10000 - creationProbの確率でEnemyは生成されない）
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!mEnemies[i]) {
			if (randNum >= 10000 - creationProb) {	// Enemyを生成するとき
				// 次のEnemyのy座標を決めておく
				mEnesNextY[i] = rnd() % (ITEM_FIRST_Y_MAX - ITEM_FIRST_Y_MIN) + ITEM_FIRST_Y_MIN;

				// randNumを1〜creationProbの範囲にしたのち，1〜100の範囲の値に正規化する
				randNum = 10000 - randNum + 1;
				randNum = (randNum / (float)creationProb) * 100;

				if (randNum <= 50) {	// 50%の確率で
					// イノシシの敵
					// x座標を決めておく
					mEnesNextX[i] = 1400;

					if (randNum <= 30) {	// 30%の確率で
						// Enemy1
						mEnesNext[i] = eEnemy1;
					}
					else if (randNum <= 40) {	// 10%の確率で
						// Enemy2
						mEnesNext[i] = eEnemy2;
					}
					else {	// 10%の確率で
						// Enemy3
						mEnesNext[i] = eEnemy3;
					}
				}
				else if (randNum <= 90) {	// 40%の確率で
					// 魔法使い
					// x座標を決めておく(Playerから離れた位置に出現させる)
					if (mPlX > 600) {	// Playerが右側にいたら
						mEnesNextX[i] = rand() % (150 + 1) + 80;
					}
					else {	// Playerが左側にいたら
						mEnesNextX[i] = rand() % (150 + 1) + 1000;
					}

					if (randNum <= 70) {	// 20%の確率で
						// Enemy4
						mEnesNext[i] = eEnemy4;
					}
					else if (randNum <= 80) {	// 10%の確率で
						// Enemy5
						mEnesNext[i] = eEnemy5;
					}
					else {	// 10%の確率で
						// Enemy6
						mEnesNext[i] = eEnemy6;
					}
				}
				else {	// 10%の確率で
					// 鎌使い（Enemy7）
					// x座標を決めておく(Playerから離れた位置に出現させる)
					if (mPlX > 600) {	// Playerが右側にいたら
						mEnesNextX[i] = rand() % (150 + 1) + 80;
					}
					else {	// Playerが左側にいたら
						mEnesNextX[i] = rand() % (150 + 1) + 1000;
					}
					
					mEnesNext[i] = eEnemy7;
				}

				break;
			}
		}
	}
}
