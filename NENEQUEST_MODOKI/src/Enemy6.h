#pragma once

// ���@�g��3�ihp1, ���΂̋ʁC�U����2�j
#include "EnemyMage.h"

class Enemy6 : public EnemyMage {
public:
	Enemy6(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};