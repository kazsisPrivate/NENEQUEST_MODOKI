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

	// ���̑�
	mExistingFrameCnt = 0;
	mIsBoss = false;
}


void EnemyBoar::Walk() {
	mX -= (int)mSpeed;

	// �t���[�����ɍ��킹�ĕ\���摜��ω�������
	int ix = mExistingFrameCnt % 20 / 10;	// 10�t���[�����ɉ摜���

	mHandleId = ix;
}