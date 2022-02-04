#include "Player1.h"
#include "DxLib.h"
//#include "HitJudge0.h"
//#include "HitJudge1.h"
//#include "HitJudge2.h"
//#include "PlayerData.h"
//#include "PowerBox.h"
#include "PlayerMgr.h"

Player1* Player1::mPlayer1;


Player1::Player1(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 1)) {
	mPlayerMgr = PlayerMgr::GetInstance();
}


Player1::~Player1() {
	delete mPlayer1;
}


Player1* Player1::GetInstance() {
	if (mPlayer1 == NULL) {
		PlayerMgr* playerMgr = PlayerMgr::GetInstance();
		mPlayer1 = new Player1(playerMgr);
		// InitializeはGetInstanceの呼び出し側にSetPlParamsとともに行ってもらう
	}

	return mPlayer1;
}


void Player1::Initialize() {
	// 位置，当たり判定の範囲関連設定
	mAX = mX + 160;
	mAY = mY + 20;
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 50, mHitRangeAH = 60;
	mImgW = 500, mImgH = 283;
	mIsGod = false;
	mGodFrameCnt = -1;

	// Playerの攻撃，ジャンプなどの状態設定
	mXFrameCnt = 0, mYFrameCnt = 0;
	mAFrameCnt = 0;
	mIsJumping = false;
	mIsAttacking = false;
	//mDeadFrameCnt = 0;
	mHandleId = 0;
	mSpeed = 1.0f;
	mAttack = 1;
	
	// アイテムや使用武器の設定
	mIteFrameCnt = 0;
	mIteKindId = 1;
	mIteHP = 0;

	if (mIteSFrameCnt > 0) {
		mHasIteS = true;
	}
	else {
		mHasIteS = false;
	}

	if (mIteAFrameCnt > 0) {
		mHasIteA = true;
	}
	else {
		mHasIteA = false;
	}
	
	if (mEffectId == 0) {
		mIteSP = 1.0f;
		mIteAP = 1;
	}
	else if (mEffectId == 1) {
		mIteSP = 2.0f;
		mIteAP = 1;
		mEffectHandle = LoadGraph("images/effect_1.png");
	}
	else if (mEffectId == 2) {
		mIteSP = 0.5f;
		mIteAP = 1;
		mEffectHandle = LoadGraph("images/effect_2.png");
	}
	else {
		mIteSP = 1.0f;
		mIteAP = 2;
		mEffectHandle = LoadGraph("images/effect_3.png");
	}
}

 void Player1::Finalize() {
	/*for (int i = 0; i < 24; i++) {
		DeleteGraph(mPlHandle[i]);
	}*/
	DeleteGraph(mEffectHandle);
}

void Player1::Update() {
	if (mHp == 0) {	// 死んだときの処理（死んだことを認識させるための120フレームの硬直）
		if (mDeadFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		mHandleId = 0;

		mDeadFrameCnt++;
	}
	else {	// 生きているときの処理
		// boss stageに突入しているかしていないかチェック
		//mIsAtBsSt = PlayerData::GetBossFlag();
		
		if (mIsAtBsSt == true && mBsStopFrameCnt <= 1280) {	// boss stageの始まる際の強制的な移動処理
			StartBossStage();
		}
		else {
			if (mIteKindId != 1 && mIteKindId != 5 && mIteKindId != 6) {	// 武器交換をするとき
				if (mIteKindId == 2) {
					mPlayerChanger->ChangePlayer(ePlayer2);
				}
				else if (mIteKindId == 3) {
					mPlayerChanger->ChangePlayer(ePlayer3);
				}
				else {
					mPlayerChanger->ChangePlayer(ePlayer4);
				}
			}

			// キー入力の取得
			gpUpdateKey();

			// 左右上下方向のキーを連続で押しているフレーム数の更新
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0) {
				mXFrameCnt = 0;
			}
			if (key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				mYFrameCnt = 0;
			}

			// 立ち止まったら立ち止まりの画像番号にする
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0 && key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
					mHandleId = 6;
				}
				else {
					mHandleId = 0;
				}
			}

			// playerの行う動作に対応した移動速度，攻撃力に更新
			UpdateSAP(); 

			// キー入力があった際は移動処理をする
			if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0 || key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
				Walk();
			}

			// ジャンプと攻撃の処理
			if (!mIsAttacking && (mIsJumping == true || key[KEY_INPUT_A] == 1)) {	// 攻撃中でなく，かつジャンプ中，もしくはジャンプ入力キーを押しているとき
				Jump();
			}
			else if (mIsAttacking || key[KEY_INPUT_S] == 1) {	// 攻撃中であるか，攻撃キーを押しているとき
				Attack();
			}

			//HitJudge();
		}
	}
}

void Player1::Draw() {
	if (mIsGod == true) {
		if (mGodFrameCnt == -1) {
			mIsGod = false;
		}
		else if (mGodFrameCnt > 80 || (mGodFrameCnt <= 60 && mGodFrameCnt > 40) || mGodFrameCnt <= 20) {
			mHandleId += 12;
			--mGodFrameCnt;
		}
		else {
			--mGodFrameCnt;
		}
	}

	DrawGraph(mX-mImgW/2, mY-mImgH/2-13, mPlHandle[mHandleId], TRUE);
	//DrawBox(mAX-50, mAY-60, mAX + 50, mAY + 60, GetColor(0, 0, 0), TRUE);

	if (mIteSP != 1 || mIteAP != 1) {
		DrawGraph(mX - 114, mY - 113, mEffectHandle, TRUE);
	}

	//DrawFormatString(100, 200, GetColor(255, 255, 255), "ys = %d", mAX);
	//DrawFormatString(100, 300, GetColor(255, 255, 255), "px = %d, ex = %d", mX, mY);
}


