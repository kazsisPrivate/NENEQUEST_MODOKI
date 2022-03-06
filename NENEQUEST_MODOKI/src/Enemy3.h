#pragma once
/*
* ƒCƒmƒVƒV3ihp1, Šp“Ë‚«o‚µUŒ‚‚ ‚èj
*/
#include "EnemyBoar.h"

class Enemy3 : public EnemyBoar {
public:
	Enemy3(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemy‚Ìƒf[ƒ^‚ğ“n‚·‚½‚ß‚Ég—p‚·‚é

private:
	void Attack();	// ŠpUŒ‚

	int mAX, mAY;	// ŠpUŒ‚‚ÌxyÀ•W
	int mHitRangeAW, mHitRangeAH;	// ŠpUŒ‚‚Ì”ÍˆÍ
};