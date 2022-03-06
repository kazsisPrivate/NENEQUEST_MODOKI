#pragma once
/*
* 剣1（攻撃力：普通，攻撃範囲：少し広い，攻撃持続時間：普通（次の攻撃までにかかる時間：普通），移動速度：普通）
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