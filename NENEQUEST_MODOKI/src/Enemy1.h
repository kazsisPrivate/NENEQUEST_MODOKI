#pragma once

// �C�m�V�V1�ihp1�j
#include "EnemyBoar.h"

class Enemy1 : public EnemyBoar {
public:
	Enemy1(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	//void Walk() override;
};