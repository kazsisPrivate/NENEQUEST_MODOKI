#include "TimeCounter.h"
#include "Dxlib.h"
#include "time.h"


void TimeCounter::Initialize() {
	// 時間の初期化
	mStartTime = 0;
	mEndTime = 0;

	// 表示に使用する画像の取得
	mTimeFrameHandle = LoadGraph("images/timeframe.png");

	// 使用するフォントの設定
	mTimeFontHandle = CreateFontToHandle("Broadway", 50, 3, -1);
}


void TimeCounter::Finalize() {
	// 画像の削除
	DeleteGraph(mTimeFrameHandle);

	// フォントの削除
	DeleteFontToHandle(mTimeFontHandle);
}


void TimeCounter::Update() {
	// 経過時間の更新
	mElapsedTime = (int)(clock() - mStartTime) / CLOCKS_PER_SEC;
}


void TimeCounter::Draw() {
	// 経過時間を表示する枠の描画
	DrawGraph(550, 40, mTimeFrameHandle, TRUE);

	// 経過時間の描画
	DrawFormatStringToHandle(563, 60, GetColor(0, 0, 0), mTimeFontHandle, "%03d", mElapsedTime);
}


void TimeCounter::StartTime() {
	mStartTime = clock();
}


void TimeCounter::StopTime() {
	mEndTime = clock();
}


int TimeCounter::GetClearTime() const {
	return (int)(mEndTime - mStartTime) / CLOCKS_PER_SEC;
}