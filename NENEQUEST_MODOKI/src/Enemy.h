#pragma once

#include "Chara.h"
#include "EnemyChanger.h"
#include "CharaGraphics.h"
//#include "ScoreAdder.h"
#include <map>
#include <string>
#include <vector>


class EnemyMgr;


class Enemy : public Chara {
public:
	Enemy(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y);
	virtual void Initialize() override;
	virtual void Finalize() override {};
	virtual void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap);	// Enemyのデータを渡すために使用する
	void SetIsHit(const bool isHit);	// Playerの攻撃との当たり判定の確認結果を受け取り，mIsHitPlAに代入する
	void SetPlParams(std::map<std::string, int>* plDataMap);	// Playerの情報を受け取る，Enemy側でのPlayerのx, y, 攻撃力などの把握のために使用する

protected:
	//virtual void Jump() override {};	// JumpとUpdateSAPはEnemyでは行わない
	//virtual void UpdateSAP() override {};
	void UpdateHp() override;	// Playerの攻撃の当たり判定を考慮したhpの更新

	EnemyChanger* mEnemyChanger;
	EnemyMgr* mEnemyMgr;	// Playerの攻撃との当たり判定などの情報の取得に使用する
	//ScoreAdder scrAdr;
	const int* mEneHandle;	// Enemyの画像
	int mEneANum;	// Enemyが出せる攻撃の数（火の玉3つなら3, 1つの角で攻撃なら1など），最大5
	int mEneIdx;	// 使用しているmEnemiesのインデックス番号
	int mPlAP;	// Playerの1回の攻撃で受けるダメージ
	int mPlX, mPlY;	// Playerのx, y座標
	//const int mEneNum; //mEnemyの何番目かを表す
	bool mIsHitPlA;	// Playerの攻撃との当たり判定，当たっているときはtrue
	const int GOD_FRAME_NUM = 100;	// 攻撃を受けてから無敵でいられるフレーム数
	const int DEAD_STOP_FRAME_NUM = 10;	// hpが0になってから死んだことを認識させるためのEnemyの硬直時間（フレーム数）
	//const int type; //そのenemyの攻撃や移動のパターンの番号
	//int plPower; //Playerから攻撃を受けたときのPlayerの攻撃力
	//bool paJudge; //Playerの攻撃との当たり判定

	//std::map<std::string, int> mEneIntDataMap;	// x, y, hitRangeW, hitRangeH, hitRangeAW, hitRangeAHなどを入れているmap，他のクラスに渡す用
	//std::vector<std::map<std::string, int>> mEneAXYMapVec;	// 各攻撃のax, ay, を入れているmapのvector，他のクラスに渡す用
													// Enemyは複数の火の玉攻撃などを持っているため，ax, ayも複数存在する
	//std::map<std::string, bool> mEneBoolDataMap;	// isDead, isAttackingなどを入れているmap，他のクラスに渡す用
};