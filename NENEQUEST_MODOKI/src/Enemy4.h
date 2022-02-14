#pragma once

// 魔法使い1（hp1, 赤い火の玉）
#include "EnemyMage.h"

class Enemy4 : public EnemyMage {
public:
	Enemy4(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};