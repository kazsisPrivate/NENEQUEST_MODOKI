#pragma once

// ���@�g��2�ihp2, �Ԃ��΂̋�, �U����1�j
#include "EnemyMage.h"

class Enemy5 : public EnemyMage {
public:
	Enemy5(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};