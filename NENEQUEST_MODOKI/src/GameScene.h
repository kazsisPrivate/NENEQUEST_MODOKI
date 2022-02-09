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
	void SetDrawingOrder(); // Player, Enemy, Itemの描画順をセットする
	void UpdateHit();	// Player, Enemy, Item間の当たり判定の更新を行う
	bool IsHit(const int (&ps1)[4], const int (&ps2)[4]);	// それぞれのターゲットの位置の配列を渡して，当たり判定を確認し，当たっていたらtrueを返す

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
	int charaY[6]; //Charaのy座標、YJudgeで使用する
	int yJudge[6]; //ソートで使用するための配列
	int drawNum[6]; //charaの描画順を入れる。1:player, 2-4:enemy, 5-6:item
	int mSoundHandle;	// 音源
	//int itAppear[320]; //始めると同時にAppearance.txtを1回だけ読み込んでここに入れてItemMgrにコンストラクタの引数として渡してあげる
	//int eneAppear[320]; //始めると同時にAppearance.txtを1回だけ読み込んでここに入れてEnemyMgrにコンストラクタの引数として渡してあげる
	//bool dnCheck[5]; //drawNumを入れ終わっていたらtrue、入っていなければfalse。同じy座標にある場合のため。 checkするためなのでelseの分はない
	//bool m_plDeadFlag; //Playerの体力が0になったときtrue
	//bool m_bsDeadFlag; //Bossの体力が0になったときtrue
	std::pair<std::pair<int, int>, int> mCharaDord;	// firstにキャラの種類のidとインデックス番号のペア，secondに描画の順番を入れる
													// （0: Player, 1: Enemy, 2: Item）
	//void Sort(int num[]); //YJudgeで使用するソートのための関数
	int iNum;
	
	std::map<std::string, int> mPlIntDataMap;	// Playerのx, y, hp, hitRangeW, hitRangeH, hitRangeAW, hitRangeAH, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectIdなどを入れているmap
	std::map<std::string, bool> mPlBoolDataMap;	// PlayerのisDead, isAttackingなどを入れているmap
	std::vector<std::map<std::string, float>> mIteDataMaps;	// 各Itemのx, y, hitRangeW, hitRangeH, healPower, speedPower, attackPowerなどを入れているmap
	bool mIteIsExistings[2];	// 各Itemが存在しているかどうか（NULLであるかないか），存在していればtrue
	std::map<std::string, std::vector<bool>> mPlIsHitMap;	// Playerの当たり判定の情報を入れたmap, キーは対称の物体の種類（item, enemy, enemyAttack）, PlayerMgrに渡す
	std::vector<std::map<std::string, bool>> mIteIsHitMaps;	// 各Itemの当たり判定の情報を入れたmap, キーは対称の物体の種類（player, playerAttack）, ItemMgrに渡す
	const int ITEM_NUM = 2;	// 保持できるitemの数

private:
	static GameScene* mGameScene;
	static int tmpNum;
};