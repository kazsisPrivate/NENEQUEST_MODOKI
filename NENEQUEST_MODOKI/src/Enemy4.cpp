// ���@�g��1�ihp1, �Ԃ��΂̋�, �U����1��j
#include "Enemy4.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy4::Enemy4(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyMage(changer, CharaGraphics::GetGraHandle(1, 4), itemIdx, x, y) {
}


void Enemy4::Initialize() {
	EnemyMage::Initialize();

	// �����蔻��֘A�̐ݒ�
	mImgW = 225, mImgH = 192;

	// �U����̗͂̐ݒ�
	mHp = 1;
	mAttack = 1;	// �΂̋ʂ̍U����

	// �΂̋ʂ̃^�C�v�̐ݒ�
	mFireType = 1;	// �Ԃ��΂̋�

	// ����񐔂̐ݒ�
	mDeleteRoDoneNum = 2;

	// �|�����瓾����X�R�A�̐ݒ�
	mScore = 600;
}