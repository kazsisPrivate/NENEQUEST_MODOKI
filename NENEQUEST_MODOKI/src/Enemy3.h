#pragma once
/*
* イノシシ3（hp1, 角突き出し攻撃あり）
*/
#include "EnemyBoar.h"

class Enemy3 : public EnemyBoar {
public:
	Enemy3(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemyのデータを渡すために使用する

private:
	void Attack();	// 角攻撃

	int mAX, mAY;	// 角攻撃のxy座標
	int mHitRangeAW, mHitRangeAH;	// 角攻撃の範囲
};