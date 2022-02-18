#pragma once

// 弓（攻撃力：普通，攻撃範囲：広い，攻撃持続時間：長い（次の攻撃までにかかる時間：長い），扱い難易度：難しい）

#include "Player.h"
#include "Arrow.h"

class Player4 : public Player {
public:
	Player4(PlayerChanger* changer);
	static Player4* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) override;	// 弓矢が動いている間のみ当たり判定のある攻撃中とみなすために，
																														// Player自身の攻撃中ではなく，Arrowの方の情報を利用する必要があるため

protected:
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void StartBossStage() override;

private:
	void PrepareWAttack();	// 弱い攻撃（弓矢が遠くまで飛ぶ，入力Sキー）の準備処理（弓矢を構えて放つまでの間の処理）
	void PrepareSAttack();	// 強い攻撃（弓矢が遠くまで飛ぶ，入力Sキー）の準備処理（弓矢を構えて放つまでの間の処理）
	void UpdateArrowIsHit();	// 弓矢の攻撃が当たったかどうかの当たり判定関連の更新処理を行う

	static Player4* mPlayer4;
	Arrow* mArrow;
	bool mArrowExists;	// 弓矢が画面上にある間（攻撃効果が続いている間）はtrue
	bool mIsPreparingWA;	// 弱い弓矢を放つ前の状態であるとき（キーから指を離せば弓矢を放てる状態のとき）にtrue
	bool mIsPreparingSA;	// 強い弓矢を放つ前の状態であるとき（キーから指を離せば弓矢を放てる状態のとき）にtrue
	bool mArrowIsHit;	// 弓矢が何かに当たればtrue
};