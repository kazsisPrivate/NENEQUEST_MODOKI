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
		const int eneNextX, const int eneNextY) = 0;	// 指定したインデックス番号のEnemy変数に次にセットするようにする(座標も指定)
};
