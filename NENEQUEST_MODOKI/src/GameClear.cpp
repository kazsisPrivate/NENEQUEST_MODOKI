#include "GameClear.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void GameClear::Initialize() {
	// 画面に表示する画像の取得
	mPlFaceHandle = LoadGraph("images/playerface.png");

	// 文字の表示に使用するフォントの取得
	mScoStrFontHandle = CreateFontToHandle("MS ゴシック", 40, 2, DX_FONTTYPE_EDGE, -1, 4);
	mGameScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mTimeScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mTotalScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 120, 1, -1);
	mPTotalScoFontHandle = CreateFontToHandle("MS ゴシック", 50, 2);
	mEscStrFontHandle = CreateFontToHandle("HG創英角ゴシックUB 標準", 40, 1, -1);

	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		mIsRankedIn[i] = false;
	}
	
	mFrameCnt = 0;
}


void GameClear::Finalize() {
	// 画像の削除
	DeleteGraph(mPlFaceHandle);

	// フォントの削除
	DeleteFontToHandle(mScoStrFontHandle);
	DeleteFontToHandle(mGameScoFontHandle);
	DeleteFontToHandle(mTimeScoFontHandle);
	DeleteFontToHandle(mTotalScoFontHandle);
	DeleteFontToHandle(mPTotalScoFontHandle);
	DeleteFontToHandle(mEscStrFontHandle);
}


void GameClear::Update() {
	mFrameCnt++;
}


