#include "TimeCounter.h"
#include "Dxlib.h"
#include "time.h"


void TimeCounter::Initialize() {
	// ���Ԃ̏�����
	mStartTime = 0;
	mEndTime = 0;

	// �\���Ɏg�p����摜�̎擾
	mTimeFrameHandle = LoadGraph("images/timeframe.png");

	// �g�p����t�H���g�̐ݒ�
	mTimeFontHandle = CreateFontToHandle("Broadway", 50, 3, -1);
}


void TimeCounter::Finalize() {
	// �摜�̍폜
	DeleteGraph(mTimeFrameHandle);

	// �t�H���g�̍폜
	DeleteFontToHandle(mTimeFontHandle);
}


void TimeCounter::Update() {
	// �o�ߎ��Ԃ̍X�V
	mElapsedTime = (int)(clock() - mStartTime) / CLOCKS_PER_SEC;
}


void TimeCounter::Draw() {
	// �o�ߎ��Ԃ�\������g�̕`��
	DrawGraph(550, 40, mTimeFrameHandle, TRUE);

	// �o�ߎ��Ԃ̕`��
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