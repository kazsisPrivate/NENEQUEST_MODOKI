#pragma once
/*
* 斧（攻撃力：普通，攻撃範囲：狭い，攻撃持続時間：少し長い（次の攻撃までにかかる時間：少し長い），移動速度：普通）
*/
#include "Player.h"


class Player3 : public Player {
public:
	Player3(PlayerChanger* changer);
	static Player3* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;

private:
	void Walk() override;
	void Jump() override;
	void StartBossStage() override;

private:
	static Player3* mPlayer3;
};