#pragma once

// 剣2（攻撃力：高い，攻撃範囲：普通，攻撃持続時間：普通（次の攻撃までにかかる時間：普通），扱い難易度：少し難しい）

#include "Player.h"


class Player2 : public Player {
public:
	Player2(PlayerChanger* changer);
	static Player2* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;

protected:
	void Walk() override;
	void Jump() override;
	void StartBossStage() override;

private:
	static Player2* mPlayer2;
};