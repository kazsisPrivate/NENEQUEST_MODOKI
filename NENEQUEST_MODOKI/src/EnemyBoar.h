#pragma once
/*
* イノシシの敵（Enemy1～3）の基底クラス
*/
#include "Enemy.h"


class EnemyBoar : public Enemy {
public:
	EnemyBoar(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;

protected:
	virtual void Walk() override;

	const int ENE_BOAR_DELETE_X = -150;	// この座標までEnemyBoarが移動したとき，自動的に消すようにする
	int mExistingFrameCnt;	// オブジェクトが生成されてからのフレーム数，画像の更新に使用する
};

