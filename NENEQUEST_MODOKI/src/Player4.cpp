#include "Player4.h"
#include "DxLib.h"
#include "PlayerMgr.h"


Player4* Player4::mPlayer4;


Player4::Player4(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 4)) {
}


Player4* Player4::GetInstance() {
	if (!mPlayer4) {
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
	mHitRangeAW = 20, mHitRangeAH = 20;	// �|��̓����蔻��

	// Player�̍U���̏�Ԑݒ�
	mAttackBase = 1;
	mAttack = mAttackBase;
	// mAFrameNum �͋����|�F120�C�ア�|�F90

	// Player�̈ړ����x�{��
	mSpeedRate = 1.0f;

	// �A�C�e����g�p����̐ݒ�
	mIteKindId = 4;
	// �|�֘A�̐ݒ�
	mIsPreparingWA = false;
	mIsPreparingSA = false;
	mArrow = new Arrow();
	mArrow->Initialize();
	mArrowExists = false;
	mArrowIsHit = false;
}


void Player4::Finalize() {
	Player::Finalize();

	delete mArrow;
	delete mPlayer4;
	mPlayer4 = NULL;
}


void Player4::Update() {
	if (mHp <= 0) {	// ���񂾂Ƃ��̏����i���񂾂��Ƃ�F�������邽�߂�120�t���[���̍d���j
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		else if (mGodFrameCnt == 0) {	// �ŏ��ɒʂ����Ƃ�
			// �_���[�W������������Ƃ��킩��摜�ɂ���
			mHandleId += 16;
		}

		mGodFrameCnt++;
	}
	else {	// �����Ă���Ƃ��̏���
		if (mIsChangingSt) {	// BossStage�̎n�܂�ۂ̋����I�Ȉړ�����
			StartBossStage();
		}
		else {
			// Enemy�Ƃ̓����蔻����l������Enemy����󂯂�_���[�W�̍X�V
			UpdateEneDamage();

			// �A�C�e���Ƃ̓����蔻����l�������A�C�e���̌��ʂ̍X�V
			UpdateIteEffect();

			// hp�̍X�V
			UpdateHp();

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
			if (!mIsAttacking && (mIsJumping || key[KEY_INPUT_A] == 1)) {	// �U�����łȂ��C���W�����v���C�������̓W�����v���̓L�[�������Ă���Ƃ�
				Jump();
			}
			else if (mIsAttacking) {	// �U�����ł���Ƃ��i�|�����������Ɓj
				Attack();

				if (mArrowExists) {	// �|��̍U�����c���Ă���Ƃ�
					mArrow->Update();

					// �U�����W�̍X�V
					std::tie(mAX, mAY) = mArrow->GetArrowXY();

					if (!mArrowIsHit) {	// �|����ɂ��������Ă��Ȃ��Ƃ�
						UpdateArrowIsHit();
					}
				}

				// �U�����Ԃ��I������玟�̍U�����ł���悤�ɂ���
				if (mAFrameCnt == mAFrameNum) {
					mIsAttacking = false;
					mArrowIsHit = false;
				}
			}
			else if ((key[KEY_INPUT_S] == 1 || mIsPreparingWA) && !mIsPreparingSA) {	//	�ア�|��łƂ��Ƃ��Ă���Ƃ�
				PrepareWAttack();
			}
			else if (key[KEY_INPUT_D] == 1 || mIsPreparingSA) {	// �����|��łƂ��Ƃ��Ă���Ƃ�
				PrepareSAttack();
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
						mHandleId += 16;
					}
				}

				mGodFrameCnt++;
			}
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
		if (mIsJumping) {	// �W�����v���Ă���Ƃ�
			mSpeed = 4 * 0.8f * mSpeedRate;
		}
		else if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// �U�����Ă���Ƃ�or�U���������̂Ƃ�
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// �㉺�̓��͂�����Ƃ�
			mSpeed = 4 * 0.625f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 1.0f * mSpeedRate;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// �㉺�̓��͂�����Ƃ�
		if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// �U�����Ă���Ƃ�or�U���������̂Ƃ�
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 0.80f * mSpeedRate;
		}
	}

	// �ړ����x�i�A�C�e�����ʁj�̍X�V
	mSpeed *= mIteSP;

	// �U���͂̍X�V
	mAttack = mAttackBase;

	// �U���́i�A�C�e�����ʁj�̍X�V
	mAttack *= mIteAP;
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
	
	mAFrameCnt++;
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
		mAFrameCnt = 0;
		mAFrameNum = 90; //����������̍d�����鎞�Ԃ��܂�ł���
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
		mAFrameCnt = 0;
		mAFrameNum = 120;
	}
}


void Player4::UpdateArrowIsHit() {
	// �|��-Enemy��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mPlAIsHitMap["enemy"].at(i)) {
			mArrowIsHit = true;
		}
	}
	// �|��-Item��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mPlAIsHitMap["item"].at(i)) {
			mArrowIsHit = true;
		}
	}

	mArrow->SetIsHit(mArrowIsHit);
}


void Player4::GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	Player::GetPlDataMap(plIntDataMap, plBoolDataMap);

	// �|������Ă���Ԃ̂ݓ����蔻��̂���U�����Ƃ݂Ȃ�
	(*plBoolDataMap)["isAttacking"] = mArrow->GetIsMoving();
}


void Player4::StartBossStage() {
	// �|��̍X�V
	mArrowExists = mArrow->GetArrowExists();

	if (mArrowExists) {
		mArrow->Update();
	}

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
		mHandleId = 8;

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
		ix += 8;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// ���������Ă���Ƃ�
			iy += 8;
		}

		mHandleId = iy;
	}

	mIsAttacking = false;
	mIsJumping = false;
	mIsGod = false;
	mGodFrameCnt = 0;
}