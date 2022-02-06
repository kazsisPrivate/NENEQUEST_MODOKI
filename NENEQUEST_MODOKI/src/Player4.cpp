// �|�i�U���́F���ʁC�U���͈́F�L���C�U���������ԁF�����i���̍U���܂łɂ����鎞�ԁF�����j�C������Փx�F����j

#include "Player4.h"
#include "DxLib.h"
#include "PlayerMgr.h"

Player4* Player4::mPlayer4;


Player4::Player4(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 4)) {
	mPlayerMgr = PlayerMgr::GetInstance();
}


Player4::~Player4() {
	delete mPlayer4;
}


Player4* Player4::GetInstance() {
	if (mPlayer4 == NULL) {
		PlayerMgr* playerMgr = PlayerMgr::GetInstance();
		mPlayer4 = new Player4(playerMgr);
		// Initialize��GetInstance�̌Ăяo������SetPlParams�ƂƂ��ɍs���Ă��炤
	}

	return mPlayer4;
}


void Player4::Initialize() {
	Player::Initialize();

	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 45, mHitRangeAH = 60;

	// Player�̍U���̏�Ԑݒ�
	mAttack = 1;
	// mAFrameNum �͋����|�F120�C�ア�|�F90

	// �A�C�e����g�p����̐ݒ�
	mIteKindId = 4;
	// �|�֘A�̐ݒ�
	mIsPreparingWA = false;
	mIsPreparingSA = false;
	mArrow = new Arrow();
	mArrow->Initialize();
	mArrowExists = false;
}


void Player4::Finalize() {
	Player::Finalize();

	delete mArrow;
}

void Player4::Update() {
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
			// �������������Ƃ�
			if (mIteKindId == 1) {
				mPlayerChanger->ChangePlayer(ePlayer1);
			}
			else if (mIteKindId == 2) {
				mPlayerChanger->ChangePlayer(ePlayer2);
			}
			else if (mIteKindId == 3) {
				mPlayerChanger->ChangePlayer(ePlayer3);
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
				if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
					mHandleId = 8;
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

			// �|��̍U�����ʂ��c���Ă��邩�m�F
			mArrowExists = mArrow->GetArrowExists();

			// �W�����v�ƍU���̏���
			if (!mIsAttacking && (mIsJumping == true || key[KEY_INPUT_A] == 1)) {	// �U�����łȂ��C���W�����v���C�������̓W�����v���̓L�[�������Ă���Ƃ�
				Jump();
			}
			else if (mIsAttacking) {	// �U�����ł���Ƃ��i�|�����������Ɓj
				Attack();

				if (mArrowExists) {	// �|��̍U�����c���Ă���Ƃ�
					mArrow->Update();
				}

				// �U�����Ԃ��I������玟�̍U�����ł���悤�ɂ���
				if (mAFrameCnt == 0) mIsAttacking = false;
			}
			else if ((key[KEY_INPUT_S] == 1 || mIsPreparingWA) && !mIsPreparingSA) {	//	�ア�|��łƂ��Ƃ��Ă���Ƃ�
				PrepareWAttack();
			}
			else if (key[KEY_INPUT_D] == 1 || mIsPreparingSA) {	// �����|��łƂ��Ƃ��Ă���Ƃ�
				PrepareSAttack();
			}

			//HitJudge();
		}
	}

	// �_���[�W���󂯂���̏����̊Ԃ̖��G���Ԃ̏���
	if (mIsGod == true) {
		if (mGodFrameCnt == -1) {
			mIsGod = false;
		}
		else if (mGodFrameCnt > 80 || (mGodFrameCnt <= 60 && mGodFrameCnt > 40) || mGodFrameCnt <= 20) {	// Player�𔒂�����
			mHandleId += 16;
			--mGodFrameCnt;
		}
		else {
			--mGodFrameCnt;
		}
	}
}

void Player4::Draw() {
	Player::Draw();

	if (mArrowExists) {
		mArrow->Draw();
	}
}

void Player4::UpdateSAP() {
	// �ړ����x�̍X�V
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// ���E�̓��͂�����Ƃ�
		if (mIsJumping == true) {	// �W�����v���Ă���Ƃ�
			mSpeed = 0.8f;
		}
		else if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// �U�����Ă���Ƃ�or�U���������̂Ƃ�
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
		if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// �U�����Ă���Ƃ�or�U���������̂Ƃ�
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

void Player4::Walk() {
	// stage���Ƃɍ\�����ς�邽�߁Cstage�̈ړ��͈͂ɍ��킹��player�̍��W�X�V���s��
	Player::Walk();

	// �\������player�̉摜�ԍ��̍X�V���s��
	int ix = abs(mXFrameCnt) % 40 / 20;
	int iy = abs(mYFrameCnt) % 40 / 20;

	if (mXFrameCnt > 0) {
		ix += 0;
		mHandleId = ix;
	}
	else if (mXFrameCnt < 0) {
		ix += 8;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// ���������Ă���Ƃ�
			iy += 8;
		}

		mHandleId = iy;
	}
}

