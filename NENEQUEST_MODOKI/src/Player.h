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
		const int iteAFrameCnt, const int bsStopFrameCnt, const int effectId, const int deadFrameCnt, const bool isDead);	// Player��ύX����ۂɌĂяo�����C�O��Player�̏����p���Ŏg�p����
	void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap);	// Player�̃f�[�^��n�����߂Ɏg�p����(int, bool)
	void GetPlIntDataMap(std::map<std::string, int>* plIntDataMap);	// Player�̃f�[�^��n�����߂Ɏg�p����(int)
	
protected:
	virtual void Walk() override;
	virtual void Jump() override;
	virtual void Attack() override;
	virtual void UpdateSAP() override;
	void UpdateHit() override;
	virtual void StartBossStage();	// bossStage�ɓ����Ă���̈�莞�Ԃ̓���

	PlayerChanger* mPlayerChanger;
	const int* mPlHandle;	// Player�̉摜
	int mXFrameCnt, mYFrameCnt;	// x, y���ꂼ��ɂ����ĉ����Â����t���[�����̃J�E���g
	int mAFrameNum;	// �U���̌��ʎ��ԁi1��̍U���̎������ԁj
	int mEneAP;	// Enemy��1��̍U���Ŏ󂯂�_���[�W
	int mIteAP;	// Item�ɂ�肩����U���{��
	int mIteHP;	// Item�ɂ��񕜗�
	float mIteSP;	// Item�ɂ�鑬�x�{��
	int mIteFrameCnt;	// item�̓����蔻��̉񐔐����̂��߂Ɏg�p����
	bool mHasIteS;	// �ړ����x�A�b�v��Item��ێ����Ă���Ƃ�true
	int mIteSFrameCnt;	// Item�ɂ�肩�����x�A�b�v�̎��Ԍo�߂Ɏg�p����
	bool mHasIteA;	// �U���̓A�b�v��Item��ێ����Ă���Ƃ�true
	int mIteAFrameCnt;	// Item�ɂ�肩����U���A�b�v�̎��Ԍo�߂Ɏg�p����
	int mEffectHandle;	// Item�ɂ�肩�����Ă����Ԃ̉摜�̕\���ɂ����Ďg��
	int mEffectId;	// ���ʂ��󂯂Ă���Item��Id�C0�͉����󂯂Ă��Ȃ����
	int mIteKindId;	// ��ԍŐV�Ɏ擾����item�̎�ށi1: player1�̌��C2: player2�̌��C3: player3�̕��C4: player4�̋|�C5: �񕜌n�̃A�C�e���C6: �������n�̃A�C�e���j
	int mBsStopFrameCnt; //bossStage�ɓ����Ă��班���̊ԓ����Ȃ�����̂Ɏg��
	//int prev_x, prev_y; //BossStart()�Ŏg��
	//int prev_xcount, prev_ycount;
	int mDeadFrameCnt; //player������ł���C���񂾂��Ƃ�F�������邽�߂�Player�������̊ԁC�ł点��Ƃ��Ɏg��
	const int DEAD_STOP_FRAME_NUM = 120;	// ���񂾂��Ƃ�F�������邽�߂�Player�̍d�����ԁi�t���[�����j
	//bool eneJudge0, eneJudge1, eneJudge2; //enemy�Ƃ̓����蔻��
	//bool eneAJudge0, eneAJudge1, eneAJudge2; //enemy�Ƃ̓����蔻��
	//bool iJudge0, iJudge1; //item�Ƃ̓����蔻��
	//bool aiJudge0, aiJudge1; //PlayerAttack
	std::vector<bool> mIsHitEneVec;	// enemy�̐g�̂Ƃ̓����蔻���vector
	std::vector<bool> mIsHitEneAVec;	// enemy�̍U���Ƃ̓����蔻���vector
	std::vector<bool> mIsHitIteVec;	// item�Ƃ̓����蔻���vector
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
	std::map<std::string, int> mPlIntDataMap;	// x, y, hp, iteSFrameCnt, iteAFrameCnt, bsStopFrameCnt, effectId�����Ă���map�C���̃N���X�ɓn���p
	std::map<std::string, bool> mPlBoolDataMap;	// isBool�����Ă���map�C���̃N���X�ɓn���p
	PlayerMgr* mPlayerMgr;	// Enemy��Item�ȂǂƂ̓����蔻��Ȃǂ̏��̎擾�Ɏg�p����
};
