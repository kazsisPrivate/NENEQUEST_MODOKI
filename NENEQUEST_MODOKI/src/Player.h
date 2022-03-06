#pragma once
/*
* Player1～4の基底クラス
*/
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
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Draw() override;
	void SetPlParams(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerを変更する際に呼び出される，前のPlayerの情報引継ぎで使用する
	virtual void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Playerのデータを渡すために使用する(int, bool)
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Playerのデータを渡すために使用する(int)
	void SetIsHits(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttackとの当たり判定の確認結果を受け取り，mPlIsHitとmPlAIsHitに代入する
	void SetEneAPowers(const int* const eneAPs);	// 各Enemyの攻撃力を受け取る，Player側でのEnemyの攻撃力の把握のために使用する
	void SetIteParams(std::vector<std::map<std::string, float>>& iteDataMaps);	// 各Itemの情報を受け取る，Player側でのItemの効果の把握のために使用する
	void SetIsChangingSt(const bool isChangingSt);	// BossStageへ変化させているかどうかをセットする，PlayerをBossStage前の強制移動のために利用し，PlayerMgr側からセットする
	void SetIsAtBsSt(const bool isAtBsSt);	// BossStageにいるかどうかをセットする，PlayerをBossStageの挙動にするために利用し，PlayerMgr側からセットする
	
protected:
	virtual void Walk() override;
	virtual void Jump();	// ジャンプ
	virtual void Attack();	// 攻撃
	virtual void UpdateSAP();	// 移動速度と攻撃力の更新
	void UpdateIteEffect();	// 当たり判定を考慮したItemの効果の更新
	void UpdateEneDamage();	// 当たり判定を考慮したEnemyから受けるダメージの更新
	void UpdateHp() override;	// itemやEnemyの当たり判定を考慮したhpの更新
	virtual void StartBossStage() = 0;	// BossStageに入ってからの一定時間の動き

	PlayerChanger* mPlayerChanger;
	PlayerMgr* mPlayerMgr;	// EnemyやItemなどとの当たり判定などの情報の取得に使用する

	const int* mPlHandle;	// Playerの画像

	const int HP_MAX = 10;	// PlayerのmHpの上限 
	float mSpeedRate;	// mSpeedに掛け合わせる移動速度倍率、Playerの種類によって異なる
	int mAX, mAY;	// Playerの攻撃の中心のxy座標
	int mHitRangeAW, mHitRangeAH; // Playerの攻撃の当たり判定の中心座標からの範囲(width, height)
	int mAttackBase;	// 攻撃力アップ系のアイテムの効果を受けていない状態のときの攻撃力，攻撃力更新で使用する

	bool mIsJumping;	// ジャンプ中ならばtrue
	int mYStart, mYPrev;	// ジャンプ処理で使用する，以前のy座標を表す
	
	int mAFrameCnt;	// 攻撃したあと，次に攻撃できるようになるまでのインターバルとして使用する
	int mXFrameCnt, mYFrameCnt;	// x, yそれぞれにおいて押しつづけたフレーム数のカウント
	int mAFrameNum;	// 攻撃の効果時間（1回の攻撃の持続時間）

	int mEneDamage;	// Enemyから受けたダメージ
	int mIteAP;	// Itemによりかかる攻撃倍率
	int mIteHP;	// Itemによる回復量, 0以外のときは回復する
	float mIteSP;	// Itemによる速度倍率
	int mEffectFrameCnt;	// Itemによりかかる自強化の時間経過に使用する
	const int EFFECT_FRAME_NUM = 600;	// Itemによりかかる自強化のフレーム数
	bool mIsEffected;	// Itemによりかかる自強化の効果を受けているとき

	int* mEffectHandle;	// Itemによりかかっている状態の画像の表示において使う
	int mEffectId;	// 効果を受けているItemのId（0: 何も受けていない状態, 1: 速度2倍, 2: 速度0.5倍, 3: 攻撃力2倍）
	int mIteKindId;	// 一番最新に取得したitemの種類（1: player1の剣，2: player2の剣，3: player3の斧，4: player4の弓，5: 回復系のアイテム，自強化系のアイテム, 箱）

	bool mIsDead;	// mHpが0，かつ消していいとき（死んだことを認識させるための固定時間後など）にtrueになる
	int mBsStopFrameCnt; //bossStageに入ってから少しの間動けなくするのに使う
	const int GOD_FRAME_NUM = 100;	// 攻撃を受けてから無敵でいられるフレーム数
	const int DEAD_STOP_FRAME_NUM = 120;	// 死んだことを認識させるためのPlayerの硬直時間（フレーム数）

	const int ENEMY_NUM = 3;	// EnemyMgrにおいてセットできる敵の数，mEneIsHitsの要素数，敵の数の上限
	bool mEneIsHits[3];	// enemyの身体との当たり判定の配列
	bool mEneAIsHits[3];	// enemyの攻撃との当たり判定の配列

	const int ITEM_NUM = 2;	// セットできるitemの数，mIteIsHitsの要素数
	bool mIteIsHits[2];	// itemとの当たり判定の配列

	std::map<std::string, std::vector<bool>> mPlAIsHitMap;	// itemとenemyをキーとして持ち，それぞれに対して攻撃が当たったかどうかを入れている
															// Player4の弓矢の処理で使用する

	bool mIsChangingSt;	// BossStageに変更中のときtrue
	const int PL_FIRST_X_AT_BSST = 350;	// BossStageが始まる際のPlayerの最初のx座標，ステージ移行中にこの付近の座標に強制移動する
	const int PL_FIRST_Y_AT_BSST = 450;	// BossStageが始まる際のPlayerの最初のx座標，ステージ移行中にこの付近の座標に強制移動する
	const int SPEED_CHANGING_ST = 2;	// BossStageに移行する際の強制移動でのPlayerの移動速度（xy座標の増加（減少）量）
	bool mIsAtBsSt;	// BossStageに入っていればtrue

	const int X_MIN_N = 53;	// NormalStageの左端のx座標
	const int X_MAX_N = 1147;	// NormalStageの右端のx座標
	const int Y_MIN_N = 242;	// NormalStageの上端のy座標
	const int Y_MAX_N = 598;	// NormalStageの下端のy座標

	const int X_MIN_B = 53;	// BossStageの左端のx座標
	const int X_MAX_B = 690;	// BossStageの右端（橋の左端まで）のx座標
	const int Y_MIN_B = 242;	// BossStageの上端のy座標
	const int Y_MAX_B = 598;	// BossStageの下端のy座標
	const int X_MIN_BR = 690;	// BossStageの橋の左端のx座標
	const int X_MAX_BR = 850;	// BossStageの橋の右端のx座標
	const int Y_MIN_BR = 401;	// BossStageの橋の上端のy座標
	const int Y_MAX_BR = 494;	// BossStageの橋の下端のy座標
	
	int mEneAPs[3];	// 各Enemyの攻撃力を入れた配列
	std::vector<std::map<std::string, float>> mIteDataMaps;	// 各ItemのhealPower, speedPower, attackPowerなどを入れているmap
};
