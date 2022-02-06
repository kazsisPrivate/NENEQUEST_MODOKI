#pragma once

#include "Chara.h"
#include "PlayerChanger.h"
#include "CharaGraphics.h"
#include "UpdateKey.h"
#include <vector>
#include <map>
#include <string>


class PlayerMgr;


class Player : public Chara, public UpdateKey {
public:
	Player(PlayerChanger* changer, const int* graph);
	//virtual void GetInstance() override {};
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Draw() override;
	void SetPlParams(const int x, const int y, const int hp, const int iteSFrameCnt, 
		const int iteAFrameCnt, const int bsStopFrameCnt, const int effectId, const int deadFrameCnt, const bool isDead);	// Playerを変更する際に呼び出される，前のPlayerの情報引継ぎで使用する
	void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerのデータを渡すために使用する(int, bool)
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Playerのデータを渡すために使用する(int)
	
protected:
	virtual void Walk() override;
	virtual void Jump() override;
	virtual void Attack() override;
	virtual void UpdateSAP() override;
	void UpdateHit() override;
	virtual void StartBossStage();	// bossStageに入ってからの一定時間の動き

	PlayerChanger* mPlayerChanger;
	const int* mPlHandle;	// Playerの画像
	int mXFrameCnt, mYFrameCnt;	// x, yそれぞれにおいて押しつづけたフレーム数のカウント
	int mAFrameNum;	// 攻撃の効果時間（1回の攻撃の持続時間）
	int mEneAP;	// Enemyの1回の攻撃で受けるダメージ
	int mIteAP;	// Itemによりかかる攻撃倍率
	int mIteHP;	// Itemによる回復量
	float mIteSP;	// Itemによる速度倍率
	int mIteFrameCnt;	// itemの当たり判定の回数制限のために使用する
	bool mHasIteS;	// 移動速度アップのItemを保持しているときtrue
	int mIteSFrameCnt;	// Itemによりかか速度アップの時間経過に使用する
	bool mHasIteA;	// 攻撃力アップのItemを保持しているときtrue
	int mIteAFrameCnt;	// Itemによりかかる攻撃アップの時間経過に使用する
	int mEffectHandle;	// Itemによりかかっている状態の画像の表示において使う
	int mEffectId;	// 効果を受けているItemのId，0は何も受けていない状態
	int mIteKindId;	// 一番最新に取得したitemの種類（1: player1の剣，2: player2の剣，3: player3の斧，4: player4の弓，5: 回復系のアイテム，6: 自強化系のアイテム）
	int mBsStopFrameCnt; //bossStageに入ってから少しの間動けなくするのに使う
	//int prev_x, prev_y; //BossStart()で使う
	//int prev_xcount, prev_ycount;
	int mDeadFrameCnt; //playerが死んでから，死んだことを認識させるためにPlayerを少しの間，固らせるときに使う
	const int DEAD_STOP_FRAME_NUM = 120;	// 死んだことを認識させるためのPlayerの硬直時間（フレーム数）
	//bool eneJudge0, eneJudge1, eneJudge2; //enemyとの当たり判定
	//bool eneAJudge0, eneAJudge1, eneAJudge2; //enemyとの当たり判定
	//bool iJudge0, iJudge1; //itemとの当たり判定
	//bool aiJudge0, aiJudge1; //PlayerAttack
	std::vector<bool> mIsHitEneVec;	// enemyの身体との当たり判定のvector
	std::vector<bool> mIsHitEneAVec;	// enemyの攻撃との当たり判定のvector
	std::vector<bool> mIsHitIteVec;	// itemとの当たり判定のvector
	bool mIsAtBsSt;	// bossStageに入っていればtrue
	const int X_MIN_N = 53;	// normal stageの左端のx座標
	const int X_MAX_N = 1147;	// normal stageの右端のx座標
	const int Y_MIN_N = 242;	// normal stageの上端のy座標
	const int Y_MAX_N = 598;	// normal stageの下端のy座標
	const int X_MIN_B = 53;	// boss stageの左端のx座標
	const int X_MAX_B = 690;	// boss stageの右端（橋の左端まで）のx座標
	const int Y_MIN_B = 242;	// boss stageの上端のy座標
	const int Y_MAX_B = 598;	// boss stageの下端のy座標
	const int X_MIN_BR = 690;	// boss stageの橋の左端のx座標
	const int X_MAX_BR = 904;	// boss stageの橋の右端のx座標
	const int Y_MIN_BR = 401;	// boss stageの橋の上端のy座標
	const int Y_MAX_BR = 494;	// boss stageの橋の下端のy座標
	std::map<std::string, int> mPlIntDataMap;	// x, y, hp, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectIdを入れているmap，他のクラスに渡す用
	std::map<std::string, bool> mPlBoolDataMap;	// isBoolを入れているmap，他のクラスに渡す用
	PlayerMgr* mPlayerMgr;	// EnemyやItemなどとの当たり判定などの情報の取得に使用する
};