void GameClear::Draw() {
	// 画面右上に表示するPlayerの顔（飾り）
	DrawGraph(1050, 20, mPlFaceHandle, TRUE);
	DrawGraph(950, 200, mPlFaceHandle, TRUE);
	DrawGraph(1150, 200, mPlFaceHandle, TRUE);

	// ゲームでアイテムや敵から得たスコアの表示
	if (mFrameCnt >= DISP_FRAME_NUMS[0]) {
		DrawFormatStringToHandle(mGameScoreX, mGameScoreY, GetColor(0, 0, 0), mGameScoFontHandle, mGameScore.c_str());
		DrawStringToHandle(100, mGameScoreY - 50, "GameScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// ゲームでの経過時間をもとにして得るスコアの表示
	if (mFrameCnt >= DISP_FRAME_NUMS[1]) {
		DrawFormatStringToHandle(mTimeScoreX, mTimeScoreY, GetColor(0, 0, 0), mTimeScoFontHandle, mTimeScore.c_str());
		DrawStringToHandle(500, mTimeScoreY - 50, "TimeScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// 合計スコアの表示
	if (mFrameCnt >= DISP_FRAME_NUMS[2]) {
		DrawFormatStringToHandle(mTotalScoreX, mTotalScoreY, GetColor(0, 0, 0), mTotalScoFontHandle, mTotalScore.c_str());
		DrawStringToHandle(300, mTotalScoreY - 50, "TotalScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// 過去の上位3位までの合計スコアの表示
	if (mFrameCnt >= DISP_FRAME_NUMS[3]) {
		for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
			int strColor;
			if (mIsRankedIn[i]) {	// 今回のスコアがランクインしてたら
				// 赤色
				strColor = GetColor(255, 0, 0);
			}
			else {
				// 黒色
				strColor = GetColor(0, 0, 0);
			}

			std::string rankStr = std::to_string(i + 1) + ": ";
			DrawFormatStringToHandle(450, mPTotalScoreYs[i], strColor, mPTotalScoFontHandle, rankStr.c_str());
			DrawFormatStringToHandle(mPTotalScoreXs[i], mPTotalScoreYs[i], strColor, mPTotalScoFontHandle, mPastTotalScores[i].c_str());
			
		}
		DrawStringToHandle(250, mPTotalScoreYs[0] - 50, "Ranking", GetColor(204, 0, 0), mScoStrFontHandle, GetColor(105, 105, 105));
		DrawFormatStringToHandle(320, 650, GetColor(0, 0, 0), mEscStrFontHandle, "メニュー画面に戻る（Escキーを押す）");
	}
}


void GameClear::SetScores(const unsigned long long gameScore, const unsigned long long timeScore) {
	mGameScore = std::to_string(gameScore);
	mTimeScore = std::to_string(timeScore);
	unsigned long long totalScore = gameScore + timeScore;
	mTotalScore = std::to_string(totalScore);

	// 過去の上位3位までの合計スコアを読みだす
	std::ifstream readingFile;
	readingFile.open("score_ranking.txt", std::ios::in | std::ios::binary);
	if (!readingFile) {	// ファイルがなかったら
		// ファイルを作成する
		std::ofstream tmpFile("score_ranking.txt", std::ios::out | std::ios::binary);
		for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
			tmpFile << "0" << std::endl;
		}
		//tmpFile.close();

		// 作成したファイルを開く
		readingFile.open("score_ranking.txt", std::ios::in | std::ios::binary);
	}

	// ファイルから過去の上位3位の合計スコアを読み込む
	std::string line;
	unsigned long long pastTotalScores[3];
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		std::getline(readingFile, line);
		pastTotalScores[i] = atoi(line.c_str());
	}
	readingFile.close();

	// 最新のスコアを過去のランキングに登録する
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		if (pastTotalScores[i] <= totalScore) {	// 過去のスコアを超えていたら
			// 過去のスコアを更新する
			unsigned long long updatedPTotalScores[3];
			for (int j = 0; j < i; j++) {
				updatedPTotalScores[j] = pastTotalScores[j];
			}

			updatedPTotalScores[i] = totalScore;

			for (int j = i + 1; j < PAST_TOTAL_SCORE_NUM; j++) {
				updatedPTotalScores[j] = pastTotalScores[j - 1];
			}

			for (int j = 0; j < PAST_TOTAL_SCORE_NUM; j++) {
				pastTotalScores[j] = updatedPTotalScores[j];
			}
			
			mIsRankedIn[i] = true;

			break;
		}
	}

	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		mPastTotalScores[i] = std::to_string(pastTotalScores[i]);
	}

	// ファイルに更新後のランキングを書き込む
	std::ofstream writingFile("score_ranking.txt", std::ios::out | std::ios::binary);
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		writingFile << mPastTotalScores[i] << std::endl;
	}

	// それぞれのスコアの表示位置を求める
	// mGameScore
	int gameScoreW = GetDrawStringWidthToHandle(mGameScore.c_str(), mGameScore.length(), mGameScoFontHandle);
	mGameScoreX = GAME_SCORE_RX - gameScoreW;
	mGameScoreY = 70;
	// mTimeScore
	int timeScoreW = GetDrawStringWidthToHandle(mTimeScore.c_str(), mTimeScore.length(), mTimeScoFontHandle);
	mTimeScoreX = TIME_SCORE_RX - timeScoreW;
	mTimeScoreY = mGameScoreY;
	// mTotalScore
	int screenW, screenH;
	GetWindowSize(&screenW, &screenH);
	mTotalScoreX = (screenW - GetDrawStringWidthToHandle(mTotalScore.c_str(), mTotalScore.length(), mTotalScoFontHandle)) / 2;
	mTotalScoreY = mGameScoreY + GetFontSizeToHandle(mGameScoFontHandle) + 100;
	// mPastTotalScores
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		int pastTotalScoreW = GetDrawStringWidthToHandle(mPastTotalScores[i].c_str(), mPastTotalScores[i].length(), mPTotalScoFontHandle);
		mPTotalScoreXs[i] = PAST_TOTAL_SCORES_RX - pastTotalScoreW;
		mPTotalScoreYs[i] = mTotalScoreY + GetFontSizeToHandle(mTotalScoFontHandle) + 90 + (GetFontSizeToHandle(mPTotalScoFontHandle) + 15) * i;
	}
}