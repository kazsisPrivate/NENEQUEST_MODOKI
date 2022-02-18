#pragma once

// �|�i�U���́F���ʁC�U���͈́F�L���C�U���������ԁF�����i���̍U���܂łɂ����鎞�ԁF�����j�C������Փx�F����j

#include "Player.h"
#include "Arrow.h"

class Player4 : public Player {
public:
	Player4(PlayerChanger* changer);
	static Player4* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) override;	// �|������Ă���Ԃ̂ݓ����蔻��̂���U�����Ƃ݂Ȃ����߂ɁC
																														// Player���g�̍U�����ł͂Ȃ��CArrow�̕��̏��𗘗p����K�v�����邽��

protected:
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void StartBossStage() override;

private:
	void PrepareWAttack();	// �ア�U���i�|������܂Ŕ�ԁC����S�L�[�j�̏��������i�|����\���ĕ��܂ł̊Ԃ̏����j
	void PrepareSAttack();	// �����U���i�|������܂Ŕ�ԁC����S�L�[�j�̏��������i�|����\���ĕ��܂ł̊Ԃ̏����j
	void UpdateArrowIsHit();	// �|��̍U���������������ǂ����̓����蔻��֘A�̍X�V�������s��

	static Player4* mPlayer4;
	Arrow* mArrow;
	bool mArrowExists;	// �|���ʏ�ɂ���ԁi�U�����ʂ������Ă���ԁj��true
	bool mIsPreparingWA;	// �ア�|�����O�̏�Ԃł���Ƃ��i�L�[����w�𗣂��΋|�����Ă��Ԃ̂Ƃ��j��true
	bool mIsPreparingSA;	// �����|�����O�̏�Ԃł���Ƃ��i�L�[����w�𗣂��΋|�����Ă��Ԃ̂Ƃ��j��true
	bool mArrowIsHit;	// �|������ɓ������true
};