#pragma once
/*
* 操作説明画面のクラス
*/
#include "BaseScene.h"


class ConfigScene : public BaseScene {
public :
	ConfigScene(SceneChanger* changer);
	static ConfigScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	int* mPlHandle;	// Playerの画像
	int *mEneHandles[2];	// Enemyの画像
	int *mWeaHandles[2];	// 武器の画像
	int *mIteHandles[3];	// Itemの画像
	int* mIteBHandles[2];	// ItemBoxの画像

	int mPlX, mPlY;	// Playerの画像のxy座標
	int mEneXs[2], mEneYs[2];	// Enemyの画像のxy座標
	int mWeaXs[2], mWeaYs[2];	// 武器の画像のxy座標
	int mIteXs[3], mIteYs[3];	// Itemの画像のxy座標
	int mIteBXs[3], mIteBYs[3];	// ItemBoxの画像のxy座標

	int mExpStrFontHandles[2];	// 説明文に使用するフォント
	int mEscStrFontHandle;	// "メニュー画面に戻る（Escキーを押す）"の文字のフォント

private:
	static ConfigScene* mConfigScene;
};