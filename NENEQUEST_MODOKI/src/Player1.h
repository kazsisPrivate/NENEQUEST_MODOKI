#pragma once

#include "Player.h"
#include "UpdateKey.h"

class Player1 : public UpdateKey, Player {
public:
	Player1(PlayerChanger* changer);
	~Player1();
	static Player1* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;

private:
	static Player1* mPlayer1;
};