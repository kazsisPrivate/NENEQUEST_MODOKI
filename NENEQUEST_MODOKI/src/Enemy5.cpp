// ���@�g��2�ihp2, �Ԃ��΂̋�, �U����1��j
#include "Enemy5.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy5::Enemy5(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 5), itemIdx, x, y) {
}


void Enemy5::Initialize() {
	EnemyMage::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 225, mImgH = 192;

	// �U����̗͂̐ݒ�
	mHp = 2;
	mAttack = 1;	// �΂̋ʂ̍U����

	// �΂̋ʂ̃^�C�v�̐ݒ�
	mFireType = 1;	// �Ԃ��΂̋�

	// ����񐔂̐ݒ�
	mDeleteRoDoneNum = 2;

	// �|�����瓾����X�R�A�̐ݒ�
	mScore = 1000;
}