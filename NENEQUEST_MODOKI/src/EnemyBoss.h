#pragma once
/*
* �{�X�i�h���S���j
*/
#include "Enemy.h"
#include "BossFire.h"
#include "ItemChanger.h"
#include <vector>


class EnemyBoss : public Enemy {
public:
	EnemyBoss(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemy�̃f�[�^��n�����߂Ɏg�p����

private:
	void UpdateSAP();	// hp�ɍ��킹���U���͂�X�s�[�h�ɕω�������
	void Walk() override;
	void Attack();
	void SelectAttack();	// �s���U�������߂�
	void SummonEnemy();	// Enemy���Ăт����U��
	void CreateEnemy();	// �V����Enemy�𐶐�����CSummonEnemy�ŌĂт���
	void DropItemBox();	// ItemBox�𗎂Ƃ��U��
	void Jump();	// ItemBox�𗎂Ƃ��U�����ōs���W�����v
	void FireAttack();	// �΂̋ʍU��

	BossFire* mBossFire;
	int IMG_W = 958, IMG_H = 600;	// EnemyBoss�̉摜�T�C�Y

	const int ENEBOSS_X_MAX = 1210;	// EnemyBoss��x�������̈ړ��͈͂̍ő�l
	const int ENEBOSS_X_MIN = 1090;	// EnemyBoss��x�������̈ړ��͈͂̍ŏ��l
	const int ENEBOSS_FIRST_X = 1160;	// BossStage�ւ̈ڍs���I���CBossStage���n�܂�ۂ�EnemyBoss�̍ŏ���x���W
	std::vector<int> mAXs;	// �e�U����x���W
	std::vector<int> mAYs;	// �e�U����y���W
	std::vector<int> mHitRangeAWs;	// �e�U���̓����蔻��͈̔́i���j
	std::vector<int> mHitRangeAHs;	// �e�U���̓����蔻��͈̔́i�����j
	int mDirecX;	// EnemyBoss�̈ړ������̌����i-1: �������C1: �E�����j
	int mAlphaValue;	// �\������EnemyBoss�̉摜�̓����x�C�|���ꂽ�Ƃ��ɓ��߂��Ă����̂Ɏg�p����

	const int ENEBOSS_ATTACK_NUM_MAX = 5;	// EnemyBoss���ł���U���̍ő吔�iFireBreath�̉΂̋�5���䂪�ő�j
	const int HP_ANGRY = 30;	// EnemyBoss���{�肾��hp�C�{�肾���ƍU���̎�ނ⑬�x�C�U���͓����ω�����
	
	unsigned long long mWatingFrameCnt;	// �U���ƍU���Ԃ̃t���[�����̃J�E���g�C�U���̎n�߂�^�C�~���O�Ȃǂ̐���Ɏg�p����
	bool mIsChangingSt;	// BossStage�ւ̈ڍs���̂Ƃ�true�CEnemyBoss�̃I�u�W�F�N�g���쐬���ꂽ�Ƃ��͈ڍs���ł���C�K��̈ʒu�Ɉړ����I������false�ɂȂ�

	int mAFrameCnt;	// �U�����̃t���[�����̃J�E���g�C�U���̎��Ԑ���Ɏg�p����
	const int ATTACK_FRAME_NUM = 240;	// ���̃t���[�������ɍU�������邩�ǂ��������߂�
	bool mIsFireAttacking;	// �΂̋ʍU�����̂Ƃ�true�ƂȂ�
	bool mIsSummoningEne;	// Enemy�Ăяo���U�����̂Ƃ�true
	bool mIsDroppingIteB;	// ItemBox���Ƃ��U���̂Ƃ�true
	const int ENEMY_FIRST_Y_MIN = 290;	// enemy�����������ۂ̍ŏ���y���W�̍ŏ��l
	const int ENEMY_FIRST_Y_MAX = 610;	// enemy�����������ۂ̍ŏ���y���W�̍ő�l

	bool mIsJumping;	// ItemBox���Ƃ����ōs���W�����v����������true
	int mYPrev, mYStart;	// �W�����v�Ŏg�p����

	int* mIteBHandle;	// ���Ƃ�ItemBox�̉摜
	int mIteBImgW, mIteBImgH;	// ���Ƃ�ItemBox�̉摜�T�C�Y
	EItem mIteBKind;	// ���Ƃ�Item�̎��
	int mIteBX, mIteBY;	// ItemBox���Ƃ��ŗ��Ƃ�ItemBox��xy���W
	const int ITEMBOX_FIRST_X_MIN = 300;	// ItemBox���������ꂽ�ۂ̍ŏ���y���W�̍ŏ��l
	const int ITEMBOX_FIRST_X_MAX = 650;	// ItemBox���������ꂽ�ۂ̍ŏ���y���W�̍ő�l
	int mIteBDY;	// ItemBox���Ƃ��ŗ��Ƃ�ItemBox��y���W�̑�����
	int mIteBHitRangeW, mIteBHitRangeH;	// ���Ƃ�ItemBox�̓����蔻��
	bool mIsCreatingIteB;	// ItemBox�𗎉������I���Ă���CItemBox��ItemMgr�̕��ō���Ă�����Ă���Ƃ�true 
	int mCreIteBFrameCnt;	// ItemBox�𗎉������I���Ă���CItemBox��ItemMgr�̕��ō���Ă�����Ă���Ԃ̃t���[����
};