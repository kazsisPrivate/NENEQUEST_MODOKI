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
	// �����蔻��֘A�ݒ�
	mIsHitPlA = false;
	mIsGod = false;
	mGodFrameCnt = 0;

	// Enemy�̍U���֘A�ݒ�
	mIsAttacking = false;

	// ���̑�
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
	//(*eneIntDataMap)["handleId"] = mHandleId;

	//(*eneBoolDataMap)["isDead"] = mIsDead;
	(*eneBoolDataMap)["isAttacking"] = mIsAttacking;
}


void  Enemy::SetIsHit(const bool isHit) {
	// Player�̍U���Ƃ̓����蔻����Z�b�g
	mIsHitPlA = isHit;
}


void Enemy::SetPlParams(std::map<std::string, int>* plDataMap) {
	// Player��x, y���W���Z�b�g
	mPlX = (*plDataMap)["x"];
	mPlY = (*plDataMap)["y"];

	// Player�̍U���͂��Z�b�g
	mPlAP = (*plDataMap)["attack"];
}


void Enemy::UpdateHp() {
	if (mIsHitPlA && !mIsGod) {	// �U�����󂯂āC�����G���ԂłȂ��Ƃ� 
		mHp -= mPlAP;

		// �����̊Ԗ��G�ɂȂ�
		mIsGod = true;
		mGodFrameCnt = 0;
	}
}