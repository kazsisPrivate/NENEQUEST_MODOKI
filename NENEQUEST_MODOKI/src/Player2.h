#pragma once

// ��2�i�U���́F�����C�U���͈́F���ʁC�U���������ԁF���ʁi���̍U���܂łɂ����鎞�ԁF���ʁj�C������Փx�F��������j

#include "Player.h"


class Player2 : public Player {
public:
	Player2(PlayerChanger* changer);
	static Player2* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	//void Draw() override;

protected:
	//void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	//void Attack() override;

private:
	static Player2* mPlayer2;
};