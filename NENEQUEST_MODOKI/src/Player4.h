#pragma once

// �|�i�U���́F���ʁC�U���͈́F�L���C�U���������ԁF�����i���̍U���܂łɂ����鎞�ԁF�����j�C������Փx�F����j

#include "Player.h"
#include "Arrow.h"

class Player4 : public Player {
public:
	Player4(PlayerChanger* changer);
	~Player4();
	static Player4* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

protected:
	void UpdateSAP() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void UpdateHit() override; //Player_4�ɂ����Ă̂ݍU���̓����蔻��̎������قȂ邽��
	void StartBossStage() override;

private:
	void PrepareWAttack();	// �ア�U���i�|������܂Ŕ�ԁC����S�L�[�j�̏��������i�|����\���ĕ��܂ł̊Ԃ̏����j
	void PrepareSAttack();	// �����U���i�|������܂Ŕ�ԁC����S�L�[�j�̏��������i�|����\���ĕ��܂ł̊Ԃ̏����j

	static Player4* mPlayer4;
	Arrow* mArrow;
	bool mArrowExists;	// �|���ʏ�ɂ���ԁi�U�����ʂ������Ă���ԁj��true
	bool mIsPreparingWA;	// �ア�|�����O�̏�Ԃł���Ƃ��i�L�[����w�𗣂��΋|�����Ă��Ԃ̂Ƃ��j��true
	bool mIsPreparingSA;	// �����|�����O�̏�Ԃł���Ƃ��i�L�[����w�𗣂��΋|�����Ă��Ԃ̂Ƃ��j��true
};