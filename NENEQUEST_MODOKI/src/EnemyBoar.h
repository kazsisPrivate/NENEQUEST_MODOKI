#pragma once

// �C�m�V�V�̓G�iEnemy1�`3�j�̌��Ƃ���N���X
#include "Enemy.h"


class EnemyBoar : public Enemy {
public:
	EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;
	//virtual void Draw() override;	// Enemy3�ȊO�͂���g��
	/*virtual void GetEneDataMap(std::map<std::string, float>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;*/	// Player�̍U���Ƃ̓����蔻��Ȃǂ̏��̎擾�Ɏg�p����CEnemy3�ȊO�͂���g��

protected:
	virtual void Walk() override;
};

