#pragma once

#include "EnemyChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>
#include <vector>


class Enemy;


class EnemyMgr : public EnemyChanger, BasicFunc {
public:
	static EnemyMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {};
	void Draw(const int eneIdx);	// 指定されたインデックス番号のmEnemyを描画
	void ChangeEnemy(const int eneIdx, EEnemy eneNext,
		const int eneNextX, const int eneNextY) override;	// eneIdxは配列mEnemyのインデックス番号を指す
	void GetEneData(std::vector<std::map<std::string, int>>* eneIntDataMaps, 
		std::vector<std::vector<std::map<std::string, int>>>* eneAXYMapVecs,
		std::vector<std::map<std::string, bool>>* eneBoolDataMaps, bool* isExistings);	// Enemyのデータを渡すために使用する
																									// isExistingsはmEnemiesの各インデックス番号においてNULLでなければtrue
	void SetIsHits(const bool* const isHits);	// Playerの攻撃との当たり判定の確認結果のMapを受け取る
	void SetPlDataMap(std::map<std::string, int>* plDataMap);	// Playerのx, y, 攻撃力を受け取る
	void CreateEnemy();	// 一定の確率でEnemyを出現させる，Enemyの自動生成のために使用し，GameSceneから一定の周期で利用する
	//bool GetBossDead() const; //Bossの体力が0になったらtrue

private:
	const int ENEMY_NUM = 3;	// 管理できるenemyの数，mEnemiesの要素数
	Enemy* mEnemies[3];
	EEnemy mEnesNext[3];	// 各mEnemiesに次にセットするitemの種類
	int mEnesNextX[3];	// 次にセットするenemyの最初のx座標
	int mEnesNextY[3];	// 次にセットするenemyの最初のy座標
	const int ITEM_FIRST_Y_MIN = 290;	// enemyが生成された際の最初のy座標の最小値
	const int ITEM_FIRST_Y_MAX = 610;	// enemyが生成された際の最初のy座標の最大値
	int mPlX;	// Playerのx座標，新しいEnemyの出現の座標の決定で使用する

private:
	static EnemyMgr* mEnemyMgr;
};