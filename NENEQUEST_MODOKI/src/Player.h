#pragma once

#include "Chara.h"
#include "PlayerChanger.h"
#include "CharaGraphics.h"
#include "UpdateKey.h"
#include <vector>
#include <map>
#include <string>
#include <vector>


class PlayerMgr;


class Player : public Chara, public UpdateKey {
public:
	Player(PlayerChanger* changer, const int* graph);
	//virtual void GetInstance() override {};
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Draw() override;
	void SetPlParams(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerを変更する際に呼び出される，前のPlayerの情報引継ぎで使用する
	virtual void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerのデータを渡すために使用する(int, bool)
	//void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Playerのデータを渡すために使用する(int)
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Playerのデータを渡すために使用する(int)
	void SetIsHits(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttackとの当たり判定の確認結果を受け取り，mPlIsHitとmPlAIsHitに代入する
	void SetEneAPowers(const int* const eneAPs);	// 各Enemyの攻撃力を受け取る，Player側でのEnemyの攻撃力の把握のために使用する
	void SetIteParams(std::vector<std::map<std::string, float>>& iteDataMaps);	// 各Itemの情報を受け取る，Player側でのItemの効果の把握のために使用する
	
protected:
	virtual void Walk() override;
	virtual void Jump();// override;
	virtual void Attack() override;
	virtual void UpdateSAP();// override;
	//void UpdateHit() override;
	void UpdateIteEffect();	// 当たり判定を考慮したItemの効果の更新
	void UpdateEneDamage();	// 当たり判定を考慮したEnemyから受けるダメージの更新
	void UpdateHp() override;	// itemやEnemyの当たり判定を考慮したhpの更新
	virtual void StartBossStage();	// bossStageに入ってからの一定時間の動き

	PlayerChanger* mPlayerChanger;
	PlayerMgr* mPlayerMgr;	// EnemyやItemなどとの当たり判定などの情報の取得に使用する
	int mAX, mAY;	// Playerの攻撃の中心のxy座標
	int mHitRangeAW, mHitRangeAH; // Playerの攻撃の当たり判定の中心座標からの範囲(width, height)
	int mAFrameCnt;	// 攻撃したあと，次に攻撃できるようになるまでのインターバルとして使用する
	bool mIsJumping;	// ジャンプ中ならばtrue
	int mYStart, mYPrev;	// ジャンプ処理で使用する。以前のy座標を表す
	const int* mPlHandle;	// Playerの画像
	const int HP_MAX = 10;	// PlayerのmHpの上限 
	int mAttackBase;	// 攻撃力アップ系のアイテムの効果を受けていない状態のときの攻撃力，攻撃力更新で使用する
	int mXFrameCnt, mYFrameCnt;	// x, yそれぞれにおいて押しつづけたフレーム数のカウント
	int mAFrameNum;	// 攻撃の効果時間（1回の攻撃の持続時間）
	int mEneDamage;	// Enemyから受けたダメージ
	int mIteAP;	// Itemによりかかる攻撃倍率
	int mIteHP;	// Itemによる回復量, 0以外のときは回復する
	float mIteSP;	// Itemによる速度倍率
	int mEffectFrameCnt;	// Itemによりかかる自強化の時間経過に使用する
	const int EFFECT_FRAME_NUM = 600;	// Itemによりかかる自強化のフレーム数
	bool mIsEffected;	// Itemによりかかる自強化の効果を受けているとき
	//bool mHasIteS;	// 移動速度アップのItemを保持しているときtrue
	//int mIteSFrameCnt;	// Itemによりかか速度アップの時間経過に使用する
	//bool mHasIteA;	// 攻撃力アップのItemを保持しているときtrue
	//int mIteAFrameCnt;	// Itemによりかかる攻撃アップの時間経過に使用する
	int* mEffectHandle;	// Itemによりかかっている状態の画像の表示において使う
	int mEffectId;	// 効果を受けているItemのId（0: 何も受けていない状態, 1: 速度2倍, 2: 速度0.5倍, 3: 攻撃力2倍）
	int mIteKindId;	// 一番最新に取得したitemの種類（1: player1の剣，2: player2の剣，3: player3の斧，4: player4の弓，5: 回復系のアイテム，自強化系のアイテム, 箱）
	int mBsStopFrameCnt; //bossStageに入ってから少しの間動けなくするのに使う
	//int prev_x, prev_y; //BossStart()で使う
	//int prev_xcount, prev_ycount;
	const int GOD_FRAME_NUM = 100;	// 攻撃を受けてから無敵でいられるフレーム数
	//int mDeadFrameCnt; //playerが死んでから，死んだことを認識させるためにPlayerを少しの間，固らせるときに使う
	const int DEAD_STOP_FRAME_NUM = 120;	// 死んだことを認識させるためのPlayerの硬直時間（フレーム数）
	const int ENEMY_NUM = 3;	// セットできる敵の数，mEneIsHitsの要素数
	bool mEneIsHits[3];	// enemyの身体との当たり判定の配列
	//const int ENEMY_ATTACK_NUM = 5;	// セットできる敵の数，mEneAIsHitsの要素数
	bool mEneAIsHits[3];	// enemyの攻撃との当たり判定の配列
	const int ITEM_NUM = 2;	// セットできるitemの数，mIteIsHitsの要素数
	bool mIteIsHits[2];	// itemとの当たり判定の配列
	std::map<std::string, std::vector<bool>> mPlAIsHitMap;	// itemとenemyをキーとして持ち，それぞれに対して攻撃が当たったかどうかを入れている
															// Player4の弓矢の処理で使用する
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
	//std::map<std::string, int> mPlIntDataMap;	// x, y, hp, hitRangeW, hitRangeH, hitRangeAW, hitRangeAH, effectFrameCnt, bsStopFrameCnt, effectIdなどを入れているmap，他のクラスに渡す用
	//std::map<std::string, bool> mPlBoolDataMap;	// isDead, isAttackingなどを入れているmap，他のクラスに渡す用
	int mEneAPs[3];	// 各Enemyの攻撃力を入れた配列
	std::vector<std::map<std::string, float>> mIteDataMaps;	// 各ItemのhealPower, speedPower, attackPowerなどを入れているmap
};