void Player1::UpdateSAP() {
	// 移動速度の更新
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// 左右の入力があるとき
		if (mIsJumping == true) {	// ジャンプしているとき
			mSpeed = 0.8f;
		}
		else if (mIsAttacking) {	// 攻撃しているとき
			mSpeed = 0.5f;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
			mSpeed = 0.625f;
		}
		else {
			mSpeed = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
		if (mIsAttacking) {	// 攻撃しているとき
			mSpeed = 0.5f;
		}
		else {
			mSpeed = 0.80f;
		}
	}

	// 移動速度（アイテム効果）の更新
	if (mHasIteS) {	
		if (mIteSFrameCnt != 0) {	// 効果中のとき
			mSpeed *= mIteSP;
			mIteSFrameCnt--;
		}
		else {	// 効果切れのとき
			mIteSP = 1.0f;
			mEffectHandle = 0;
			mHasIteS = false;
		}
	}

	// 攻撃力（アイテム効果）の更新
	if (mHasIteA) {
		if (mIteAFrameCnt != 0) {	// 効果中のとき
			mAttack *= mIteAP;
			mIteAFrameCnt--;
		}
		else {	// 効果切れのとき
			mIteAP = 1;
			mEffectHandle = 0;
			mHasIteA = false;
		}
	}
}

void Player1::Walk() {
	// stageごとに構成が変わるため，stageの移動範囲に合わせたplayerの座標更新を行う
	if (mIsAtBsSt == false) {	// boss stageではないとき
		if (key[KEY_INPUT_LEFT] != 0) {
			if (mX > X_MIN_N) {
				mX -= (int)(4 * mSpeed);
			}

			if (mX < X_MIN_N) mX = X_MIN_N;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {
			if (mX < X_MAX_N) {
				mX += (int)(4 * mSpeed);
			}

			if (mX > X_MAX_N) mX = X_MAX_N;

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && mIsJumping == false) {
			if (mY > Y_MIN_N) {
				mY -= (int)(4 * mSpeed);
			}

			if (mY < Y_MIN_N) mY = Y_MIN_N;

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && mIsJumping == false) {
			if (mY < Y_MAX_N) {
				mY += (int)(4 * mSpeed);
			}

			if (mY > Y_MAX_N) mY = Y_MAX_N;

			if (mYFrameCnt < 0) {
				mYFrameCnt = 0;
			}
			++mYFrameCnt;
		}
	}
	else {	// boss stageのとき
		if (key[KEY_INPUT_LEFT] != 0) {
			if (mX > X_MIN_B) {
				mX -= (int)(4 * mSpeed);
			}

			if (mX < X_MIN_B) mX = X_MIN_B;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {
			if (mX < X_MAX_B) {
				mX += (int)(4 * mSpeed);

				if (mX > X_MAX_B) mX = X_MAX_B;
			}
			else if (mX < X_MAX_BR && mY >= Y_MIN_BR && mY <= Y_MAX_BR) {
				mX += (int)(4 * mSpeed);

				if (mX > X_MAX_BR) mX = X_MAX_BR;
			}

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && mIsJumping == false) {
			if (mY > Y_MIN_B && mX <= X_MAX_B) {
				mY -= (int)(4 * mSpeed);

				if (mY < Y_MIN_B) mY = Y_MIN_B;
			}
			else if (mY > Y_MIN_BR && mX <= X_MAX_BR) {
				mY -= (int)(4 * mSpeed);

				if (mY < Y_MIN_BR) mY = Y_MIN_BR;
			}

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && mIsJumping == false) {
			if (mY < Y_MAX_B && mX <= X_MAX_B) {
				mY += (int)(4 * mSpeed);

				if (mY > Y_MAX_B) mY = Y_MAX_B;
			}
			else if (mY < Y_MAX_BR && mX <= X_MAX_BR) {
				mY += (int)(4 * mSpeed);

				if (mY > Y_MAX_BR) mY = Y_MAX_BR;
			}

			if (mYFrameCnt < 0) {
				mYFrameCnt = 0;
			}
			++mYFrameCnt;
		}
	}

	// 表示するplayerの画像番号の更新を行う
	int ix = abs(mXFrameCnt) % 40 / 20;
	int iy = abs(mYFrameCnt) % 40 / 20;

	if (mXFrameCnt > 0) {
		ix += 0;
		mHandleId = ix;
	}
	else if (mXFrameCnt < 0) {
		ix += 6;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
			iy += 6;
		}
		
		mHandleId = iy;
	}
}


void Player1::Attack() {
	// 表示するplayerの画像番号の更新を行う
	mHandleId += 2;

	/*if (mXFrameCnt != 0) {
		ix += 2;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		iy += 2;
		mHandleId = iy;
	}*/


	if (mIsAttacking) {
		if (mAFrameCnt > 0) --mAFrameCnt;
		else mIsAttacking = false;
	}
	else {
		mIsAttacking = true;
		mAFrameCnt = 20;
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// 攻撃しているとき
			mAX = mX - 160;
			mAY = mY + 20;
		}
		else {	// 攻撃していないとき
			mAX = mX + 160;
			mAY = mY + 20;
		}
	}
}

void Player1::Jump() {
	// 表示するplayerの画像番号の更新を行う
	if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
		mHandleId = 10;
	}
	else {
		mHandleId = 4;
	}

	// playerの座標の更新を行う
	if (mIsJumping == true) {
		int yTemp = mY;
		mY += (mY - mYPrev) + 1;
		mYPrev = yTemp;

		if (mY == mYStart) {
			mIsJumping = false;
		}
	}
	else {
		mIsJumping = true;
		mYStart = mY;
		mYPrev = mY;
		mY = mY - 17;
	}
}