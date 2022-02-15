#include "ScoreCounter.h"
#include "DxLib.h"
#include <string>

void ScoreCounter::Initialize() {
	// ���v�X�R�A�̏�����
	mTotalScore = 0;
	mTotalScoreStr = "0";
	
	// �X�R�A��\������g�̉摜�̎擾
	mScoreFrameHandle = LoadGraph("images/scoreframe.png");

	// �g�p����t�H���g�̎擾
	mScoreFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mStrFontHandle = CreateFontToHandle("Ravie", 20, 5, DX_FONTTYPE_EDGE);

	// ������̍��v�X�R�A�̉����̏�����
	mTotalScoreStrW = GetDrawFormatStringWidthToHandle(mScoreFontHandle, "%d", mTotalScoreStr);
}


void ScoreCounter::Update() {
	// ������̍��v�X�R�A�̍X�V
	mTotalScoreStr = std::to_string(mTotalScore);
	// ������̍��v�X�R�A�̉����̍X�V
	mTotalScoreStrW = GetDrawStringWidthToHandle(mTotalScoreStr.c_str(), mTotalScoreStr.length(), mScoreFontHandle);
}


void ScoreCounter::Draw() {	
	// �X�R�A��\������g�̕`��
	DrawGraph(750, 40, mScoreFrameHandle, TRUE);

	// �X�R�A�̕`��
	DrawFormatStringToHandle(SCORE_STR_RX - mTotalScoreStrW, 55, GetColor(0, 0, 0), mScoreFontHandle, "%d", mTotalScore);
	DrawFormatStringToHandle(SCORE_STR_RX, 205, GetColor(0, 0, 0), mScoreFontHandle, "%d", mTotalScoreStrW);
}


int ScoreCounter::GetTotalScore() const {
	return mTotalScore;
}

void ScoreCounter::AddScore(const int score) {
	mTotalScore += score;
}