#pragma once

#include "PlayerChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>
#include <vector>


class Player;
class GameScene;


class PlayerMgr : public PlayerChanger, BasicFunc {
public:
	PlayerMgr();
	static PlayerMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangePlayer(EPlayer playerNext) override;
	void GetPlDataMaps(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerの情報を取得するために使用する，GameSceneに渡す
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);
	void SetIsHitMap(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttackとの当たり判定の確認結果のMapを受け取る
	void SetIteDataMaps(std::vector<std::map<std::string, float>>& iteDataMaps);	// Itemの効果の情報を受け取る，Player側でのItemの効果の把握のために使用する
	//bool GetDead(); //playerのhpが0かどうかを得る　GameOverの画面に移行するのに使う　Game.cppにて使用している
	
	
	

private:
	Player* mPlayer;
	EPlayer mPlayerNext;
	GameScene* mGameScene;
	std::vector<std::map<std::string, float>> mIteDataMaps;	// 各ItemのhealPower, speedPower, attackPowerなどを入れているmap, Playerに渡す
	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Playerの当たり判定の情報を入れたmap, キーは対称の物体の種類（item, enemy, enemyAttack）, PlayerMgrに渡す
	const int ITEM_NUM = 2;	// セットできるitemの数

private:
	static PlayerMgr* mPlayerMgr;
};