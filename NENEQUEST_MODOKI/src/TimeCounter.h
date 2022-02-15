#pragma once

// �o�ߎ��Ԃ�\�����邽�߂̃N���X
#include "time.h" 
#include "BasicFunc.h"


class TimeCounter : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override {};
	void Update() override;
	void Draw() override;
	int GetClearTime() const;	// Game�̃N���A���Ԃ�Ԃ�
	void StartTime();	// �^�C�}�[���J�n����i�Q�[���X�^�[�g���j
	void StopTime();	// �^�C�}�[���~�߂�i�Q�[���N���A���j

private:
	int mTimeFrameHandle;	// ���Ԃ�\������g�̉摜
	int mTimeFontHandle;	// �o�ߎ��Ԃ�\������̂Ɏg�p����t�H���g
	clock_t mStartTime;
	clock_t mEndTime;
	int mElapsedTime;	// �X�^�[�g���Ă���̌o�ߎ��ԁi�b�P�ʂŊǗ��C999�b�ȏ��999�ƕ\������j
};