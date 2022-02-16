#pragma once

// Playerの体力が0になったときのゲームオーバー画面
#include "BasicFunc.h"


class GameOver : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	void Move();	// GAMEOVER!それぞれの文字の座標の更新に使う

	int mBackHandle;	// 背景画像
	const int LETTER_NUM = 9;	// GAMEOVER!の文字数
	int mLetterHandles[9];	// GAMEOVER! の9文字の画像
	int mStrFontHandle;	// 「メニュー画面に戻る（Escキーを押す）」の文字の表示に使用するフォント
	const int IMG_W = 170, IMG_H = 170;	// 文字の画像の大きさ
	int mLetXs[9], mLetYs[9];	// GAME OVER!の文字それぞれの座標
	int mLetYsPrev[9];	// 文字の移動で使う
	//int count; //時間の経過を計る
	bool mLetIsMovings[9];	// それぞれの文字が移動中かどうか
	bool mHasSetLetters;	// それぞれの文字の移動を終えたかどうか，終わっていたらtrue
	int mMoveLetterId;	// 動き始めさせる文字のid，1文字ずつ順に動き出させる
	unsigned long long mFrameCnt;	// 経過したフレーム数のカウント，各文字の動き初めに使用したりする
	const int FIRST_LETTER_STOP_FRAME_NUM = 30;	// 最初の文字が動き始めるまで止まっている時間
	const int EACH_LETTERS_STOP_FRAME_NUM = 10;	// 各文字が前の文字が動いてから止まっている時間
	//bool m_bChgScene; //SceneをMenuに変えるならtrue
	
};