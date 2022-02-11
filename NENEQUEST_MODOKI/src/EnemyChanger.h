#pragma once


typedef enum {
	eEnemy1,
	eEnemy2,
	eEnemy3,
	eEnemy4,
	eEnemy5,
	eEnemy6,
	eEnemy7,
	eEnemyBoss,
	eEnemyNULL,
	eEnemyNone
} EEnemy;

class EnemyChanger {
public:
	virtual void ChangeEnemy(const int eneIdx, EEnemy eneNext,
		const int eneNextX, const int eneNextY) = 0;	// �w�肵���C���f�b�N�X�ԍ���Enemy�ϐ��Ɏ��ɃZ�b�g����悤�ɂ���(���W���w��)
};
