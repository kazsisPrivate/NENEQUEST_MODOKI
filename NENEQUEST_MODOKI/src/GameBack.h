#pragma once
/*
* GameSceneにおける，背景のクラス
*/
#include "BasicFunc.h"

class GameBack : BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void UpdateNormalBack();	// BossStageに入るまでの背景の更新処理
	void UpdateBossBack();	// BossStageに入った後の背景の更新処理
	void StartChangingSt();	// BossStageへの移行を始める際の処理，GameScene側から呼びだす
	int GetBsStX();	// BossStageのx座標を返す，EnemyBossの作成の際(BossStageへの移行を始める際)にGameScene側から呼びだす
	bool GetIsAtBsSt();	// BossStageに入ったかどうかを返す

private:
	const int STAGE_IMG_W = 1280, STAGE_IMG_H = 720;	// NormalStageとBackStageの画像のサイズ
	int mNorStHandles[2];	// NormalStageの画像
	int mCloudHandles[2];	// 雲の画像
	int mBsStHandle; // BossStageの画像

	const int BACK_X_MIN = -1280, BACK_X_MAX = 1280;	// 背景画像の移動範囲の左端と右端のx座標
	int mNorStXs[2];	// 各NormalStageの画像の左端のx座標
	float mCloudXs[2];	// 各雲の画像の左端のx座標
	int mBsStX;	// BossStageの画像の左端のx座標
	const int BRIDGE_LX = 690;	// BossStageの背景画像内の橋の左端のx座標

	bool mIsChangingSt;	// BossStageへ変更中であったらtrue
	bool mIsMovingNorSts[2];	// BossStageへの変更中のとき，各NormalStageを動かしているときtrue
	bool mIsAtBsSt;	// BossStageにいたらtrue

	int mStrFontHandle;	// BossStageへの移行中に"!BossStage!"という表示をする際に使用するフォント
};