#include "Player.h"
#include "DxLib.h"
//#include <map>
//#include <string>
//#include "HitJudge0.h"
//#include "HitJudge1.h"
//#include "HitJudge2.h"
//#include "PlayerData.h"
//#include "PowerBox.h"
#include "PlayerMgr.h"


Player::Player(PlayerChanger* changer, const int* graph) : mPlHandle(graph) {
	mPlayerChanger = changer;
}


void Player::Initialize() {
	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mAX = mX + 160;
	mAY = mY + 20;
	//mHitRangeW = 33, mHitRangeH = 60;
	//mHitRangeAW = 50, mHitRangeAH = 60;
	mImgW = 500, mImgH = 283;
	mIsGod = false;
	mGodFrameCnt = -1;

	// Player�̍U���C�W�����v�Ȃǂ̏�Ԑݒ�
	mXFrameCnt = 0, mYFrameCnt = 0;
	mAFrameCnt = 0;
	mIsJumping = false;
	mIsAttacking = false;
	mHandleId = 0;
	mSpeed = 1.0f;
	//mAttack = 1;

	// �A�C�e����g�p����̐ݒ�
	mIteFrameCnt = 0;
	//mIteKindId = 1;
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
		mEffectHandle = NULL;
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


void Player::Finalize() {
	// ���ʂ̉摜���폜
	DeleteGraph(mEffectHandle);
}


void Player::Draw() {
	// Player�̉摜�\��
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 13, mPlHandle[mHandleId], TRUE);

	// Effect�̉摜�\��
	if (mHasIteS || mHasIteA) {	// Item�̌��ʒ��̂Ƃ�
		DrawGraph(mX - 114, mY - 113, mEffectHandle, TRUE);
	}
}


