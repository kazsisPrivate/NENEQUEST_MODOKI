#pragma once
/*
* メニュー画面（GameScene）のクラス
*/
#include "BaseScene.h"
#include "UpdateKey.h"
#include "SceneChanger.h"
#include <string>


class MenuScene : public BaseScene, UpdateKey {
public :
	MenuScene(SceneChanger* changer);
	static MenuScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	int mTitleFontHandle;	// タイトルの文字のフォント
	int mOptionFontHandle;	// 選択肢の文字フォント

	std::string mTitleStrs[2];
	int mTitleXs[2];// = { 100, 300 };	// タイトルの文字のx座標
	int mTitleYs[2];// = { 30, 150};	// タイトルの文字のy座標
	int mTriY;	// 選択に使用する三角形の中心のy座標
	const int TRI_YS[3] = { 525, 590, 655 };
	int mTriYId = 0;

private:
	static MenuScene* mMenuScene;
};