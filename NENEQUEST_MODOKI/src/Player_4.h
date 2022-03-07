#pragma once

#include "Player.h"
#include "UpdateKey.h"
#include "Arrow.h"

class Player_4 : public UpdateKey, Player {
public:
	Player_4(PlayerChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Speed() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void PreAttackS(); //弓矢をひいてはいるがまだ矢を放っていない状態のとき
	void PreAttackD();
	void HitJudge() override; //Player_4においてのみ攻撃の当たり判定の取り方が異なるため
	void BossStart() override;

private:
	Arrow* arrow;
	//int charaHandle[32];
	bool preAttackFlagS; //矢を放つ前の状態であるとき（キーから指を離せば矢を放てる状態のとき）true
	bool preAttackFlagD;
};