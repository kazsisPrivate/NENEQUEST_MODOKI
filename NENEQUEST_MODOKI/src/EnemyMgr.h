#pragma once

#include "EnemyChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>
#include <vector>


class Enemy;


class EnemyMgr : public EnemyChanger, BasicFunc {
public:
	static EnemyMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {};
	void Draw(const int eneIdx);	// �w�肳�ꂽ�C���f�b�N�X�ԍ���mEnemy��`��
	void ChangeEnemy(const int eneIdx, EEnemy eneNext,
		const int eneNextX, const int eneNextY) override;	// eneIdx�͔z��mEnemy�̃C���f�b�N�X�ԍ����w��
	void GetEneData(std::vector<std::map<std::string, int>>* eneIntDataMaps, 
		std::vector<std::vector<std::map<std::string, int>>>* eneAXYMapVecs,
		std::vector<std::map<std::string, bool>>* eneBoolDataMaps, bool* isExistings);	// Enemy�̃f�[�^��n�����߂Ɏg�p����
																									// isExistings��mEnemies�̊e�C���f�b�N�X�ԍ��ɂ�����NULL�łȂ����true
	void SetIsHits(const bool* const isHits);	// Player�̍U���Ƃ̓����蔻��̊m�F���ʂ�Map���󂯎��
	void SetPlDataMap(std::map<std::string, int>* plDataMap);	// Player��x, y, �U���͂��󂯎��
	void CreateEnemy();	// ���̊m����Enemy���o��������CEnemy�̎��������̂��߂Ɏg�p���CGameScene������̎����ŗ��p����
	//bool GetBossDead() const; //Boss�̗̑͂�0�ɂȂ�����true

private:
	const int ENEMY_NUM = 3;	// �Ǘ��ł���enemy�̐��CmEnemies�̗v�f��
	Enemy* mEnemies[3];
	EEnemy mEnesNext[3];	// �emEnemies�Ɏ��ɃZ�b�g����item�̎��
	int mEnesNextX[3];	// ���ɃZ�b�g����enemy�̍ŏ���x���W
	int mEnesNextY[3];	// ���ɃZ�b�g����enemy�̍ŏ���y���W
	const int ITEM_FIRST_Y_MIN = 290;	// enemy���������ꂽ�ۂ̍ŏ���y���W�̍ŏ��l
	const int ITEM_FIRST_Y_MAX = 610;	// enemy���������ꂽ�ۂ̍ŏ���y���W�̍ő�l
	int mPlX;	// Player��x���W�C�V����Enemy�̏o���̍��W�̌���Ŏg�p����

private:
	static EnemyMgr* mEnemyMgr;
};