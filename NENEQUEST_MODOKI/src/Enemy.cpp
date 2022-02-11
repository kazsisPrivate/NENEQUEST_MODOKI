#include "Enemy.h"
#include "EnemyMgr.h"


Enemy::Enemy(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y) : mEneHandle(graph) {
	mEnemyChanger = changer;
	mEneIdx = eneIdx;
	mX = x;
	mY = y;

	mEnemyMgr = EnemyMgr::GetInstance();
}


void Enemy::Initialize() {
	// 当たり判定関連設定
	mIsHitPlA = false;
	mIsGod = false;
	mGodFrameCnt = 0;

	// Enemyの攻撃関連設定
	mIsAttacking = false;

	// その他
	mHandleId = 0;
}


void Enemy::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	(*eneIntDataMap)["x"] = mX;
	(*eneIntDataMap)["y"] = mY;
	(*eneIntDataMap)["hp"] = mHp;
	(*eneIntDataMap)["hitRangeW"] = mHitRangeW;
	(*eneIntDataMap)["hitRangeH"] = mHitRangeH;
	(*eneIntDataMap)["attack"] = mAttack;
	(*eneIntDataMap)["attackNum"] = mEneANum;

	//(*eneBoolDataMap)["isDead"] = mIsDead;
	(*eneBoolDataMap)["isAttacking"] = mIsAttacking;
}


void  Enemy::SetIsHit(const bool isHit) {
	// Playerの攻撃との当たり判定をセット
	mIsHitPlA = isHit;
}


void Enemy::SetPlAPower(const int plAPower) {
	// Playerの攻撃力をセット
	mPlAP = plAPower;
}


void Enemy::UpdateHp() {
	if (mIsHitPlA && !mIsGod) {	// 攻撃を受けて，かつ無敵時間でないとき 
		mHp -= mPlAP;

		// 少しの間無敵になる
		mIsGod = true;
		mGodFrameCnt = 0;
	}
}