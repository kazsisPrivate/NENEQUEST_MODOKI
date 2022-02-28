#include "GameClear.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


void GameClear::Initialize() {
	// ��ʂɕ\������摜�̎擾
	mPlFaceHandle = LoadGraph("images/playerface.png");

	// �����̕\���Ɏg�p����t�H���g�̎擾
	mScoStrFontHandle = CreateFontToHandle("MS �S�V�b�N", 40, 2, DX_FONTTYPE_EDGE, -1, 4);
	mGameScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mTimeScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 60, 1, -1);
	mTotalScoFontHandle = CreateFontToHandle("SHOWCARD GOTHIC", 120, 1, -1);
	mPTotalScoFontHandle = CreateFontToHandle("MS �S�V�b�N", 50, 2);
	mEscStrFontHandle = CreateFontToHandle("HG�n�p�p�S�V�b�NUB �W��", 40, 1, -1);

	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		mIsRankedIn[i] = false;
	}
	
	mFrameCnt = 0;
}


void GameClear::Finalize() {
	// �摜�̍폜
	DeleteGraph(mPlFaceHandle);

	// �t�H���g�̍폜
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
	// ��ʉE��ɕ\������Player�̊�i����j
	DrawGraph(1050, 20, mPlFaceHandle, TRUE);
	DrawGraph(950, 200, mPlFaceHandle, TRUE);
	DrawGraph(1150, 200, mPlFaceHandle, TRUE);

	// �Q�[���ŃA�C�e����G���瓾���X�R�A�̕\��
	if (mFrameCnt >= DISP_FRAME_NUMS[0]) {
		DrawFormatStringToHandle(mGameScoreX, mGameScoreY, GetColor(0, 0, 0), mGameScoFontHandle, mGameScore.c_str());
		DrawStringToHandle(100, mGameScoreY - 50, "GameScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// �Q�[���ł̌o�ߎ��Ԃ����Ƃɂ��ē���X�R�A�̕\��
	if (mFrameCnt >= DISP_FRAME_NUMS[1]) {
		DrawFormatStringToHandle(mTimeScoreX, mTimeScoreY, GetColor(0, 0, 0), mTimeScoFontHandle, mTimeScore.c_str());
		DrawStringToHandle(500, mTimeScoreY - 50, "TimeScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// ���v�X�R�A�̕\��
	if (mFrameCnt >= DISP_FRAME_NUMS[2]) {
		DrawFormatStringToHandle(mTotalScoreX, mTotalScoreY, GetColor(0, 0, 0), mTotalScoFontHandle, mTotalScore.c_str());
		DrawStringToHandle(300, mTotalScoreY - 50, "TotalScore", GetColor(0, 128, 128), mScoStrFontHandle, GetColor(105, 105, 105));
	}

	// �ߋ��̏��3�ʂ܂ł̍��v�X�R�A�̕\��
	if (mFrameCnt >= DISP_FRAME_NUMS[3]) {
		for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
			int strColor;
			if (mIsRankedIn[i]) {	// ����̃X�R�A�������N�C�����Ă���
				// �ԐF
				strColor = GetColor(255, 0, 0);
			}
			else {
				// ���F
				strColor = GetColor(0, 0, 0);
			}

			std::string rankStr = std::to_string(i + 1) + ": ";
			DrawFormatStringToHandle(450, mPTotalScoreYs[i], strColor, mPTotalScoFontHandle, rankStr.c_str());
			DrawFormatStringToHandle(mPTotalScoreXs[i], mPTotalScoreYs[i], strColor, mPTotalScoFontHandle, mPastTotalScores[i].c_str());
			
		}
		DrawStringToHandle(250, mPTotalScoreYs[0] - 50, "Ranking", GetColor(204, 0, 0), mScoStrFontHandle, GetColor(105, 105, 105));
		DrawFormatStringToHandle(320, 650, GetColor(0, 0, 0), mEscStrFontHandle, "���j���[��ʂɖ߂�iEsc�L�[�������j");
	}
}


void GameClear::SetScores(const unsigned long long gameScore, const unsigned long long timeScore) {
	mGameScore = std::to_string(gameScore);
	mTimeScore = std::to_string(timeScore);
	unsigned long long totalScore = gameScore + timeScore;
	mTotalScore = std::to_string(totalScore);

	// �ߋ��̏��3�ʂ܂ł̍��v�X�R�A��ǂ݂���
	std::ifstream readingFile;
	readingFile.open("score_ranking.txt", std::ios::in | std::ios::binary);
	if (!readingFile) {	// �t�@�C�����Ȃ�������
		// �t�@�C�����쐬����
		std::ofstream tmpFile("score_ranking.txt", std::ios::out | std::ios::binary);
		for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
			tmpFile << "0" << std::endl;
		}
		//tmpFile.close();

		// �쐬�����t�@�C�����J��
		readingFile.open("score_ranking.txt", std::ios::in | std::ios::binary);
	}

	// �t�@�C������ߋ��̏��3�ʂ̍��v�X�R�A��ǂݍ���
	std::string line;
	unsigned long long pastTotalScores[3];
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		std::getline(readingFile, line);
		pastTotalScores[i] = atoi(line.c_str());
	}
	readingFile.close();

	// �ŐV�̃X�R�A���ߋ��̃����L���O�ɓo�^����
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		if (pastTotalScores[i] <= totalScore) {	// �ߋ��̃X�R�A�𒴂��Ă�����
			// �ߋ��̃X�R�A���X�V����
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

	// �t�@�C���ɍX�V��̃����L���O����������
	std::ofstream writingFile("score_ranking.txt", std::ios::out | std::ios::binary);
	for (int i = 0; i < PAST_TOTAL_SCORE_NUM; i++) {
		writingFile << mPastTotalScores[i] << std::endl;
	}

	// ���ꂼ��̃X�R�A�̕\���ʒu�����߂�
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