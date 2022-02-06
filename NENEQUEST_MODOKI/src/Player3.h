#pragma once

// ���i�U���́F���ʁC�U���͈́F�����C�U���������ԁF���������i���̍U���܂łɂ����鎞�ԁF���������j�C������Փx�F�����ȒP�j

#include "Player.h"


class Player3 : public Player {
public:
	Player3(PlayerChanger* changer);
	~Player3();
	static Player3* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

protected:
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;

private:
	static Player3* mPlayer3;
};