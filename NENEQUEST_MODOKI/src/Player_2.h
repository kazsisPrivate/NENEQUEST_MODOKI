#pragma once

#include "Player.h"
#include "UpdateKey.h"

class Player_2 : public UpdateKey, Player {
public:
	Player_2(PlayerChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Speed() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;

private:
	//int charaHandle[24];
};