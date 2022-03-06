#pragma once
/*
* GameScene�ɂ�����C�Q�[���I�[�o�[��ʂ̃N���X
* Player�̗̑͂�0�ɂȂ����Ƃ��ɕ\�������
*/
#include "BasicFunc.h"


class GameOver : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	void Move();	// GAMEOVER!���ꂼ��̕����̍��W�̍X�V�Ɏg��

	int mBackHandle;	// �w�i�摜
	const int LETTER_NUM = 9;	// GAMEOVER!�̕�����
	int mLetterHandles[9];	// GAMEOVER! ��9�����̉摜
	const int IMG_W = 170, IMG_H = 170;	// �����̉摜�̑傫��

	int mStrFontHandle;	// �u���j���[��ʂɖ߂�iEsc�L�[�������j�v�̕����̕\���Ɏg�p����t�H���g

	int mLetXs[9], mLetYs[9];	// GAME OVER!�̕������ꂼ��̍��W
	int mLetYsPrev[9];	// �����̈ړ��Ŏg��

	bool mLetIsMovings[9];	// ���ꂼ��̕������ړ������ǂ���
	bool mHasSetLetters;	// ���ꂼ��̕����̈ړ����I�������ǂ����C�I����Ă�����true
	int mMoveLetterId;	// �����n�߂����镶����id�C1���������ɓ����o������

	unsigned long long mFrameCnt;	// �o�߂����t���[�����̃J�E���g�C�e�����̓������߂Ɏg�p�����肷��
	const int FIRST_LETTER_STOP_FRAME_NUM = 30;	// �ŏ��̕����������n�߂�܂Ŏ~�܂��Ă��鎞��
	const int EACH_LETTERS_STOP_FRAME_NUM = 10;	// �e�������O�̕����������Ă���~�܂��Ă��鎞��
};