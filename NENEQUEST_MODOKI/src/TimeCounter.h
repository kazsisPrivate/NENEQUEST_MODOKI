#pragma once

// 経過時間を表示するためのクラス
#include "time.h" 
#include "BasicFunc.h"


class TimeCounter : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override {};
	void Update() override;
	void Draw() override;
	int GetClearTime() const;	// Gameのクリア時間を返す
	void StartTime();	// タイマーを開始する（ゲームスタート時）
	void StopTime();	// タイマーを止める（ゲームクリア時）

private:
	int mTimeFrameHandle;	// 時間を表示する枠の画像
	int mTimeFontHandle;	// 経過時間を表示するのに使用するフォント
	clock_t mStartTime;
	clock_t mEndTime;
	int mElapsedTime;	// スタートしてからの経過時間（秒単位で管理，999秒以上は999と表示する）
};