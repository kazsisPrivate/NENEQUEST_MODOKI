#pragma once

#include "ItemChanger.h"
#include "BasicFunc.h"
#include <map>
#include <string>
#include <vector>


class Item;


class ItemMgr : public ItemChanger, BasicFunc {
public:
	static ItemMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {};
	void Draw(const int itemIdx);	// �w�肳�ꂽ�C���f�b�N�X�ԍ���mItem��`��
	void ChangeItem(const int itemIdx, EItem itemNext, 
		const int itemNextX, const int itemNextY) override;	// itemIdx�͔z��mItem�̃C���f�b�N�X�ԍ����w��
	void GetIteData(std::vector<std::map<std::string, float>>* iteIntDataMaps, 
		std::vector<std::map<std::string, float>>* iteBoolDataMaps, bool* isExistings);	// Item�̃f�[�^��n�����߂Ɏg�p����
																									// isExistings��mItems�̊e�C���f�b�N�X�ԍ��ɂ�����NULL�łȂ����true
	void SetIsHitMaps(std::vector<std::map<std::string, bool>>& isHitMaps);	// Player�Ƃ̓����蔻��̊m�F���ʂ�Map���󂯎��
	void CreateItem();	// ���̊m����Item���o��������CItem�̎��������̂��߂Ɏg�p���CGameScene������̎����ŗ��p����

private:
	const int ITEM_NUM = 2;	// �Z�b�g�ł���item�̐��CmItems�̗v�f��
	Item* mItems[2];
	EItem mItesNext[2];	// �emItem�Ɏ��ɃZ�b�g����item�̎��
	int mItesNextX[2];	// ���ɃZ�b�g����item�̍ŏ���x���W
	int mItesNextY[2];	// ���ɃZ�b�g����item�̍ŏ���y���W
	const int ITEM_FIRST_X = 1400;	// item���������ꂽ�ۂ̍ŏ���x���W�i�Œ�j
	const int ITEM_FIRST_Y_MIN = 290;	// item���������ꂽ�ۂ̍ŏ���y���W�̍ŏ��l
	const int ITEM_FIRST_Y_MAX = 610;	// item���������ꂽ�ۂ̍ŏ���y���W�̍ő�l
	//int itAppear[320];
	//const int ITEM_DELETE_FRAME_NUM = 320;	// item���o�������Ă���Citem���폜����܂ł̃t���[����
	//int mItemsCnt[2];	// �eitem�̏o�����o�������Ă���̃t���[����
	bool mIsAtBsSt;	// bossStage�ɓ����Ă����true

private:
	static ItemMgr* mItemMgr;
};