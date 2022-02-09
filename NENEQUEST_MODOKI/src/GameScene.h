#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"
#include "GameBack.h"
//#include "GameClear.h"

#include "PlayerHpGauge.h"
//#include "Appearance.h"

//#include "GameOver.h"

//#include "GameCounters.h"
//#include "PlayerMgr.h"
//#include "EnemyMgr.h"
#include "ItemMgr.h"

#include <memory>
#include <string>
#include <map>
#include <vector>

//
class PlayerMgr;
////class EnemyMgr;
//class ItemMgr;
//class SceneMgr;


class GameScene : public BaseScene {
public:
	GameScene(SceneChanger* changer);
	static GameScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	void UpdateDOrder(); // Player, Enemy, Item�̕`�揇�idrawing order�j���X�V����
	void UpdateHit();	// Player, Enemy, Item�Ԃ̓����蔻��̍X�V���s��
	bool IsHit(const int (&ps1)[4], const int (&ps2)[4]);	// ���ꂼ��̃^�[�Q�b�g�̈ʒu�̔z���n���āC�����蔻����m�F���C�������Ă�����true��Ԃ�

	GameBack* mGameBack;
	PlayerMgr* mPlayerMgr;
	//EnemyMgr* enemyMgr;
	ItemMgr* mItemMgr;
	PlayerHpGauge* mPlHpGauge;
	//Appearance* appear;
	//CharaGraphics mCharaGraphics;
	//GameCounters gameCtrs;
	//GameOver gameOver;
	//std::unique_ptr<GameClear> gameClear;
	std::vector<std::pair<int, std::pair<int, int>>> mDOrderVec;	// �`�悷��I�u�W�F�N�g�̎�ނ�����pair��`�揇�ɓ����vector
														// first��y���W�Csecond�ɕ��̂̎�ނƃC���f�b�N�X�ԍ�����ꂽpair��vector
														// �L�����̎�ށi0: Player, 1: Enemy, 2: Item�j
	int mSoundHandle;	// ����
	//int itAppear[320]; //�n�߂�Ɠ�����Appearance.txt��1�񂾂��ǂݍ���ł����ɓ����ItemMgr�ɃR���X�g���N�^�̈����Ƃ��ēn���Ă�����
	//int eneAppear[320]; //�n�߂�Ɠ�����Appearance.txt��1�񂾂��ǂݍ���ł����ɓ����EnemyMgr�ɃR���X�g���N�^�̈����Ƃ��ēn���Ă�����
	//bool dnCheck[5]; //drawNum�����I����Ă�����true�A�����Ă��Ȃ����false�B����y���W�ɂ���ꍇ�̂��߁B check���邽�߂Ȃ̂�else�̕��͂Ȃ�
	//bool m_plDeadFlag; //Player�̗̑͂�0�ɂȂ����Ƃ�true
	//bool m_bsDeadFlag; //Boss�̗̑͂�0�ɂȂ����Ƃ�true
	//void Sort(int num[]); //YJudge�Ŏg�p����\�[�g�̂��߂̊֐�
	int iNum;
	
	std::map<std::string, int> mPlIntDataMap;	// Player��x, y, hp, hitRangeW, hitRangeH, hitRangeAW, hitRangeAH, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectId�Ȃǂ����Ă���map
	std::map<std::string, bool> mPlBoolDataMap;	// Player��isDead, isAttacking�Ȃǂ����Ă���map
	std::vector<std::map<std::string, float>> mIteDataMaps;	// �eItem��x, y, hitRangeW, hitRangeH, healPower, speedPower, attackPower�Ȃǂ����Ă���map
	bool mIteIsExistings[2];	// �eItem�����݂��Ă��邩�ǂ����iNULL�ł��邩�Ȃ����j�C���݂��Ă����true
	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Player�̓����蔻��̏�����ꂽmap, �L�[�͑Ώ̂̕��̂̎�ށiitem, enemy, enemyAttack, plAToItem, plAToEnemy�j, PlayerMgr�ɓn��
															// plAToItem��plAToEnemy��Player�̍U�����������Ă�����true�ŕԂ�
	std::vector<std::map<std::string, bool>> mIteIsHitMaps;	// �eItem�̓����蔻��̏�����ꂽmap, �L�[�͑Ώ̂̕��̂̎�ށiplayer, playerAttack�j, ItemMgr�ɓn��
	const int ITEM_NUM = 2;	// �ێ��ł���item�̐�

private:
	static GameScene* mGameScene;
	static int tmpNum;
};