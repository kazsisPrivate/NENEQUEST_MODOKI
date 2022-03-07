#include "GameOver.h"
#include "DxLib.h"


void GameOver::Initialize() {
	// �w�i�摜�̓ǂݍ���
	mBackHandle = LoadGraph("images/gameoverback.png");
	// GAMEOVER!�̕����̉摜�̓ǂݍ���
	LoadDivGraph("images/gameoverletters.png", 9, 1, 9, IMG_W, IMG_H, mLetterHandles);

	// �����̕\���Ɏg�p����t�H���g�̎擾
	mStrFontHandle = CreateFontToHandle("HG�n�p�p�S�V�b�NUB �W��", 40, 1, -1);

	// GAMEOVER!�̂��ꂼ��̕����̍��W�̐ݒ�
	for (int i = 0; i < LETTER_NUM; i++) {
		mLetXs[i] = 120 + 130 * i;
		mLetYs[i] = -245;

		// �����Ă��Ȃ���Ԃɂ���
		mLetIsMovings[i] = false;
	}

	// �܂������̈ړ����I���Ă��Ȃ���Ԃɏ�����
	mHasSetLetters = false;

	mMoveLetterId = 0;
	mFrameCnt = 0;
}


void GameOver::Finalize() {
	// �w�i�摜�̍폜
	DeleteGraph(mBackHandle);

	// GAMEOVER!�̕����̉摜�̍폜
	for (int i = 0; i < LETTER_NUM; i++) {
		DeleteGraph(mLetterHandles[i]);
	}

	// �t�H���g�̍폜
	DeleteFontToHandle(mStrFontHandle);
}


void GameOver::Update() {
	// �����������Ă��邩�ǂ�������
	bool isMoving = false;
	for (int i = 0; i < LETTER_NUM; i++) {
		if (mLetIsMovings[i]) isMoving = true;
	}

	if (isMoving) {	// �����������Ă����Ԃ�������
		// �������ړ�������
		Move();

		// ���ׂĂ̕����������I����Ă��邩�ǂ����m�F
		bool hasSetLetters = true;
		for (int i = 0; i < LETTER_NUM; i++) {
			if (mLetIsMovings[i]) hasSetLetters = false;
		}
		mHasSetLetters = hasSetLetters;
	}
	
	if (mFrameCnt >= FIRST_LETTER_STOP_FRAME_NUM &&	// �ŏ��̕����𓮂��n�߂����鎞�Ԃ𒴂��Ă���
		mMoveLetterId < LETTER_NUM) {	// 1�ł������������n�߂Ă��Ȃ��Ƃ�
		if (mFrameCnt % EACH_LETTERS_STOP_FRAME_NUM == 0) {	// ����̎��Ԗ���
			// �����𓮂��o������
			mLetYsPrev[mMoveLetterId] = mLetYs[mMoveLetterId];
			mLetYs[mMoveLetterId] = mLetYs[mMoveLetterId] + 31;
			mLetIsMovings[mMoveLetterId] = true;

			mMoveLetterId++;
		}
	}

	mFrameCnt++;
}


void GameOver::Move() {
	for (int i = 0; i < 9; i++) {
		if (mLetIsMovings[i]) {	// �����Ă�����
			int letYTemp = mLetYs[i];
			mLetYs[i] += (mLetYs[i] - mLetYsPrev[i]) - 1;
			mLetYsPrev[i] = letYTemp;

			if (mLetYs[i] - mLetYsPrev[i] == -10) {
				mLetIsMovings[i] = false;
			}
		}
	}
}

void GameOver::Draw() {
	// �w�i�摜�̕`��
	DrawGraph(0, 0, mBackHandle, FALSE);

	// GAMEOVER!�̕����̉摜�̕`��
	for (int i = 0; i < LETTER_NUM; i++) {
		DrawGraph(mLetXs[i] - IMG_W / 2, mLetYs[i] - IMG_H / 2, mLetterHandles[i], TRUE);
	}

	// �u���j���[��ʂɖ߂�iEsc�L�[�������j�v�̕`��
	if (mHasSetLetters) {	// ���ׂĂ̕����̈ړ����I����Ă�����
		DrawFormatStringToHandle(320, 600, GetColor(255, 255, 255), mStrFontHandle, "���j���[��ʂɖ߂�iEsc�L�[�������j");
	}
}