#pragma once
/*
* �C�m�V�V3�ihp1, �p�˂��o���U������j
*/
#include "EnemyBoar.h"

class Enemy3 : public EnemyBoar {
public:
	Enemy3(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemy�̃f�[�^��n�����߂Ɏg�p����

private:
	void Attack();	// �p�U��

	int mAX, mAY;	// �p�U����xy���W
	int mHitRangeAW, mHitRangeAH;	// �p�U���͈̔�
};