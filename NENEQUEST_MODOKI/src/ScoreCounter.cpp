#include "ScoreCounter.h"
#include "DxLib.h"
#include <string>

void ScoreCounter::Initialize() {
	// 合計スコアの初期化
	mTotalScore = 0;
	mTotalScoreStr = "0";
	
	// スコアを表示する枠の画像の取得
	mScoreFrameHandle = LoadGraph("images/scoreframe.png");

	// 使用するフォントの取得
	mScoreFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mStrFontHandle = CreateFontToHandle("Ravie", 20, 5, DX_FONTTYPE_EDGE);

	// 文字列の合計スコアの横幅の初期化
	mTotalScoreStrW = GetDrawFormatStringWidthToHandle(mScoreFontHandle, "%d", mTotalScoreStr);
}


void ScoreCounter::Finalize() {
	// フォントの削除
	DeleteFontToHandle(mScoreFontHandle);
	DeleteFontToHandle(mStrFontHandle);
}


void ScoreCounter::Update() {
	// 文字列の合計スコアの更新
	mTotalScoreStr = std::to_string(mTotalScore);
	// 文字列の合計スコアの横幅の更新
	mTotalScoreStrW = GetDrawStringWidthToHandle(mTotalScoreStr.c_str(), mTotalScoreStr.length(), mScoreFontHandle);
}


void ScoreCounter::Draw() {	
	// スコアを表示する枠の描画
	DrawGraph(750, 40, mScoreFrameHandle, TRUE);

	// スコアの描画
	DrawFormatStringToHandle(SCORE_STR_RX - mTotalScoreStrW, 55, GetColor(0, 0, 0), mScoreFontHandle, "%d", mTotalScore);
	DrawFormatStringToHandle(770, 30, GetColor(255, 241, 15), mStrFontHandle, "SCORE");
}


unsigned long long ScoreCounter::GetTotalScore() const {
	return mTotalScore;
}

void ScoreCounter::AddScore(const int score) {
	mTotalScore += score;
}