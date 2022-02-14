#pragma once

// 魔法使い2（hp2, 赤い火の玉, 攻撃回数1）
#include "EnemyMage.h"

class Enemy5 : public EnemyMage {
public:
	Enemy5(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};