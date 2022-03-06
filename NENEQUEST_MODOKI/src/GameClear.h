#pragma once
/*
* GameScene�ɂ�����C�Q�[���N���A��ʂ̃N���X
* �{�X�iEnemyBoss�j��|�����Ƃ��ɂɂȂ����Ƃ��ɕ\�������
*/
#include "BasicFunc.h"
#include <string>


class GameClear : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void SetScores(const unsigned long long gameScore, const unsigned long long timeScore);	// EnemyBoss��|�����Ƃ��ɌĂ΂��C�\������X�R�A���Z�b�g����

private:
	std::string mGameScore;	// �Q�[���ŃA�C�e����G���瓾���X�R�A
	std::string mTimeScore;	// �Q�[���ł̌o�ߎ��Ԃ����Ƃɂ��ē���X�R�A
	std::string mTotalScore;	// ���v�X�R�A
	const int PAST_TOTAL_SCORE_NUM = 3;	// �\������ߋ��̃X�R�A�̐�
	std::string mPastTotalScores[3];	// �ߋ��̏��3�ʂ܂ł̍��v�X�R�A

	int mGameScoreX, mGameScoreY;	// �Q�[���ŃA�C�e����G���瓾���X�R�A��\������xy���W
	int mTimeScoreX, mTimeScoreY;	// �Q�[���ł̌o�ߎ��Ԃ����Ƃɂ��ē���X�R�A��\������xy���W
	int mTotalScoreX, mTotalScoreY;	// ���v�X�R�A��\������xy���W
	int mPTotalScoreXs[3], mPTotalScoreYs[3];	// �ߋ��̏��3�ʂ܂ł̍��v�X�R�A��\������xy���W
	const int GAME_SCORE_RX = 400;	// mGameScore�̕\���ʒu�̉E�[
	const int TIME_SCORE_RX = 800;	// mTimeScore�̕\���ʒu�̉E�[
	const int PAST_TOTAL_SCORES_RX = 900;	// mPastTotalScore�̕\���ʒu�̉E�[

	int mScoStrFontHandle;	// �����̕\���Ɏg�p����t�H���g
	int mGameScoFontHandle;	// �Q�[���ŃA�C�e����G���瓾���X�R�A�̕\���Ɏg�p����t�H���g
	int mTimeScoFontHandle;	// �Q�[���ł̌o�ߎ��Ԃ����Ƃɂ��ē���X�R�A�̕\���Ɏg�p����t�H���g
	int mTotalScoFontHandle;	// ���v�X�R�A�̕\���Ɏg�p����t�H���g
	int mPTotalScoFontHandle;	// �ߋ��̏��3�ʂ܂ł̍��v�X�R�A�̕\���Ɏg�p����t�H���g
	int mEscStrFontHandle;	// "Esc�L�[�Ń��j���[�ɖ߂�"��\������̂Ɏg�p����t�H���g

	unsigned long long mFrameCnt;	// �o�߂����t���[����
	int DISP_FRAME_NUMS[4] = { 30, 60, 90, 120 };	// �e�X�R�A�̕\�����n�߂�t���[����
	bool mIsRankedIn[3];	// ���3�ʈȓ��ɓ����Ă�����C���̓����������N�̗v�f��true�ɂȂ�

	int mPlFaceHandle;	// ��ʂɕ\������Player�̊�̉摜
};