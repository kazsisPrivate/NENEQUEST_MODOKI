#pragma once

#include "PlayerChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>
#include <vector>


class Player;
//class GameScene;


class PlayerMgr : public PlayerChanger, BasicFunc {
public:
	PlayerMgr();
	static PlayerMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangePlayer(EPlayer playerNext) override;
	void GetPlData(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerの情報を取得するために使用する，GameSceneに渡す
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);
	void SetIsHitMap(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttackとの当たり判定の確認結果のMapを受け取る
	void SetIteDataMaps(std::vector<std::map<std::string, float>>& iteDataMaps);	// Itemの効果の情報を受け取る，Player側でのItemの効果の把握のために使用する
	void SetEneAPowers(const int* const eneAPs);	// 各Enemyの攻撃力を受け取る，Player側でのEnemyの攻撃力の把握のために使用する
	void SetIsChangingSt(const bool isChangingSt);	// BossStageへ変化させているかどうかをセットする，PlayerをBossStage前の強制移動のために利用し，GameScene側からセットする
	void SetIsAtBsSt(const bool isAtBsSt);	// BossStageにいるかどうかをセットする，PlayerをBossStageの挙動にするために利用し，GameScene側からセットする

private:
	Player* mPlayer;
	EPlayer mPlayerNext;
	//GameScene* mGameScene;
	int mEneAPs[3];	// 各Enemyの攻撃力を入れた配列
	std::vector<std::map<std::string, float>> mIteDataMaps;	// 各ItemのhealPower, speedPower, attackPowerなどを入れているmap, Playerに渡す
	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Playerの当たり判定の情報を入れたmap
															// キーは対称の物体の種類（item, enemy, enemyAttack, plAToEnemy, plAToItem）, PlayerMgrに渡す
	const int ENEMY_NUM = 3;	// セットできるEnemyの数
	const int ITEM_NUM = 2;	// セットできるitemの数
	//bool mIsChangingSt;	// BossStageへ変化させているときはtrueになる

private:
	static PlayerMgr* mPlayerMgr;
};