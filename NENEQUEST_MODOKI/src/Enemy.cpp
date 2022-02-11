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
	// “–‚½‚è”»’èŠÖ˜Aİ’è
	mIsHitPlA = false;
	mIsGod = false;
	mGodFrameCnt = 0;

	// Enemy‚ÌUŒ‚ŠÖ˜Aİ’è
	mIsAttacking = false;

	// ‚»‚Ì‘¼
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
	// Player‚ÌUŒ‚‚Æ‚Ì“–‚½‚è”»’è‚ğƒZƒbƒg
	mIsHitPlA = isHit;
}


void Enemy::SetPlAPower(const int plAPower) {
	// Player‚ÌUŒ‚—Í‚ğƒZƒbƒg
	mPlAP = plAPower;
}


void Enemy::UpdateHp() {
	if (mIsHitPlA && !mIsGod) {	// UŒ‚‚ğó‚¯‚ÄC‚©‚Â–³“GŠÔ‚Å‚È‚¢‚Æ‚« 
		mHp -= mPlAP;

		// ­‚µ‚ÌŠÔ–³“G‚É‚È‚é
		mIsGod = true;
		mGodFrameCnt = 0;
	}
}