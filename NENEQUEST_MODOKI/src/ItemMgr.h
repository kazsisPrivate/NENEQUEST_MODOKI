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
	void Draw(const int itemIdx);	// 指定されたインデックス番号のmItemを描画
	void ChangeItem(const int itemIdx, EItem itemNext, 
		const int itemNextX, const int itemNextY) override;	// itemIdxは配列mItemのインデックス番号を指す
	void GetIteData(std::vector<std::map<std::string, float>>* iteIntDataMaps, 
		std::vector<std::map<std::string, float>>* iteBoolDataMaps, bool* isExistings);	// Itemのデータを渡すために使用する
																									// isExistingsはmItemsの各インデックス番号においてNULLでなければtrue
	void SetIsHitMaps(std::vector<std::map<std::string, bool>>& isHitMaps);	// Playerとの当たり判定の確認結果のMapを受け取る
	void CreateItem();	// 一定の確率でItemを出現させる，Itemの自動生成のために使用し，GameSceneから一定の周期で利用する

private:
	const int ITEM_NUM = 2;	// セットできるitemの数，mItemsの要素数
	Item* mItems[2];
	EItem mItesNext[2];	// 各mItemに次にセットするitemの種類
	int mItesNextX[2];	// 次にセットするitemの最初のx座標
	int mItesNextY[2];	// 次にセットするitemの最初のy座標
	const int ITEM_FIRST_X = 1400;	// itemが生成された際の最初のx座標（固定）
	const int ITEM_FIRST_Y_MIN = 290;	// itemが生成された際の最初のy座標の最小値
	const int ITEM_FIRST_Y_MAX = 610;	// itemが生成された際の最初のy座標の最大値
	//int itAppear[320];
	//const int ITEM_DELETE_FRAME_NUM = 320;	// itemを出現させてから，itemを削除するまでのフレーム数
	//int mItemsCnt[2];	// 各itemの出現を出現させてからのフレーム数
	bool mIsAtBsSt;	// bossStageに入っていればtrue

private:
	static ItemMgr* mItemMgr;
};