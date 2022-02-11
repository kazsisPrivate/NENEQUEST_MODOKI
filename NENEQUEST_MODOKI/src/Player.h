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
	void SetPlParams(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Player��ύX����ۂɌĂяo�����C�O��Player�̏����p���Ŏg�p����
	virtual void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Player�̃f�[�^��n�����߂Ɏg�p����(int, bool)
	//void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Player�̃f�[�^��n�����߂Ɏg�p����(int)
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Player�̃f�[�^��n�����߂Ɏg�p����(int)
	void SetIsHits(std::map<std::string, std::vector<bool>>* isHitMap);	// Item, Enemy, EnemyAttack�Ƃ̓����蔻��̊m�F���ʂ��󂯎��CmPlIsHit��mPlAIsHit�ɑ������
	void SetEneAPowers(const int* const eneAPs);	// �eEnemy�̍U���͂��󂯎��CPlayer���ł�Enemy�̍U���͂̔c���̂��߂Ɏg�p����
	void SetIteParams(std::vector<std::map<std::string, float>>& iteDataMaps);	// �eItem�̏����󂯎��CPlayer���ł�Item�̌��ʂ̔c���̂��߂Ɏg�p����
	
protected:
	virtual void Walk() override;
	virtual void Jump();// override;
	virtual void Attack() override;
	virtual void UpdateSAP();// override;
	//void UpdateHit() override;
	void UpdateIteEffect();	// �����蔻����l������Item�̌��ʂ̍X�V
	void UpdateEneDamage();	// �����蔻����l������Enemy����󂯂�_���[�W�̍X�V
	void UpdateHp() override;	// item��Enemy�̓����蔻����l������hp�̍X�V
	virtual void StartBossStage();	// bossStage�ɓ����Ă���̈�莞�Ԃ̓���

	PlayerChanger* mPlayerChanger;
	PlayerMgr* mPlayerMgr;	// Enemy��Item�ȂǂƂ̓����蔻��Ȃǂ̏��̎擾�Ɏg�p����
	int mAX, mAY;	// Player�̍U���̒��S��xy���W
	int mHitRangeAW, mHitRangeAH; // Player�̍U���̓����蔻��̒��S���W����͈̔�(width, height)
	int mAFrameCnt;	// �U���������ƁC���ɍU���ł���悤�ɂȂ�܂ł̃C���^�[�o���Ƃ��Ďg�p����
	bool mIsJumping;	// �W�����v���Ȃ��true
	int mYStart, mYPrev;	// �W�����v�����Ŏg�p����B�ȑO��y���W��\��
	const int* mPlHandle;	// Player�̉摜
	const int HP_MAX = 10;	// Player��mHp�̏�� 
	int mAttackBase;	// �U���̓A�b�v�n�̃A�C�e���̌��ʂ��󂯂Ă��Ȃ���Ԃ̂Ƃ��̍U���́C�U���͍X�V�Ŏg�p����
	int mXFrameCnt, mYFrameCnt;	// x, y���ꂼ��ɂ����ĉ����Â����t���[�����̃J�E���g
	int mAFrameNum;	// �U���̌��ʎ��ԁi1��̍U���̎������ԁj
	int mEneDamage;	// Enemy����󂯂��_���[�W
	int mIteAP;	// Item�ɂ�肩����U���{��
	int mIteHP;	// Item�ɂ��񕜗�, 0�ȊO�̂Ƃ��͉񕜂���
	float mIteSP;	// Item�ɂ�鑬�x�{��
	int mEffectFrameCnt;	// Item�ɂ�肩���鎩�����̎��Ԍo�߂Ɏg�p����
	const int EFFECT_FRAME_NUM = 600;	// Item�ɂ�肩���鎩�����̃t���[����
	bool mIsEffected;	// Item�ɂ�肩���鎩�����̌��ʂ��󂯂Ă���Ƃ�
	//bool mHasIteS;	// �ړ����x�A�b�v��Item��ێ����Ă���Ƃ�true
	//int mIteSFrameCnt;	// Item�ɂ�肩�����x�A�b�v�̎��Ԍo�߂Ɏg�p����
	//bool mHasIteA;	// �U���̓A�b�v��Item��ێ����Ă���Ƃ�true
	//int mIteAFrameCnt;	// Item�ɂ�肩����U���A�b�v�̎��Ԍo�߂Ɏg�p����
	int* mEffectHandle;	// Item�ɂ�肩�����Ă����Ԃ̉摜�̕\���ɂ����Ďg��
	int mEffectId;	// ���ʂ��󂯂Ă���Item��Id�i0: �����󂯂Ă��Ȃ����, 1: ���x2�{, 2: ���x0.5�{, 3: �U����2�{�j
	int mIteKindId;	// ��ԍŐV�Ɏ擾����item�̎�ށi1: player1�̌��C2: player2�̌��C3: player3�̕��C4: player4�̋|�C5: �񕜌n�̃A�C�e���C�������n�̃A�C�e��, ���j
	int mBsStopFrameCnt; //bossStage�ɓ����Ă��班���̊ԓ����Ȃ�����̂Ɏg��
	//int prev_x, prev_y; //BossStart()�Ŏg��
	//int prev_xcount, prev_ycount;
	const int GOD_FRAME_NUM = 100;	// �U�����󂯂Ă��疳�G�ł�����t���[����
	//int mDeadFrameCnt; //player������ł���C���񂾂��Ƃ�F�������邽�߂�Player�������̊ԁC�ł点��Ƃ��Ɏg��
	const int DEAD_STOP_FRAME_NUM = 120;	// ���񂾂��Ƃ�F�������邽�߂�Player�̍d�����ԁi�t���[�����j
	const int ENEMY_NUM = 3;	// �Z�b�g�ł���G�̐��CmEneIsHits�̗v�f��
	bool mEneIsHits[3];	// enemy�̐g�̂Ƃ̓����蔻��̔z��
	//const int ENEMY_ATTACK_NUM = 5;	// �Z�b�g�ł���G�̐��CmEneAIsHits�̗v�f��
	bool mEneAIsHits[3];	// enemy�̍U���Ƃ̓����蔻��̔z��
	const int ITEM_NUM = 2;	// �Z�b�g�ł���item�̐��CmIteIsHits�̗v�f��
	bool mIteIsHits[2];	// item�Ƃ̓����蔻��̔z��
	std::map<std::string, std::vector<bool>> mPlAIsHitMap;	// item��enemy���L�[�Ƃ��Ď����C���ꂼ��ɑ΂��čU���������������ǂ��������Ă���
															// Player4�̋|��̏����Ŏg�p����
	bool mIsAtBsSt;	// bossStage�ɓ����Ă����true
	const int X_MIN_N = 53;	// normal stage�̍��[��x���W
	const int X_MAX_N = 1147;	// normal stage�̉E�[��x���W
	const int Y_MIN_N = 242;	// normal stage�̏�[��y���W
	const int Y_MAX_N = 598;	// normal stage�̉��[��y���W
	const int X_MIN_B = 53;	// boss stage�̍��[��x���W
	const int X_MAX_B = 690;	// boss stage�̉E�[�i���̍��[�܂Łj��x���W
	const int Y_MIN_B = 242;	// boss stage�̏�[��y���W
	const int Y_MAX_B = 598;	// boss stage�̉��[��y���W
	const int X_MIN_BR = 690;	// boss stage�̋��̍��[��x���W
	const int X_MAX_BR = 904;	// boss stage�̋��̉E�[��x���W
	const int Y_MIN_BR = 401;	// boss stage�̋��̏�[��y���W
	const int Y_MAX_BR = 494;	// boss stage�̋��̉��[��y���W
	//std::map<std::string, int> mPlIntDataMap;	// x, y, hp, hitRangeW, hitRangeH, hitRangeAW, hitRangeAH, effectFrameCnt, bsStopFrameCnt, effectId�Ȃǂ����Ă���map�C���̃N���X�ɓn���p
	//std::map<std::string, bool> mPlBoolDataMap;	// isDead, isAttacking�Ȃǂ����Ă���map�C���̃N���X�ɓn���p
	int mEneAPs[3];	// �eEnemy�̍U���͂���ꂽ�z��
	std::vector<std::map<std::string, float>> mIteDataMaps;	// �eItem��healPower, speedPower, attackPower�Ȃǂ����Ă���map
};
