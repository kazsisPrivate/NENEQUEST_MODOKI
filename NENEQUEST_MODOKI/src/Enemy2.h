#pragma once
/*
* �C�m�V�V2�ihp2�j
*/
#include "EnemyBoar.h"

class Enemy2 : public EnemyBoar {
public:
	Enemy2(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};