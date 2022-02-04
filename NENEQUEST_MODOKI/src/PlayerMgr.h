#pragma once

#include "PlayerChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>


class Player;


class PlayerMgr : public PlayerChanger, BasicFunc {
public:
	PlayerMgr();
	~PlayerMgr();
	static PlayerMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangePlayer(EPlayer playerNext) override;
	//bool GetDead(); //playerのhpが0かどうかを得る　GameOverの画面に移行するのに使う　Game.cppにて使用している
	//void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);

private:
	Player* mPlayer;
	EPlayer mPlayerNext;

private:
	static PlayerMgr* mPlayerMgr;
};