#pragma once

// ���@�g��1�ihp1, �Ԃ��΂̋ʁj
#include "EnemyMage.h"

class Enemy4 : public EnemyMage {
public:
	Enemy4(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
};