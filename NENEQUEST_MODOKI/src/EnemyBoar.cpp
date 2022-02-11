// Enemy1�`3�̃C�m�V�V�̓G�̊��N���X
#include "EnemyBoar.h"
#include "DxLib.h"


EnemyBoar::EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y)
	: Enemy(changer, graph, eneIdx, x, y) {
}


void EnemyBoar::Initialize() {
	Enemy::Initialize();

	// �����蔻��֘A�̐ݒ�
	mHitRangeW = 70, mHitRangeH = 35;

	// �ړ����x��U���͂̐ݒ�
	mSpeed = 20.0f;
	mAttack = 1;
}


void EnemyBoar::Walk() {
	mX -= (int)mSpeed;

	// x���W�ɍ��킹�ĕ\���摜��ω�������
	int ix = (mX + 1000) % 20 / 10;

	mHandleId = ix;
}