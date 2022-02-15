#pragma once

// �擾�����X�R�A��\�����邽�߂̃N���X
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
	int mScoreFrameHandle;	// �X�R�A��\������g�̉摜
	int mScoreFontHandle;	// �X�R�A��\������̂Ɏg�p����t�H���g
	int mStrFontHandle;	// "Score"�Ƃ����������\������̂Ɏg�p����t�H���g
	const int SCORE_STR_RX = 1150;	// �X�R�A��\������ۂ́C�X�R�A�̕�����̉E�[��x���W�C������̉E�񂹂Ŏg�p���� 	
	int mTotalScore;	// ���v�X�R�A
	std::string mTotalScoreStr;	// �`�悷��p�̕�����̍��v�X�R�A
	int mTotalScoreStrW;	// �`�悷��ۂ̕�����̍��v�X�R�A�̉���
};