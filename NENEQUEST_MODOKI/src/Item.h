#pragma once

#include "BasicFunc.h"
#include "ItemChanger.h"
#include <map>
#include <string>
#include <vector>

class ItemMgr;


class Item : public BasicFunc {
public:
	Item(ItemChanger* changer, const int* graph, const int itemIdx, const int x, const int y);
	virtual void Initialize() override {};
	virtual void Finalize() override {};
	virtual void Update() override;
	virtual void Draw() override;	
	void GetIteDataMap(std::map<std::string, float>* iteDataMap);	// Item�̃f�[�^��n�����߂Ɏg�p����
	void SetIsHits(std::vector<std::map<std::string, bool>>& isHitMap);	// Player�Ƃ̓����蔻��̊m�F���ʂ��󂯎��CmIsHitPl��mIsHitPlA�ɑ������

protected:
	virtual void Move();	// �ړ�
	//virtual void Jump();	// �W�����v�iItem12�`14�Ŏg�p����j
	//virtual void UpdateHit();	// �����蔻��̍X�V

	ItemChanger* mItemChanger;
	ItemMgr* mItemMgr;	// Enemy��Item�ȂǂƂ̓����蔻��Ȃǂ̏��̎擾�Ɏg�p����
	const int* mIteHandle;	// Item�̉摜
	int mItemIdx;	// �g�p���Ă���mItems�̃C���f�b�N�X�ԍ�
	int mItemId;	// ���g��Item��Id�iItem{}.cpp��{}�̕����j
	int mX, mY;	// item��x���W��y���W
	int mImgW, mImgH;	// item�̉摜�̉�(width)�A�c�̃T�C�Y(height)
	int mHitRangeW, mHitRangeH;	// item�̓����蔻��̒��S���W����͈̔�(width, height)
	float mSpeed;	// item�̈ړ����x
	int mHealPower;	// �񕜌n�̃A�C�e����0�ȊO�̒l�ɂȂ�
	float mSpeedPower;	// �������n�i�ړ����x�A�b�v�j�̃A�C�e����1�ȊO�̒l�ɂȂ�C���Ƃ̈ړ����x�Ɋ|�����킹��{��
	int mAttackPower;	// �������n�i�U���̓A�b�v�j�̃A�C�e����1�ȊO�̒l�ɂȂ�C���Ƃ̍U���͂Ɋ|�����킹��{��
	bool mPlIsHit;	// Player�Ƃ̓����蔻��C�������Ă���Ƃ�true
	bool mPlAIsHit;	// Player�̍U���Ƃ̓����蔻��C�������Ă���Ƃ���true
	const int ITEM_DELETE_X = -90;	// ���̍��W�܂�item���ړ������Ƃ��C�����I�ɏ����悤�ɂ���
	bool mIsChangingItem;	// Item���`�F���W���鏈����ChangeItem���Ăт���������true�ɂ���CPlayer��2�񔻒��^���Ȃ��悤�ɂ��邽�߂Ɏg�p����
	//std::map<std::string, int> mIteIntDataMap;	// x, y, hitRangeW, hitRangeH, healPower, speedPower, attackPower�Ȃǂ����Ă���map�C���̃N���X�ɓn���p

	//int type; //����Item�̍��W�̃p�^�[���̔ԍ�
	//bool plJudge; //Player�̍U���Ƃ̓����蔻��
};