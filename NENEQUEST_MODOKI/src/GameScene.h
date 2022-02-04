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
	int charaY[6]; //Charaのy座標、YJudgeで使用する
	int yJudge[6]; //ソートで使用するための配列
	int drawNum[6]; //charaの描画順を入れる。1:player, 2-4:enemy, 5-6:item
	int mSoundHandle;	// 音源
	//int itAppear[320]; //始めると同時にAppearance.txtを1回だけ読み込んでここに入れてItemMgrにコンストラクタの引数として渡してあげる
	//int eneAppear[320]; //始めると同時にAppearance.txtを1回だけ読み込んでここに入れてEnemyMgrにコンストラクタの引数として渡してあげる
	//bool dnCheck[5]; //drawNumを入れ終わっていたらtrue、入っていなければfalse。同じy座標にある場合のため。 checkするためなのでelseの分はない
	//bool m_plDeadFlag; //Playerの体力が0になったときtrue
	//bool m_bsDeadFlag; //Bossの体力が0になったときtrue
	std::pair<std::pair<int, int>, int> mCharaDord;	// firstにキャラの種類のidとキャラ番号のペア，secondに描画の順番を入れる
	void SetDrawingOrder(); // Player, Enemy, Itemの描画順をセットする
	//void Sort(int num[]); //YJudgeで使用するソートのための関数
	int iNum;

	std::map<std::string, int> mPlIntDataMap;	// Playerのx, y, hp, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectIdを入れているmap
};