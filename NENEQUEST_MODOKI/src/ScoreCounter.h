#pragma once

// 取得したスコアを表示するためのクラス
#include "BasicFunc.h"
#include <string>


class ScoreCounter : BasicFunc {
public:
	void Initialize() override;
	void Finalize() override {};
	void Update() override;
	void Draw() override;
	int GetTotalScore() const;
	void AddScore(const int score);

private:
	int mScoreFrameHandle;	// スコアを表示する枠の画像
	int mScoreFontHandle;	// スコアを表示するのに使用するフォント
	int mStrFontHandle;	// "Score"という文字列を表示するのに使用するフォント
	const int SCORE_STR_RX = 1150;	// スコアを表示する際の，スコアの文字列の右端のx座標，文字列の右寄せで使用する 	
	int mTotalScore;	// 合計スコア
	std::string mTotalScoreStr;	// 描画する用の文字列の合計スコア
	int mTotalScoreStrW;	// 描画する際の文字列の合計スコアの横幅
};