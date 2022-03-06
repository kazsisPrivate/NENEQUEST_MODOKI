#pragma once
/*
* �C�m�V�V�̓G�iEnemy1�`3�j�̊��N���X
*/
#include "Enemy.h"


class EnemyBoar : public Enemy {
public:
	EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;

protected:
	virtual void Walk() override;

	const int ENE_BOAR_DELETE_X = -150;	// ���̍��W�܂�EnemyBoar���ړ������Ƃ��C�����I�ɏ����悤�ɂ���
	int mExistingFrameCnt;	// �I�u�W�F�N�g����������Ă���̃t���[�����C�摜�̍X�V�Ɏg�p����
};