void Player::UpdateSAP() {
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


void Player::Walk() {
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
}


void Player::Jump() {
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


void Player::Attack() {
	// Player4�ȊO����Attack()�g��
	// �\������player�̉摜�ԍ��̍X�V���s��
	mHandleId += 2;

	if (mIsAttacking) {	// �U�����Ă���Ƃ�
		if (mAFrameCnt > 0) --mAFrameCnt;
		else mIsAttacking = false;
	}
	else {
		mIsAttacking = true;
		mAFrameCnt = mAFrameNum;
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// ���������Ă���Ƃ�
			mAX = mX - 160;
			mAY = mY + 20;
		}
		else {	// �E�������Ă���Ƃ�
			mAX = mX + 160;
			mAY = mY + 20;
		}
	}
}


void Player::UpdateHit() {
	//HitJudge0::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge1::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge2::SetPlRange(x, y, hitRangeX, hitRangeY);

	//if (mIsAttacking == true) {
	//	HitJudge0::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
	//	HitJudge1::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
	//	HitJudge2::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
	//	mIsAttacking = false;
	//}
	//else {
	//	HitJudge0::SetPlARange(-3000, -3000, 0, 0);
	//	HitJudge1::SetPlARange(-3000, -3000, 0, 0);
	//	HitJudge2::SetPlARange(-3000, -3000, 0, 0);
	//}

	//if (mIsGod == false) {
	//	eneJudge0 = HitJudge0::PEJudge();
	//	eneJudge1 = HitJudge1::PEJudge();
	//	eneJudge2 = HitJudge2::PEJudge();
	//	eneAJudge0 = HitJudge0::EaPJudge();
	//	eneAJudge1 = HitJudge1::EaPJudge();
	//	eneAJudge2 = HitJudge2::EaPJudge();
	//}
	//
	//if (icount == 1) {
	//	iJudge0 = false;
	//	iJudge1 = false;
	//	icount++;
	//}
	//else if (icount == 2) {
	//	icount = 0;
	//}
	//else {
	//	iJudge0 = HitJudge0::PIJudge();
	//	iJudge1 = HitJudge1::PIJudge();
	//}

	//if (iJudge0 == true || iJudge1 == true) {
	//	if (iJudge0 == true) {
	//		weaponNum = PowerBox::GetWpn0Num();

	//		if (weaponNum == 6) { //6�͎������n��Item��\��
	//			iPower = PowerBox::GetIPower0();
	//			isPower = PowerBox::GetISPower0();
	//		}
	//		
	//		ihPower = PowerBox::GetIHPower0();
	//	}
	//	else {
	//		weaponNum = PowerBox::GetWpn1Num();

	//		if (weaponNum == 6) { //4�͎������n��Item��\��
	//			iPower = PowerBox::GetIPower1();
	//			isPower = PowerBox::GetISPower1();
	//		}

	//		ihPower = PowerBox::GetIHPower1();
	//	}

	//	hp = hp + ihPower;
	//	if (hp < 0) {
	//		hp = 0;
	//	}
	//	else if (hp > 10) {
	//		hp = 10;
	//	}
	//	PlayerData::SetPlayerHP(hp);

	//	if (isPower != 1 && weaponNum == 6) { //�Ȃɂ����ʂ��󂯂Ă���Ƃ��ɕ�����Ƃ���count��600�Ƀ��Z�b�g����Ȃ�����
	//		iscount = 600;
	//		
	//		if (isPower == 2) {
	//			effectHandle = LoadGraph("images/effect_1.png");
	//			PlayerData::SetEffectNum(1);
	//		}
	//		else {
	//			isPower = 0.5;
	//			effectHandle = LoadGraph("images/effect_2.png");
	//			PlayerData::SetEffectNum(2);
	//		}
	//	}
	//	else if (iPower != 1 && weaponNum == 6) {
	//		ipcount = 600;
	//		PowerBox::SetPlPower(iPower);
	//		effectHandle = LoadGraph("images/effect_3.png");
	//		PlayerData::SetEffectNum(3);
	//	}

	//	icount++;
	//}

	//if (eneJudge0 == true || eneJudge1 == true || eneJudge2 == true || eneAJudge0 == true || eneAJudge1 == true || eneAJudge2 == true) {
	//	if (eneJudge0 == true) {
	//		enePower = PowerBox::GetEnePower0();
	//		eneJudge0 = false;
	//	}
	//	else if (eneJudge1 == true) {
	//		enePower = PowerBox::GetEnePower1();
	//		eneJudge1 = false;
	//	}
	//	else if (eneJudge2 == true) {
	//		enePower = PowerBox::GetEnePower2();
	//		eneJudge2 = false;
	//	}
	//	else if (eneAJudge0 == true) {
	//		enePower = PowerBox::GetEneAPower0();
	//		eneAJudge0 = false;
	//	}
	//	else if (eneAJudge1 == true) {
	//		enePower = PowerBox::GetEneAPower1();
	//		eneAJudge1 = false;
	//	}
	//	else {
	//		enePower = PowerBox::GetEneAPower2();
	//		eneAJudge2 = false;
	//	}

	//	hp = hp - enePower;
	//	if (hp < 0) {
	//		hp = 0;
	//	}
	//	else if (hp > 10) {
	//		hp = 10;
	//	}
	//	PlayerData::SetPlayerHP(hp);
	//	godCount = 100;
	//	godFlag = true;
	//}
}


void Player::SetPlParams(const int x, const int y, const int hp, const int iteSFrameCnt,
	const int iteAFrameCnt, const int bsStopFrameCnt, const int effectId, const int deadFrameCnt, const bool isDead) {
	// �p�����[�^�Ŏ󂯎�����l��������
	mX = x;
	mY = y;
	mHp = hp;
	mIteSFrameCnt = iteSFrameCnt;
	mIteAFrameCnt = iteAFrameCnt;
	mBsStopFrameCnt = bsStopFrameCnt;
	mEffectId = effectId;
	mDeadFrameCnt = deadFrameCnt;
	mIsDead = isDead;
}


void Player::StartBossStage() {
	//prev_x = x;
	//prev_y = y;
	//prev_xcount = xcount;
	//prev_ycount = ycount;

	//if (x > 353) {
	//	x -= 2;

	//	/*if (xcount > 0) {
	//		xcount = 0;
	//	}*/
	//	--xcount;
	//}
	//if (x < 349) {
	//	x += 2;

	//	/*if (xcount < 0) {
	//		xcount = 0;
	//	}*/
	//	++xcount;
	//}
	//if (y > 453) {
	//	y -= 2;

	//	/*if (ycount > 0) {
	//		ycount = 0;
	//	}*/
	//	--ycount;
	//}
	//if (y < 449) {
	//	prev_y = y;
	//	y += 2;

	//	/*if (ycount < 0) {
	//		ycount = 0;
	//	}*/
	//	++ycount;
	//}


	//if (y == prev_y && x == prev_x) {
	//	handleNumber = 0;
	//}
	//else {
	//	if (xcount != prev_xcount) {
	//		ix = abs(xcount) % 40 / 20;

	//		if (xcount > 0) {
	//			ix += 0;
	//			handleNumber = ix;
	//		}
	//		else if (xcount < 0) {
	//			ix += 6;
	//			handleNumber = ix;
	//		}
	//	}
	//	
	//	if (prev_ycount != prev_ycount && ycount != 0) {
	//		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
	//				iy += 6;
	//		}

	//		handleNumber = iy;
	//	}
	//}

	//PlayerData::SetBscount(bscount + 1);
	//bscount++;
}


void Player::GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	// �ق�Ƃ͂��ꂼ�ꂵ����ׂ��ꏊ�ōX�V���I�����u�Ԃɂ��ꏑ�����ق��������i�S�̏����I����Ă���C������j
	mPlIntDataMap["x"] = mX;
	mPlIntDataMap["y"] = mY;
	mPlIntDataMap["hp"] = mHp;
	mPlIntDataMap["iteFrameSCnt"] = mIteSFrameCnt;
	mPlIntDataMap["iteFrameACnt"] = mIteAFrameCnt;
	mPlIntDataMap["bsStopFrameCnt"] = mBsStopFrameCnt;
	mPlBoolDataMap["isDead"] = mIsDead;

	plIntDataMap = &mPlIntDataMap;
	plBoolDataMap = &mPlBoolDataMap;
}


void Player::GetPlIntDataMap(std::map<std::string, int>* plIntDataMap) {
	mPlIntDataMap["x"] = mX;
	mPlIntDataMap["y"] = mY;
	mPlIntDataMap["hp"] = mHp;
	mPlIntDataMap["iteFrameSCnt"] = mIteSFrameCnt;
	mPlIntDataMap["iteFrameACnt"] = mIteAFrameCnt;
	mPlIntDataMap["bsStopFrameCnt"] = mBsStopFrameCnt;

	plIntDataMap = &mPlIntDataMap;
}