#include "Player.h"
#include "DxLib.h"
#include "PlayerMgr.h"
#include "EffectGraphics.h"


Player::Player(PlayerChanger* changer, const int* graph) : mPlHandle(graph) {
	mPlayerChanger = changer;
	mPlayerMgr = PlayerMgr::GetInstance();
}


void Player::Initialize() {
	// �ʒu�C�����蔻��͈̔͊֘A�ݒ�
	mAX = mX + 160;
	mAY = mY + 20;
	mImgW = 500, mImgH = 283;

	// Player�̍U���C�W�����v�Ȃǂ̏�Ԑݒ�
	mXFrameCnt = 0, mYFrameCnt = 0;
	mAFrameCnt = 0;
	mIsJumping = false;
	mIsAttacking = false;
	mHandleId = 0;
	mSpeed = 4.0f;

	// �A�C�e����g�p����̐ݒ�
	mIteHP = 0;
	mEneDamage = 0;

	if (mEffectFrameCnt > 0) {
		mIsEffected = true;
	}
	else {
		mIsEffected = false;
	}

	if (mEffectId == 0) {
		mIteSP = 1.0f;
		mIteAP = 1;
		mEffectHandle = NULL;
	}
	else if (mEffectId == 1) {
		mIteSP = 2.0f;
		mIteAP = 1;
		mEffectHandle = EffectGraphics::GetGraHandle(1);
	}
	else if (mEffectId == 2) {
		mIteSP = 0.5f;
		mIteAP = 1;
		mEffectHandle = EffectGraphics::GetGraHandle(2);
	}
	else {
		mIteSP = 1.0f;
		mIteAP = 2;
		mEffectHandle = EffectGraphics::GetGraHandle(3);
	}

	// ���ێ��Ɏg�p����map(vector), �z��̏�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneIsHits[i] = false;
		mEneAIsHits[i] = false;
		mPlAIsHitMap["enemy"].push_back(false);
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mIteIsHits[i] = false;
		mIteDataMaps.push_back({});
		mPlAIsHitMap["item"].push_back(false);
	}
}


void Player::Finalize() {
}


void Player::Draw() {
	// Player�̉摜�\��
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 13, mPlHandle[mHandleId], TRUE);

	// �����蔻��̕`��i�f�o�b�O�p�j
	/*DrawBox(mX - mHitRangeW, mY - mHitRangeH,
		mX + mHitRangeW, mY + mHitRangeH, GetColor(255, 0, 0), FALSE);*/

	// Effect�̉摜�\��
	if (mIsEffected) {	// Item�̌��ʒ��̂Ƃ�
		DrawGraph(mX - 114, mY - 113, *mEffectHandle, TRUE);
	}
}


void Player::UpdateSAP() {
	// �ړ����x�̍X�V
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// ���E�̓��͂�����Ƃ�
		if (mIsJumping) {	// �W�����v���Ă���Ƃ�
			mSpeed = 4 * 0.8f * mSpeedRate;
		}
		else if (mIsAttacking) {	// �U�����Ă���Ƃ�
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
		if (mIsAttacking) {	// �U�����Ă���Ƃ�
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 0.80f * mSpeedRate;
		}
	}

	// �U���͂̍X�V
	mAttack = mAttackBase;

	// �ړ����x�i�A�C�e�����ʁj�̍X�V
	mSpeed *= mIteSP;

	// �U���́i�A�C�e�����ʁj�̍X�V
	mAttack *= mIteAP;
}


