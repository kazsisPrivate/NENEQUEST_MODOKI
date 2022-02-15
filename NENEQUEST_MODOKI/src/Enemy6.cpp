// ���@�g��3�ihp1, ���΂̋�, �U����2��j
#include "Enemy6.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy6::Enemy6(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 6), itemIdx, x, y) {
}


void Enemy6::Initialize() {
	EnemyMage::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 225, mImgH = 190;

	// �U����̗͂̐ݒ�
	mHp = 1;
	mAttack = 1;	// �΂̋ʂ̍U����

	// �΂̋ʂ̃^�C�v�̐ݒ�
	mFireType = 2;	// ���΂̋�

	// ����񐔂̐ݒ�
	mDeleteRoDoneNum = 3;

	// �|�����瓾����X�R�A�̐ݒ�
	mScore = 1000;
}