#pragma once

// 弓（攻撃力：普通，攻撃範囲：広い，攻撃持続時間：長い（次の攻撃までにかかる時間：長い），扱い難易度：難しい）

#include "Player.h"
#include "Arrow.h"

class Player4 : public Player {
public:
	Player4(PlayerChanger* changer);
	~Player4();
	static Player4* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

protected:
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void UpdateHit() override; //Player_4においてのみ攻撃の当たり判定の取り方が異なるため
	void StartBossStage() override;

private:
	void PrepareWAttack();	// 弱い攻撃（弓矢が遠くまで飛ぶ，入力Sキー）の準備処理（弓矢を構えて放つまでの間の処理）
	void PrepareSAttack();	// 強い攻撃（弓矢が遠くまで飛ぶ，入力Sキー）の準備処理（弓矢を構えて放つまでの間の処理）

	static Player4* mPlayer4;
	Arrow* mArrow;
	bool mArrowExists;	// 弓矢が画面上にある間（攻撃効果が続いている間）はtrue
	bool mIsPreparingWA;	// 弱い弓矢を放つ前の状態であるとき（キーから指を離せば弓矢を放てる状態のとき）にtrue
	bool mIsPreparingSA;	// 強い弓矢を放つ前の状態であるとき（キーから指を離せば弓矢を放てる状態のとき）にtrue
};