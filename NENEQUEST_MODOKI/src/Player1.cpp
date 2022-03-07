#include "Player1.h"
#include "DxLib.h"
#include "PlayerMgr.h"

Player1* Player1::mPlayer1;


Player1::Player1(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 1)) {
}


Player1* Player1::GetInstance() {
	if (!mPlayer1) {
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
	mAttackBase = 1;
	mAttack = mAttackBase;
	mAFrameNum = 20;
	
	// Player�̈ړ����x�{��
	mSpeedRate = 1.0f;

	// �A�C�e����g�p����̐ݒ�
	mIteKindId = 1;
}


void Player1::Finalize() {
	Player::Finalize();

	delete mPlayer1;
	mPlayer1 = NULL;
}


void Player1::Update() {
	if (mHp <= 0) {	// ���񂾂Ƃ��̏����i���񂾂��Ƃ�F�������邽�߂�120�t���[���̍d���j
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		else if (mGodFrameCnt == 0) {	// �ŏ��ɒʂ����Ƃ�
			// �_���[�W������������Ƃ��킩��摜�ɂ���
			mHandleId += 12;
		}

		mGodFrameCnt++;
	}
	else {	// �����Ă���Ƃ��̏���
		// Enemy�Ƃ̓����蔻����l������Enemy����󂯂�_���[�W�̍X�V
		UpdateEneDamage();

		// Item�Ƃ̓����蔻����l�������A�C�e���̌��ʂ̍X�V
		UpdateIteEffect();

		// hp�̍X�V
		UpdateHp();
		
		if (mIsChangingSt) {	// BosStage�̎n�܂�ۂ̋����I�Ȉړ�����
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
			if (!mIsAttacking && (mIsJumping || key[KEY_INPUT_A] == 1)) {	// �U�����łȂ��C���W�����v���C�������̓W�����v���̓L�[�������Ă���Ƃ�
				Jump();
			}
			else if (mIsAttacking || key[KEY_INPUT_S] == 1) {	// �U�����ł��邩�C�U���L�[�������Ă���Ƃ�
				Attack();
			}

			// �_���[�W���󂯂���̏����̊Ԃ̖��G���Ԃ̏���
			if (mIsGod) {	// �U�����󂯂���̖��G���Ԃ̂Ƃ�
				if (mGodFrameCnt == GOD_FRAME_NUM) {	// ���G���Ԃ��I�������
					mIsGod = false;
					mGodFrameCnt = 0;
				}
				else {	// ���G���Ԓ��Ȃ�
					// ���G���Ԃł��邱�Ƃ�\���摜�ɂ���
					if ((mGodFrameCnt / 20) % 2 == 0) {	// �_�ŏ���
						mHandleId += 12;
					}
				}

				mGodFrameCnt++;
			}
		}
	}

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


void Player1::StartBossStage() {
	// x���W�̍X�V
	if (mX < PL_FIRST_X_AT_BSST - SPEED_CHANGING_ST) {	// �Z�b�g�������ʒu�t�߂�荶���ɂ�����
		mX += SPEED_CHANGING_ST;
		mHandleId = 0;

		if (mXFrameCnt < 0) {	// BossStage�ɓ������Ƃ���mXFrameCnt��0��菬�����Ƃ��iPlayer�������Ɉړ����������Ƃ��j
			mXFrameCnt = 0;
		}

		mXFrameCnt++;
	}
	else if (mX > PL_FIRST_X_AT_BSST + SPEED_CHANGING_ST) {	// �Z�b�g�������ʒu�t�߂��E���ɂ�����
		mX -= SPEED_CHANGING_ST;
		mHandleId = 6;

		if (mXFrameCnt > 0) {	// BossStage�ɓ������Ƃ���mXFrameCnt��0���傫���Ƃ��iPlayer���E���Ɉړ����������Ƃ��j
			mXFrameCnt = 0;
		}

		mXFrameCnt--;
	}
	else {
		mHandleId = 0;
		mXFrameCnt = 0;
	}

	// y���W�̍X�V
	if (mY < PL_FIRST_Y_AT_BSST - SPEED_CHANGING_ST) {	// �Z�b�g�������ʒu�t�߂��㑤�ɂ�����
		mY += SPEED_CHANGING_ST;

		if (mYFrameCnt < 0) {	// BossStage�ɓ������Ƃ���mXFrameCnt��0��菬�����Ƃ��iPlayer���㑤�Ɉړ����������Ƃ��j
			mYFrameCnt = 0;
		}

		mYFrameCnt++;
	}
	else if (mY > PL_FIRST_Y_AT_BSST + SPEED_CHANGING_ST) {	// �Z�b�g�������ʒu�t�߂�艺���ɂ�����
		mY -= SPEED_CHANGING_ST;

		if (mYFrameCnt > 0) {	// BossStage�ɓ������Ƃ���mXFrameCnt��0��菬�����Ƃ��iPlayer�������Ɉړ����������Ƃ��j
			mYFrameCnt = 0;
		}

		mYFrameCnt--;
	}
	else {
		mYFrameCnt = 0;
	}

	// �\������player�̉摜�ԍ��̍X�V���s��
	int ix = abs(mXFrameCnt) % 40 / 20;
	int iy = abs(mYFrameCnt) % 40 / 20;

	if (mXFrameCnt != 0) {
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		mHandleId = iy;
	}

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

	mIsAttacking = false;
	mIsJumping = false;
	mIsGod = false;
	mGodFrameCnt = 0;
}