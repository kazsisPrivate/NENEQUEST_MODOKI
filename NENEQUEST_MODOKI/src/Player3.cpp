// ���i�U���́F���ʁC�U���͈́F�����C�U���������ԁF���������i���̍U���܂łɂ����鎞�ԁF���������j�C������Փx�F�����ȒP�j

#include "Player3.h"
#include "DxLib.h"
#include "PlayerMgr.h"

Player3* Player3::mPlayer3;


Player3::Player3(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 3)) {
	mPlayerMgr = PlayerMgr::GetInstance();
}


Player3::~Player3() {
	delete mPlayer3;
}


Player3* Player3::GetInstance() {
	if (mPlayer3 == NULL) {
		PlayerMgr* playerMgr = PlayerMgr::GetInstance();
		mPlayer3 = new Player3(playerMgr);
		// Initialize��GetInstance�̌Ăяo������SetPlParams�ƂƂ��ɍs���Ă��炤
	}

	return mPlayer3;
}


void Player3::Initialize() {
	Player::Initialize();

	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 35, mHitRangeAH = 60;

	// Player�̍U���̏�Ԑݒ�
	mAttack = 1;
	mAFrameNum = 30;

	// �A�C�e����g�p����̐ݒ�
	mIteKindId = 3;
}


void Player3::Finalize() {
	Player::Finalize();
}


void Player3::Update() {
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


void Player3::Draw() {
	Player::Draw();
}


void Player3::UpdateSAP() {
	Player::UpdateSAP();
}


void Player3::Walk() {
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


void Player3::Attack() {
	Player::Attack();
}


void Player3::Jump() {
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