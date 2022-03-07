#pragma once
/*
* GameSceneにおける，ゲームクリア画面のクラス
* ボス（EnemyBoss）を倒したときにになったときに表示される
*/
#include "BasicFunc.h"
#include <string>


class GameClear : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void SetScores(const unsigned long long gameScore, const unsigned long long timeScore);	// EnemyBossを倒したときに呼ばれる，表示するスコアをセットする

private:
	std::string mGameScore;	// ゲームでアイテムや敵から得たスコア
	std::string mTimeScore;	// ゲームでの経過時間をもとにして得るスコア
	std::string mTotalScore;	// 合計スコア
	const int PAST_TOTAL_SCORE_NUM = 3;	// 表示する過去のスコアの数
	std::string mPastTotalScores[3];	// 過去の上位3位までの合計スコア

	int mGameScoreX, mGameScoreY;	// ゲームでアイテムや敵から得たスコアを表示するxy座標
	int mTimeScoreX, mTimeScoreY;	// ゲームでの経過時間をもとにして得るスコアを表示するxy座標
	int mTotalScoreX, mTotalScoreY;	// 合計スコアを表示するxy座標
	int mPTotalScoreXs[3], mPTotalScoreYs[3];	// 過去の上位3位までの合計スコアを表示するxy座標
	const int GAME_SCORE_RX = 400;	// mGameScoreの表示位置の右端
	const int TIME_SCORE_RX = 800;	// mTimeScoreの表示位置の右端
	const int PAST_TOTAL_SCORES_RX = 900;	// mPastTotalScoreの表示位置の右端

	int mScoStrFontHandle;	// 文字の表示に使用するフォント
	int mGameScoFontHandle;	// ゲームでアイテムや敵から得たスコアの表示に使用するフォント
	int mTimeScoFontHandle;	// ゲームでの経過時間をもとにして得るスコアの表示に使用するフォント
	int mTotalScoFontHandle;	// 合計スコアの表示に使用するフォント
	int mPTotalScoFontHandle;	// 過去の上位3位までの合計スコアの表示に使用するフォント
	int mEscStrFontHandle;	// "Escキーでメニューに戻る"を表示するのに使用するフォント

	unsigned long long mFrameCnt;	// 経過したフレーム数
	int DISP_FRAME_NUMS[4] = { 30, 60, 90, 120 };	// 各スコアの表示を始めるフレーム数
	bool mIsRankedIn[3];	// 上位3位以内に入っていたら，その入ったランクの要素がtrueになる

	int mPlFaceHandle;	// 画面に表示するPlayerの顔の画像
};