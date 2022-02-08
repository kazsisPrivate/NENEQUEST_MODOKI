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
	void Draw() override;
	//void Draw(const int itemIdx);	// 指定されてインデックス番号のmItemを描画
	void ChangeItem(const int itemIdx, EItem itemNext, 
		const int itemNextX, const int itemNextY) override;	// itemIdxは配列mItemのインデックス番号を指す
	void GetIteDataMaps(std::vector<std::map<std::string, float>>* iteDataMaps, bool* isExistings);	// Itemのデータを渡すために使用する, isExistingsはmItemsの各インデックス番号においてNULLでなければtrue
	void SetIsHitMaps(std::vector<std::map<std::string, bool>>& isHitMaps);	// Playerとの当たり判定の確認結果のMapを受け取る
	//int nItNum0; //Bossとのやり取りのみで使用する

private:
	const int ITEM_NUM = 2;	// 保持できるitemの数，mItemsの要素数
	Item* mItems[2];
	EItem mItemsNext[2];	// 各mItemに次にセットするitemの種類
	int mItemNextX[2];	// 次にセットするitemの最初のx座標
	int mItemNextY[2];	// 次にセットするitemの最初のy座標
	//int itAppear[320];
	//const int ITEM_DELETE_FRAME_NUM = 320;	// itemを出現させてから，itemを削除するまでのフレーム数
	//int mItemsCnt[2];	// 各itemの出現を出現させてからのフレーム数
	bool mIsAtBsSt;	// bossStageに入っていればtrue

private:
	static ItemMgr* mItemMgr;
};