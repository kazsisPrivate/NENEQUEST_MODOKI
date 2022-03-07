#pragma once
/*
* ��1�i�U���́F���ʁC�U���͈́F�����L���C�U���������ԁF���ʁi���̍U���܂łɂ����鎞�ԁF���ʁj�C�ړ����x�F���ʁj
*/
#include "Player.h"


class Player1 : public Player {
public:
	Player1(PlayerChanger* changer);
	static Player1* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;

private:
	void Walk() override;
	void Jump() override;
	void StartBossStage() override;

private:
	static Player1* mPlayer1;
};