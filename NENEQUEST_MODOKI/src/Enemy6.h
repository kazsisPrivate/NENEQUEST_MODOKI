#pragma once

// 魔法使い3（hp1, 青い火の玉，攻撃回数2）
#include "EnemyMage.h"

class Enemy6 : public EnemyMage {
public:
	Enemy6(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};