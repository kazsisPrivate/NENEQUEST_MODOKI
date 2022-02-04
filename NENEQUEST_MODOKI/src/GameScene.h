#pragma once

#include "BaseScene.h"
#include "SceneChanger.h"
#include "PlayerMgr.h"
//#include "EnemyMgr.h"
//#include "ItemMgr.h"
#include "GameBack.h"
//#include "GameClear.h"

//#include "HpGauge.h"
//#include "Appearance.h"
#include "CharaGraphics.h"

//#include "GameOver.h"

//#include "GameCounters.h"

#include <memory>
#include <string>


class GameScene : public BaseScene {
public:
	GameScene(SceneChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	GameBack* mGameBack;
	PlayerMgr* mPlayerMgr;
	/*EnemyMgr* enemyMgr;
	ItemMgr* itemMgr;
	HpGauge* hpGauge;
	Appearance* appear;*/
	CharaGraphics mCharaGraphics;
	//GameCounters gameCtrs;
	//GameOver gameOver;
	//std::unique_ptr<GameClear> gameClear;
	int charaY[6]; //Chara��y���W�AYJudge�Ŏg�p����
	int yJudge[6]; //�\�[�g�Ŏg�p���邽�߂̔z��
	int drawNum[6]; //chara�̕`�揇������B1:player, 2-4:enemy, 5-6:item
	int mSoundHandle;	// ����
	//int itAppear[320]; //�n�߂�Ɠ�����Appearance.txt��1�񂾂��ǂݍ���ł����ɓ����ItemMgr�ɃR���X�g���N�^�̈����Ƃ��ēn���Ă�����
	//int eneAppear[320]; //�n�߂�Ɠ�����Appearance.txt��1�񂾂��ǂݍ���ł����ɓ����EnemyMgr�ɃR���X�g���N�^�̈����Ƃ��ēn���Ă�����
	//bool dnCheck[5]; //drawNum�����I����Ă�����true�A�����Ă��Ȃ����false�B����y���W�ɂ���ꍇ�̂��߁B check���邽�߂Ȃ̂�else�̕��͂Ȃ�
	//bool m_plDeadFlag; //Player�̗̑͂�0�ɂȂ����Ƃ�true
	//bool m_bsDeadFlag; //Boss�̗̑͂�0�ɂȂ����Ƃ�true
	std::pair<std::pair<int, int>, int> mCharaDord;	// first�ɃL�����̎�ނ�id�ƃL�����ԍ��̃y�A�Csecond�ɕ`��̏��Ԃ�����
	void SetDrawingOrder(); // Player, Enemy, Item�̕`�揇���Z�b�g����
	//void Sort(int num[]); //YJudge�Ŏg�p����\�[�g�̂��߂̊֐�
	int iNum;

	std::map<std::string, int> mPlIntDataMap;	// Player��x, y, hp, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectId�����Ă���map
};