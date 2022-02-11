#pragma once

// イノシシの敵（Enemy1～3）の元とするクラス
#include "Enemy.h"


class EnemyBoar : public Enemy {
public:
	EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;
	//virtual void Draw() override;	// Enemy3以外はこれ使う
	/*virtual void GetEneDataMap(std::map<std::string, float>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;*/	// Playerの攻撃との当たり判定などの情報の取得に使用する，Enemy3以外はこれ使う

protected:
	virtual void Walk() override;
};

