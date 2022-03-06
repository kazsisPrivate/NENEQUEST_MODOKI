#pragma once
/*
* Enemy1�`7, EnemyBoss�̊��N���X
*/
#include "Chara.h"
#include "EnemyChanger.h"
#include "CharaGraphics.h"
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
		std::map<std::string, bool>* eneBoolDataMap);	// Enemy�̃f�[�^��n�����߂Ɏg�p����
	void SetIsHit(const bool isHit);	// Player�̍U���Ƃ̓����蔻��̊m�F���ʂ��󂯎��CmIsHitPlA�ɑ������
	void SetPlParams(std::map<std::string, int>* plDataMap);	// Player�̏����󂯎��CEnemy���ł�Player��x, y, �U���͂Ȃǂ̔c���̂��߂Ɏg�p����

protected:
	void UpdateHp() override;	// Player�̍U���̓����蔻����l������hp�̍X�V

	EnemyChanger* mEnemyChanger;
	EnemyMgr* mEnemyMgr;	// Player�̍U���Ƃ̓����蔻��Ȃǂ̏��̎擾�Ɏg�p����

	const int* mEneHandle;	// Enemy�̉摜

	int mEneANum;	// Enemy���o����U���̐��i�΂̋�3�Ȃ�3, 1�̊p�ōU���Ȃ�1�Ȃǁj�C�ő�5
	int mEneIdx;	// �g�p���Ă���mEnemies�̃C���f�b�N�X�ԍ�
	int mPlAP;	// Player��1��̍U���Ŏ󂯂�_���[�W
	int mPlX, mPlY;	// Player��x, y���W
	int mScore;	// Player��Enemy��|�����ۂɓ�����X�R�A
	
	bool mIsHitPlA;	// Player�̍U���Ƃ̓����蔻��C�������Ă���Ƃ���true
	const int GOD_FRAME_NUM = 100;	// �U�����󂯂Ă��疳�G�ł�����t���[����
	const int DEAD_STOP_FRAME_NUM = 10;	// hp��0�ɂȂ��Ă��玀�񂾂��Ƃ�F�������邽�߂�Enemy�̍d�����ԁi�t���[�����j
	bool mIsDead;	// Enemy��Player�ɓ|���ꂽ�Ƃ���true�ɂȂ�
	bool mIsBoss;	// Enemy��Boss�������Ƃ�true, EnemyBoss�ȊO��false, GameScene�̕��ōs��������Boss�̎��̂ݍs������������g�p����
};