#pragma once

#include "BasicFunc.h"

class GameBack : BasicFunc {
public:
	GameBack();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void UpdateNormal();	// bossに入るまでの背景の更新処理
	void UpdateBoss();	//bossに入った後の背景の更新処理

private:
	const int END_LEFT_X = -1280, END_RIGHT_X = 1280;
	int mMo1Handle, mMo2Handle;	// 山の画像
	int mCl1Handle, mCl2Handle;	// 雲の画像
	int mBoStHandle; // bossStageの画像
	int mMountain1X, mMountain2X;	// 山の画像の左端のx座標
	float mClouds1X, mClouds2X;	// 雲の画像の左端のx座標
	int mBoStX;	// bossStageの画像の左端のx座標
	const int UPDATE_FRAME_NUM = 3;	// 更新を行うタイミング（UPDATE_CNT_NUMが2ならば2フレーム毎に更新する）
	int mUpdFraCnt;	// 更新フレーム数のカウント，UPDATE_FRAME_NUMになったら0に戻る
	int mBackChCnt; //景色が入れ替わった回数、つまりmountainHandleが-1280に到達するごとに1増えていく、ボスバトルに入ったときの景色の変更、playerにボスバトルに入ったというのを知らせるのに使う
	bool mIsBossStage; //bossStageに入ったときtrueになる
};