void Player::Walk() {
	// stage���Ƃɍ\�����ς�邽�߁Cstage�̈ړ��͈͂ɍ��킹��player�̍��W�X�V���s��
	if (!mIsAtBsSt) {	// boss stage�ł͂Ȃ��Ƃ�
		if (key[KEY_INPUT_LEFT] != 0) {	// �����Ɉړ�����Ƃ�
			if (mX > X_MIN_N) {	// ���[�łȂ��Ƃ�
				mX -= (int)(mSpeed);
			}

			if (mX < X_MIN_N) mX = X_MIN_N;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {	// �E���Ɉړ�����Ƃ�
			if (mX < X_MAX_N) {	// �E�[�łȂ��Ƃ�
				mX += (int)(mSpeed);
			}

			if (mX > X_MAX_N) mX = X_MAX_N;

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && !mIsJumping) {	// �㑤�Ɉړ�����Ƃ��ŃW�����v���łȂ��Ƃ�
			if (mY > Y_MIN_N) {	// ��[�łȂ��Ƃ�
				mY -= (int)(mSpeed);
			}

			if (mY < Y_MIN_N) mY = Y_MIN_N;

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && !mIsJumping) {	// �����Ɉړ�����Ƃ��ŃW�����v���łȂ��Ƃ�
			if (mY < Y_MAX_N) {	// ���[�łȂ��Ƃ�
				mY += (int)(mSpeed);
			}

			if (mY > Y_MAX_N) mY = Y_MAX_N;

			if (mYFrameCnt < 0) {
				mYFrameCnt = 0;
			}
			++mYFrameCnt;
		}
	}
	else {	// boss stage�̂Ƃ�
		if (key[KEY_INPUT_LEFT] != 0) {	// �����Ɉړ�����Ƃ�
			if (mX > X_MIN_B) {	// ���[�łȂ��Ƃ�
				mX -= (int)(mSpeed);
			}

			if (mX < X_MIN_B) mX = X_MIN_B;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {	// �E���Ɉړ�����Ƃ�
			if (mIsJumping) {	// �W�����v���̂Ƃ�
				if (mX < X_MAX_B) {	// �E�[�łȂ��Ƃ�
					mX += (int)(mSpeed);

					if (mX > X_MAX_B) mX = X_MAX_B;
				}
				else if (mX < X_MAX_BR && mYStart >= Y_MIN_BR && mYStart <= Y_MAX_BR) {	// �W�����v�O�ɋ��̏�ɂ����Ƃ�
					mX += (int)(mSpeed);

					if (mX > X_MAX_BR) mX = X_MAX_BR;
				}
			}
			else {	// �W�����v���łȂ��Ƃ�
				if (mX < X_MAX_B) {	// �E�[�łȂ��Ƃ�
					mX += (int)(mSpeed);

					if (mX > X_MAX_B) mX = X_MAX_B;
				}
				else if (mX < X_MAX_BR && mY >= Y_MIN_BR && mY <= Y_MAX_BR) {	// ���̏�ɂ���Ƃ�
					mX += (int)(mSpeed);

					if (mX > X_MAX_BR) mX = X_MAX_BR;
				}
			}

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && !mIsJumping) {	// �㑤�Ɉړ�����Ƃ��ŃW�����v���łȂ��Ƃ�
			if (mY > Y_MIN_B && mX <= X_MAX_B) {	// ���ɂ��Ȃ��āC��[�łȂ��Ƃ�
				mY -= (int)(mSpeed);

				if (mY < Y_MIN_B) mY = Y_MIN_B;	// �X�V����
			}
			else if (mY > Y_MIN_BR && mX <= X_MAX_BR) {	// ���̏�ɂ��āC���̉E�[�łȂ��Ƃ�
				mY -= (int)(mSpeed);

				if (mY < Y_MIN_BR) mY = Y_MIN_BR;
			}

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && !mIsJumping) {	// �����Ɉړ�����Ƃ��ŃW�����v���łȂ��Ƃ�
			if (mY < Y_MAX_B && mX <= X_MAX_B) {	// ���ɂ��Ȃ��āC���[�łȂ��Ƃ�
				mY += (int)(mSpeed);

				if (mY > Y_MAX_B) mY = Y_MAX_B;
			}
			else if (mY < Y_MAX_BR && mX <= X_MAX_BR) {	// ���̏�ɂ��āC���̍��[�łȂ��Ƃ�
				mY += (int)(mSpeed);

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
	if (mIsJumping) {
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


void Player::UpdateIteEffect() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsHits[i]) {	// Item�ɓ������Ă�����
			int itemId = (int)mIteDataMaps.at(i)["itemId"];

			// �󂯎����Item�̎�ނɍ��킹���X�V���s��
			if (itemId <= 4) {	// �񕜌n�A�C�e��
				mIteKindId = 5;

				// �񕜗ʂ̐ݒ�
				mIteHP = (int)mIteDataMaps.at(i)["healPower"];
			}
			else if (itemId <= 7) {	// �������n�A�C�e��
				mIteKindId = 5;

				// ���ʂ̏������̐ݒ�
				mEffectId = itemId - 4;
				mIsEffected = true;
				mEffectFrameCnt = 0;
					
				// �������nItem�̌��ʂ̐ݒ�
				mIteAP = (int)mIteDataMaps.at(i)["attackPower"];
				mIteSP = mIteDataMaps.at(i)["speedPower"];

				// �摜�̐ݒ�
				mEffectHandle = EffectGraphics::GetGraHandle(mEffectId);
			}
			else if (itemId <= 11) {	// ����
				mIteKindId = itemId - 7;
			}
			else {	// ��
				mIteKindId = 5;
			}
		}
	}

	// Item�̎������n���ʂ̍X�V
	if (mIsEffected) {
		if (mEffectFrameCnt <= EFFECT_FRAME_NUM) {
			mEffectFrameCnt++;
		}
		else {
			mIteAP = 1;
			mIteSP = 1.0f;
			mIsEffected = false;
			mEffectHandle = NULL;
		}
	}
}


void Player::UpdateEneDamage() {
	if (!mIsGod) {	// ���G���ԂłȂ��Ƃ�
		// Enemy�̐g�̂ƍU���Ƃ̓����蔻��
		for (int i = 0; i < ENEMY_NUM; i++) {
			// Enemy�̐g�̂Ƃ̓����蔻��
			if (mEneIsHits[i]) {	// Enemy�̐g�̂ɂ������Ă�����
				mEneDamage = 1;
			}

			// Enemy�̍U���Ƃ̓����蔻��
			if (mEneAIsHits[i]) {
				mEneDamage = mEneAPs[i];
			}
		}
	}
}


void Player::UpdateHp() {
	// �A�C�e���ɂ���
	if (mIteHP != 0) {
		mHp += mIteHP;

		mIteHP = 0;

		if (mIteHP < 0) {	// �A�C�e���ɂ���ă_���[�W���󂯂���
			// �����̊Ԗ��G�ɂȂ�
			mIsGod = true;
			mGodFrameCnt = 0;
		}
	}

	// �G�ɂ��_���[�W
	if (mEneDamage != 0) {
		mHp -= mEneDamage;

		mEneDamage = 0;
		// �����̊Ԗ��G�ɂȂ�
		mIsGod = true;
		mGodFrameCnt = 0;
	}

	// �̗͂̕␳
	if (mHp > HP_MAX) {	// hp�̏���𒴂����Ƃ�
		mHp = HP_MAX;
	}
	else if (mHp < 0) {	// hp��0�����ɂȂ�����
		mHp = 0;
	}
}


void Player::SetPlParams(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	// �p�����[�^�Ŏ󂯎�����l��������
	mX = (*plIntDataMap)["x"];
	mY = (*plIntDataMap)["y"];
	mHp = (*plIntDataMap)["hp"];
	mEffectFrameCnt = (*plIntDataMap)["effectFrameCnt"];
	mBsStopFrameCnt = (*plIntDataMap)["bsStopFrameCnt"];
	mEffectId = (*plIntDataMap)["effectId"];
	mGodFrameCnt = (*plIntDataMap)["godFrameCnt"];

	mIsDead = (*plBoolDataMap)["isDead"];
	mIsGod = (*plBoolDataMap)["isGod"];
	mIsChangingSt = (*plBoolDataMap)["isChanginSt"];
	mIsAtBsSt = (*plBoolDataMap)["isAtBsSt"];
}


void Player::GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	(*plIntDataMap)["x"] = mX;
	(*plIntDataMap)["y"] = mY;
	(*plIntDataMap)["ax"] = mAX;
	(*plIntDataMap)["ay"] = mAY;
	(*plIntDataMap)["hp"] = mHp;
	(*plIntDataMap)["hitRangeW"] = mHitRangeW;
	(*plIntDataMap)["hitRangeH"] = mHitRangeH;
	(*plIntDataMap)["hitRangeAW"] = mHitRangeAW;
	(*plIntDataMap)["hitRangeAH"] = mHitRangeAH;
	(*plIntDataMap)["effectFrameCnt"] = mEffectFrameCnt;
	(*plIntDataMap)["bsStopFrameCnt"] = mBsStopFrameCnt;
	(*plIntDataMap)["effectId"] = mEffectId;
	(*plIntDataMap)["attack"] = mAttack;
	(*plIntDataMap)["godFrameCnt"] = mGodFrameCnt;

	(*plBoolDataMap)["isDead"] = mIsDead;
	(*plBoolDataMap)["isAttacking"] = mIsAttacking;
	(*plBoolDataMap)["isGod"] = mIsGod;
	(*plBoolDataMap)["isChanginSt"] = mIsChangingSt;
	(*plBoolDataMap)["isAtBsSt"] = mIsAtBsSt;
}


void Player::GetPlIntDataMap(std::map<std::string, int>* plIntDataMap) {
	(*plIntDataMap)["x"] = mX;
	(*plIntDataMap)["y"] = mY;
	(*plIntDataMap)["ax"] = mAX;
	(*plIntDataMap)["ay"] = mAY;
	(*plIntDataMap)["hp"] = mHp;
	(*plIntDataMap)["hitRangeW"] = mHitRangeW;
	(*plIntDataMap)["hitRangeH"] = mHitRangeH;
	(*plIntDataMap)["hitRangeAW"] = mHitRangeAW;
	(*plIntDataMap)["hitRangeAH"] = mHitRangeAH;
	(*plIntDataMap)["effectFrameCnt"] = mEffectFrameCnt;
	(*plIntDataMap)["bsStopFrameCnt"] = mBsStopFrameCnt;
	(*plIntDataMap)["effectId"] = mEffectId;
	(*plIntDataMap)["attack"] = mAttack;
	(*plIntDataMap)["godFrameCnt"] = mGodFrameCnt;
}


void Player::SetIsHits(std::map<std::string, std::vector<bool>>* isHitMap) {
	// �eEnemy�Ƃ̓����蔻����Z�b�g
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneIsHits[i] = (*isHitMap)["enemy"].at(i);
		mEneAIsHits[i] = (*isHitMap)["enemyAttack"].at(i);
		mPlAIsHitMap["enemy"].at(i) = (*isHitMap)["plAToEnemy"].at(i);
	}

	// �eItem�Ƃ̓����蔻����Z�b�g
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteIsHits[i] = (*isHitMap)["item"].at(i);
		mPlAIsHitMap["item"].at(i) = (*isHitMap)["plAToItem"].at(i);
	}
}


void Player::SetIteParams(std::vector<std::map<std::string, float>>& iteDataMaps) {
	// �eItem�̌��ʂ̏����Z�b�g
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.at(i)["healPower"] = iteDataMaps.at(i)["healPower"];
		mIteDataMaps.at(i)["speedPower"] = iteDataMaps.at(i)["speedPower"];
		mIteDataMaps.at(i)["attackPower"] = iteDataMaps.at(i)["attackPower"];
		mIteDataMaps.at(i)["itemId"] = iteDataMaps.at(i)["itemId"];
	}
}


void Player::SetEneAPowers(const int* const eneAPs) {
	// �eEnemy�̍U���͂̃Z�b�g
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneAPs[i] = eneAPs[i];
	}
}


void Player::SetIsChangingSt(const bool isChangingSt) {
	// BossStage�֕ύX�����ǂ����Z�b�g
	mIsChangingSt = isChangingSt;
}


void Player::SetIsAtBsSt(const bool isAtBsSt) {
	// BossStage�ɓ����Ă��邩�ǂ����Z�b�g
	mIsAtBsSt = isAtBsSt;
}