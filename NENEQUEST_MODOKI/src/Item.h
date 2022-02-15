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
	void GetIteDataMap(std::map<std::string, float>* iteIntDataMap, std::map<std::string, float>* iteBoolDataMap);	// Itemのデータを渡すために使用する
	void SetIsHits(std::vector<std::map<std::string, bool>>& isHitMap);	// Playerとの当たり判定の確認結果を受け取り，mIsHitPlとmIsHitPlAに代入する

protected:
	virtual void Move();	// 移動
	//virtual void Jump();	// ジャンプ（Item12～14で使用する）
	//virtual void UpdateHit();	// 当たり判定の更新

	ItemChanger* mItemChanger;
	ItemMgr* mItemMgr;	// EnemyやItemなどとの当たり判定などの情報の取得に使用する
	const int* mIteHandle;	// Itemの画像
	int mItemIdx;	// 使用しているmItemsのインデックス番号
	int mItemId;	// 自身のItemのId（Item{}.cppの{}の部分）
	int mX, mY;	// itemのx座標とy座標
	int mImgW, mImgH;	// itemの画像の横(width)、縦のサイズ(height)
	int mHitRangeW, mHitRangeH;	// itemの当たり判定の中心座標からの範囲(width, height)
	int mScore;	// Playerが取得した際に得ることができるスコア
	float mSpeed;	// itemの移動速度
	int mHealPower;	// 回復系のアイテムは0以外の値になる
	float mSpeedPower;	// 自強化系（移動速度アップ）のアイテムは1以外の値になる，もとの移動速度に掛け合わせる倍率
	int mAttackPower;	// 自強化系（攻撃力アップ）のアイテムは1以外の値になる，もとの攻撃力に掛け合わせる倍率
	bool mPlIsHit;	// Playerとの当たり判定，当たっているときtrue
	bool mPlAIsHit;	// Playerの攻撃との当たり判定，当たっているときはtrue
	const int ITEM_DELETE_X = -90;	// この座標までitemが移動したとき，自動的に消すようにする
	bool mIsDead;	// ItemがPlayerに取得されたときにtrueになる

	//int type; //そのItemの座標のパターンの番号
	//bool plJudge; //Playerの攻撃との当たり判定
};