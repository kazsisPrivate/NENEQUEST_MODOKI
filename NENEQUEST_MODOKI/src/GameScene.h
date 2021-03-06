#pragma once
/*
* ゲームプレイ画面（GameScene）のクラス
*/
#include "BaseScene.h"
#include "SceneChanger.h"
#include "GameBack.h"
#include "PlayerMgr.h"
#include "EnemyMgr.h"
#include "ItemMgr.h"
#include "PlayerHpGauge.h"
#include "TimeCounter.h"
#include "ScoreCounter.h"
#include "GameOver.h"
#include "GameClear.h"
#include <memory>
#include <string>
#include <map>
#include <vector>


class GameScene : public BaseScene {
public:
	GameScene(SceneChanger* changer);
	static GameScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	void UpdateDOrder(); // Player, Enemy, Itemの描画順（drawing order）を更新する
	void UpdateHit();	// Player, Enemy, Item間の当たり判定の更新を行う
	void UpdateScore();	// EnemyとItemのisDeadをもとに，スコアを追加する
	bool IsHit(const int (&ps1)[4], const int (&ps2)[4]);	// それぞれのターゲットの位置の配列を渡して，当たり判定を確認し，当たっていたらtrueを返す

	GameBack* mGameBack;
	PlayerMgr* mPlayerMgr;
	EnemyMgr* mEnemyMgr;
	ItemMgr* mItemMgr;
	PlayerHpGauge* mPlHpGauge;
	TimeCounter* mTimeCounter;
	ScoreCounter* mScoreCounter;
	GameOver* mGameOver;
	GameClear* mGameClear;

	std::vector<std::pair<int, std::pair<int, int>>> mDOrderVec;	// 描画するオブジェクトの種類を示すpairを描画順に入れるvector
														// firstにy座標，secondに物体の種類とインデックス番号を入れたpairのvector
														// キャラの種類（0: Player, 1: Enemy, 2: Item）
	int mSoundHandle;	// 音源

	unsigned long long mFrameCnt;	// フレーム数のカウント，EnemyやItemの出現，Bossへの突入の管理のために使用する
	const int ENE_CREATION_FRAME_NUM = 120;	// このフレーム毎にEnemyを出現させるかどうかを決める
	const int ITE_CREATION_FRAME_NUM = 60;	// このフレーム毎にItemを出現させるかどうかを決める
	const unsigned long long BOSS_START_FRAME_NUM = 9000;	// このフレーム数を超えたら，ボスステージに入る準備を始める(9000フレーム=約2分30秒)

	const int ITEM_NUM = 2;	// 管理できるitemの数
	const int ENEMY_NUM = 3;	// 管理できるEnemyの数
	const int ENEMY_ATTACK_NUM = 5;	// 管理できるEnemyの攻撃の数
	
	std::map<std::string, int> mPlIntDataMap;	// Playerのx, y, hp, hitRangeW, hitRangeH, hitRangeAW, hitRangeAH, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectIdなどを入れているmap
	std::map<std::string, bool> mPlBoolDataMap;	// PlayerのisDead, isAttackingなどを入れているmap
	
	std::vector<std::map<std::string, int>> mEneIntDataMaps;	// 各Enemyのx, y, hitRangeW, hitRangeHなどを入れているmapのvector
	std::vector<std::vector<std::map<std::string, int>>> mEneAXYMapVecs;	// 各Enemyの各攻撃（複数の火の玉など）のax, ay, hitRangeAW, hitRangeAHを入れているmapのvectorのvector
	std::vector<std::map<std::string, bool>> mEneBoolDataMaps;	// EnemyのisAttackingなどを入れているmap
	bool mEneIsExistings[3];	// 各Enemyが存在しているかどうか（NULLであるかないか），存在していればtrue

	std::vector<std::map<std::string, float>> mIteIntDataMaps;	// 各Itemのx, y, hitRangeW, hitRangeH, healPower, speedPower, attackPowerなどを入れているmapのvector
	std::vector<std::map<std::string, float>> mIteBoolDataMaps;	// 各ItemのisDeadなどを入れているvector
	bool mIteIsExistings[2];	// 各Itemが存在しているかどうか（NULLであるかないか），存在していればtrue

	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Playerの当たり判定の情報を入れたmap, キーは対称の物体の種類（item, enemy, enemyAttack, plAToItem, plAToEnemy）, PlayerMgrに渡す
															// plAToItemとplAToEnemyはPlayerの攻撃が当たっていたらtrueで返す
	bool mEneIsHits[3];	// 各Enemyにおける，Playerの攻撃との当たり判定を入れた配列
	std::vector<std::map<std::string, bool>> mIteIsHitMaps;	// 各Itemの当たり判定の情報を入れたmap, キーは対称の物体の種類（player, playerAttack）, ItemMgrに渡す

	bool mPlIsDead;	// Playerが死んでいたら（PlayerのmIsDeadがtrueになっていたら）true, GameOver画面への移行に使う
	bool mIsChangingSt;	// BossStageへ変更中であったらtrue
	bool mIsAtBsSt;	// BossStageにいたらtrue
	bool mHasClearedGame;	// Bossを倒したらtrue

private:
	static GameScene* mGameScene;
};