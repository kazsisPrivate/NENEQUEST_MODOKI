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
		// Initialize��GetInstance�̌Ăяo������SetPlParams�ƂƂ��ɍs���Ă��炤
	}

	return mPlayer1;
}


void Player1::Initialize() {
	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mAX = mX + 160;
	mAY = mY + 20;
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 50, mHitRangeAH = 60;
	mImgW = 500, mImgH = 283;
	mIsGod = false;
	mGodFrameCnt = -1;

	// Player�̍U���C�W�����v�Ȃǂ̏�Ԑݒ�
	mXFrameCnt = 0, mYFrameCnt = 0;
	mAFrameCnt = 0;
	mIsJumping = false;
	mIsAttacking = false;
	//mDeadFrameCnt = 0;
	mHandleId = 0;
	mSpeed = 1.0f;
	mAttack = 1;
	
	// �A�C�e����g�p����̐ݒ�
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
	if (mHp == 0) {	// ���񂾂Ƃ��̏����i���񂾂��Ƃ�F�������邽�߂�120�t���[���̍d���j
		if (mDeadFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		mHandleId = 0;

		mDeadFrameCnt++;
	}
	else {	// �����Ă���Ƃ��̏���
		// boss stage�ɓ˓����Ă��邩���Ă��Ȃ����`�F�b�N
		//mIsAtBsSt = PlayerData::GetBossFlag();
		
		if (mIsAtBsSt == true && mBsStopFrameCnt <= 1280) {	// boss stage�̎n�܂�ۂ̋����I�Ȉړ�����
			StartBossStage();
		}
		else {
			if (mIteKindId != 1 && mIteKindId != 5 && mIteKindId != 6) {	// �������������Ƃ�
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

			// �L�[���͂̎擾
			gpUpdateKey();

			// ���E�㉺�����̃L�[��A���ŉ����Ă���t���[�����̍X�V
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0) {
				mXFrameCnt = 0;
			}
			if (key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				mYFrameCnt = 0;
			}

			// �����~�܂����痧���~�܂�̉摜�ԍ��ɂ���
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0 && key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
					mHandleId = 6;
				}
				else {
					mHandleId = 0;
				}
			}

			// player�̍s������ɑΉ������ړ����x�C�U���͂ɍX�V
			UpdateSAP(); 

			// �L�[���͂��������ۂ͈ړ�����������
			if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0 || key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
				Walk();
			}

			// �W�����v�ƍU���̏���
			if (!mIsAttacking && (mIsJumping == true || key[KEY_INPUT_A] == 1)) {	// �U�����łȂ��C���W�����v���C�������̓W�����v���̓L�[�������Ă���Ƃ�
				Jump();
			}
			else if (mIsAttacking || key[KEY_INPUT_S] == 1) {	// �U�����ł��邩�C�U���L�[�������Ă���Ƃ�
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
	// �ړ����x�̍X�V
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// ���E�̓��͂�����Ƃ�
		if (mIsJumping == true) {	// �W�����v���Ă���Ƃ�
			mSpeed = 0.8f;
		}
		else if (mIsAttacking) {	// �U�����Ă���Ƃ�
			mSpeed = 0.5f;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// �㉺�̓��͂�����Ƃ�
			mSpeed = 0.625f;
		}
		else {
			mSpeed = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// �㉺�̓��͂�����Ƃ�
		if (mIsAttacking) {	// �U�����Ă���Ƃ�
			mSpeed = 0.5f;
		}
		else {
			mSpeed = 0.80f;
		}
	}

	// �ړ����x�i�A�C�e�����ʁj�̍X�V
	if (mHasIteS) {	
		if (mIteSFrameCnt != 0) {	// ���ʒ��̂Ƃ�
			mSpeed *= mIteSP;
			mIteSFrameCnt--;
		}
		else {	// ���ʐ؂�̂Ƃ�
			mIteSP = 1.0f;
			mEffectHandle = 0;
			mHasIteS = false;
		}
	}

	// �U���́i�A�C�e�����ʁj�̍X�V
	if (mHasIteA) {
		if (mIteAFrameCnt != 0) {	// ���ʒ��̂Ƃ�
			mAttack *= mIteAP;
			mIteAFrameCnt--;
		}
		else {	// ���ʐ؂�̂Ƃ�
			mIteAP = 1;
			mEffectHandle = 0;
			mHasIteA = false;
		}
	}
}

void Player1::Walk() {
	// stage���Ƃɍ\�����ς�邽�߁Cstage�̈ړ��͈͂ɍ��킹��player�̍��W�X�V���s��
	if (mIsAtBsSt == false) {	// boss stage�ł͂Ȃ��Ƃ�
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
	else {	// boss stage�̂Ƃ�
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

	// �\������player�̉摜�ԍ��̍X�V���s��
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
	// �\������player�̉摜�ԍ��̍X�V���s��
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
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// �U�����Ă���Ƃ�
			mAX = mX - 160;
			mAY = mY + 20;
		}
		else {	// �U�����Ă��Ȃ��Ƃ�
			mAX = mX + 160;
			mAY = mY + 20;
		}
	}
}

void Player1::Jump() {
	// �\������player�̉摜�ԍ��̍X�V���s��
	if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
		mHandleId = 10;
	}
	else {
		mHandleId = 4;
	}

	// player�̍��W�̍X�V���s��
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