void Player4::Attack() {
	mHandleId += 4;
	
	--mAFrameCnt;
}

void Player4::Jump() {
	// �\������player�̉摜�ԍ��̍X�V���s��
	if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// ���������Ă���Ƃ�
		mHandleId = 14;
	}
	else {	// �E�������Ă���Ƃ�
		mHandleId = 6;
	}

	// player�̍��W�̍X�V���s��
	Player::Jump();
}

void Player4::PrepareWAttack() {	// �ア�U���i�|��߂��ɗ�����C����D�L�[�j
	mHandleId += 2;

	if (key[KEY_INPUT_S] >= 1) {	// �|����\���Ă���Ƃ�
		mIsPreparingWA = true;
	}
	else {	// �|�����Ƃ�
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
			mAX = mX - 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 2);
		}
		else {
			mAX = mX + 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 1);
		}

		mIsPreparingWA = false;
		mIsAttacking = true;
		mAFrameCnt = 90; //����������̍d�����鎞�Ԃ��܂�ł���
	}
}

void Player4::PrepareSAttack() {	// �����U���i�|������܂Ŕ�ԁC����S�L�[�j
	mHandleId += 2;

	if (key[KEY_INPUT_D] >= 1) {
		mIsPreparingSA = true;
	}
	else {	// �|�����Ƃ�
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
			mAX = mX - 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 4);
		}
		else {
			mAX = mX + 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 3);
		}

		mIsPreparingSA = false;
		mIsAttacking = true;
		mAFrameCnt = 120;
	}
}

void Player4::UpdateHit() {
	//HitJudge0::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge1::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge2::SetPlRange(x, y, hitRangeX, hitRangeY);

	//if (godFlag == false) {
	//	eneJudge0 = HitJudge0::PEJudge();
	//	eneJudge1 = HitJudge1::PEJudge();
	//	eneJudge2 = HitJudge2::PEJudge();
	//	eneAJudge0 = HitJudge0::EaPJudge();
	//	eneAJudge1 = HitJudge1::EaPJudge();
	//	eneAJudge2 = HitJudge2::EaPJudge();
	//}

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

	//		ihPower = PowerBox::GetIHPower0();
	//	}
	//	else {
	//		weaponNum = PowerBox::GetWpn1Num();

	//		if (weaponNum == 6) { //6�͎������n��Item��\��
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

	//	if (isPower != 1 && weaponNum == 6) {
	//		iscount = 600;

	//		if (isPower == 2) {
	//			effectHandle = LoadGraph("images/effect_1.png");
	//		}
	//		else {
	//			isPower = 0.5;
	//			effectHandle = LoadGraph("images/effect_2.png");
	//		}
	//	}
	//	else if (iPower != 1 && weaponNum == 6) {
	//		ipcount = 600;
	//		PowerBox::SetPlPower(iPower);
	//		effectHandle = LoadGraph("images/effect_3.png");
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

void Player4::StartBossStage() {

	//attackFlag = mArrow->GetArrowFlag();

	//if (attackFlag == true) {
	//	mArrow->Update();
	//}

	//prev_x = x;
	//prev_y = y;
	//prev_xcount = xcount;
	//prev_ycount = ycount;

	//if (x > 353) {
	//	x -= 2;

	//	/*if (xcount > 0) {
	//	xcount = 0;
	//	}*/
	//	--xcount;
	//}
	//if (x < 349) {
	//	x += 2;

	//	/*if (xcount < 0) {
	//	xcount = 0;
	//	}*/
	//	++xcount;
	//}
	//if (y > 453) {
	//	y -= 2;

	//	/*if (ycount > 0) {
	//	ycount = 0;
	//	}*/
	//	--ycount;
	//}
	//if (y < 449) {
	//	prev_y = y;
	//	y += 2;

	//	/*if (ycount < 0) {
	//	ycount = 0;
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
	//			ix += 8;
	//			handleNumber = ix;
	//		}
	//	}

	//	if (prev_ycount != prev_ycount && ycount != 0) {
	//		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
	//			iy += 8;
	//		}

	//		handleNumber = iy;
	//	}
	//}

	//PlayerData::SetBscount(bscount + 1);
	//bscount++;
}