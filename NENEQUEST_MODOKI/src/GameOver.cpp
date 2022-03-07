#include "GameOver.h"
#include "DxLib.h"


void GameOver::Initialize() {
	// 背景画像の読み込み
	mBackHandle = LoadGraph("images/gameoverback.png");
	// GAMEOVER!の文字の画像の読み込み
	LoadDivGraph("images/gameoverletters.png", 9, 1, 9, IMG_W, IMG_H, mLetterHandles);

	// 文字の表示に使用するフォントの取得
	mStrFontHandle = CreateFontToHandle("HG創英角ゴシックUB 標準", 40, 1, -1);

	// GAMEOVER!のそれぞれの文字の座標の設定
	for (int i = 0; i < LETTER_NUM; i++) {
		mLetXs[i] = 120 + 130 * i;
		mLetYs[i] = -245;

		// 動いていない状態にする
		mLetIsMovings[i] = false;
	}

	// まだ文字の移動を終えていない状態に初期化
	mHasSetLetters = false;

	mMoveLetterId = 0;
	mFrameCnt = 0;
}


void GameOver::Finalize() {
	// 背景画像の削除
	DeleteGraph(mBackHandle);

	// GAMEOVER!の文字の画像の削除
	for (int i = 0; i < LETTER_NUM; i++) {
		DeleteGraph(mLetterHandles[i]);
	}

	// フォントの削除
	DeleteFontToHandle(mStrFontHandle);
}


void GameOver::Update() {
	// 文字が動いているかどうか見る
	bool isMoving = false;
	for (int i = 0; i < LETTER_NUM; i++) {
		if (mLetIsMovings[i]) isMoving = true;
	}

	if (isMoving) {	// 文字が動いている状態だったら
		// 文字を移動させる
		Move();

		// すべての文字が動き終わっているかどうか確認
		bool hasSetLetters = true;
		for (int i = 0; i < LETTER_NUM; i++) {
			if (mLetIsMovings[i]) hasSetLetters = false;
		}
		mHasSetLetters = hasSetLetters;
	}
	
	if (mFrameCnt >= FIRST_LETTER_STOP_FRAME_NUM &&	// 最初の文字を動き始めさせる時間を超えていて
		mMoveLetterId < LETTER_NUM) {	// 1つでも文字が動き始めていないとき
		if (mFrameCnt % EACH_LETTERS_STOP_FRAME_NUM == 0) {	// 特定の時間毎に
			// 文字を動き出させる
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
		if (mLetIsMovings[i]) {	// 動いていたら
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
	// 背景画像の描画
	DrawGraph(0, 0, mBackHandle, FALSE);

	// GAMEOVER!の文字の画像の描画
	for (int i = 0; i < LETTER_NUM; i++) {
		DrawGraph(mLetXs[i] - IMG_W / 2, mLetYs[i] - IMG_H / 2, mLetterHandles[i], TRUE);
	}

	// 「メニュー画面に戻る（Escキーを押す）」の描画
	if (mHasSetLetters) {	// すべての文字の移動が終わっていたら
		DrawFormatStringToHandle(320, 600, GetColor(255, 255, 255), mStrFontHandle, "メニュー画面に戻る（Escキーを押す）");
	}
}