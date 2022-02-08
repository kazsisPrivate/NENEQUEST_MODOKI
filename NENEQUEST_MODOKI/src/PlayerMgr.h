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
	void GetPlDataMaps(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Player�̏����擾���邽�߂Ɏg�p����CGameScene�ɓn��
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);
	void SetIsHitMap(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttack�Ƃ̓����蔻��̊m�F���ʂ�Map���󂯎��
	void SetIteDataMaps(std::vector<std::map<std::string, float>>& iteDataMaps);	// Item�̌��ʂ̏����󂯎��CPlayer���ł�Item�̌��ʂ̔c���̂��߂Ɏg�p����
	//bool GetDead(); //player��hp��0���ǂ����𓾂�@GameOver�̉�ʂɈڍs����̂Ɏg���@Game.cpp�ɂĎg�p���Ă���
	
	
	

private:
	Player* mPlayer;
	EPlayer mPlayerNext;
	GameScene* mGameScene;
	std::vector<std::map<std::string, float>> mIteDataMaps;	// �eItem��healPower, speedPower, attackPower�Ȃǂ����Ă���map, Player�ɓn��
	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Player�̓����蔻��̏�����ꂽmap, �L�[�͑Ώ̂̕��̂̎�ށiitem, enemy, enemyAttack�j, PlayerMgr�ɓn��
	const int ITEM_NUM = 2;	// �Z�b�g�ł���item�̐�

private:
	static PlayerMgr* mPlayerMgr;
};