// ��1�i�U���́F���ʁC�U���͈́F�����L���C�U���������ԁF���ʁi���̍U���܂łɂ����鎞�ԁF���ʁj�C������Փx�F���ʁj

#include "Player1.h"
#include "DxLib.h"
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
	Player::Initialize();

	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 50, mHitRangeAH = 60;

	// Player�̍U���̏�Ԑݒ�
	mAttack = 1;
	mAFrameNum = 20;
	
	// �A�C�e����g�p����̐ݒ�
	mIteKindId = 1;
}


void Player1::Finalize() {
	Player::Finalize();
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
			// �������������Ƃ�
			if (mIteKindId == 2) {
				mPlayerChanger->ChangePlayer(ePlayer2);
			}
			else if (mIteKindId == 3) {
				mPlayerChanger->ChangePlayer(ePlayer3);
			}
			else if (mIteKindId == 4) {
				mPlayerChanger->ChangePlayer(ePlayer4);
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

	// �_���[�W���󂯂���̏����̊Ԃ̖��G���Ԃ̏���
	if (mIsGod == true) {
		if (mGodFrameCnt == -1) {
			mIsGod = false;
		}
		else if (mGodFrameCnt > 80 || (mGodFrameCnt <= 60 && mGodFrameCnt > 40) || mGodFrameCnt <= 20) {	// Player�𔒂�����
			mHandleId += 12;
			--mGodFrameCnt;
		}
		else {
			--mGodFrameCnt;
		}
	}
}


void Player1::Draw() {
	Player::Draw();
}


void Player1::UpdateSAP() {
	Player::UpdateSAP();
}


void Player1::Walk() {
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
		ix += 6;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// ���������Ă���Ƃ�
			iy += 6;
		}
		
		mHandleId = iy;
	}
}


void Player1::Attack() {
	Player::Attack();
}


void Player1::Jump() {
	// �\������player�̉摜�ԍ��̍X�V���s��
	if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// ���������Ă���Ƃ�
		mHandleId = 10;
	}
	else {	// �E�������Ă���Ƃ�
		mHandleId = 4;
	}

	// player�̍��W�̍X�V���s��
	Player::Jump();
}