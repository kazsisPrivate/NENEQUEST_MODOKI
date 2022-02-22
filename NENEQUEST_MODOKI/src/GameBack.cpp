#include "DxLib.h"
#include "GameBack.h"


void GameBack::Initialize() {
	// �w�i�摜�̓ǂݍ���
	mNorStHandles[0] = LoadGraph("images/normalstage.png");
	mNorStHandles[1] = LoadGraph("images/normalstage.png");
	mCloudHandles[0] = LoadGraph("images/clouds1.jpg");
	mCloudHandles[1] = LoadGraph("images/clouds2.jpg");
	mBsStHandle = LoadGraph("images/bossstage.png");

	// �w�i�摜�̈ʒu
	mNorStXs[0] = 0;
	mNorStXs[1] = BACK_X_MAX;
	mCloudXs[0] = 0;
	mCloudXs[1] = BACK_X_MIN;
	mBsStX = BACK_X_MAX;

	// BossStage�ɓ����Ă��邩�֘A�̐ݒ�
	mIsChangingSt = false;
	for (int i = 0; i < 2; i++) {
		mIsMovingNorSts[i] = true;
	}
	//mIsMovingBsSt = false;
	mIsAtBsSt = false;	
}


void GameBack::Finalize() {
	// �w�i�摜�̍폜
	for (int i = 0; i < 2; i++) {
		DeleteGraph(mNorStHandles[i]);
		DeleteGraph(mCloudHandles[i]);
	}
	DeleteGraph(mBsStHandle);
}


void GameBack::Update() {
	if (!mIsAtBsSt) {	// BossStage�łȂ��Ƃ�
		UpdateNormalBack();
	}
	else {	// BossStage�̂Ƃ�
		UpdateBossBack();
	}
}


void GameBack::Draw() {
	// �_�̕`��
	for (int i = 0; i < 2; i++) {
		DrawGraph(mCloudXs[i], 0, mCloudHandles[i], TRUE);
	}

	//// NormalStage�̕`��
	//for (int i = 0; i < 2; i++) {
	//	DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
	//}
	/*DrawGraph(mClouds1X, 0, mCl1Handle, TRUE);
	DrawGraph(mClouds2X, 0, mCl2Handle, TRUE);*/
	
	if (mIsChangingSt) {	// BossStage�Ɉڍs���̂Ƃ�
		// BossStage�̕`��
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
		//if (mIsMovingBsSt) {	// BossStage�̉摜�𓮂����Ă���Ƃ�
		//	DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
		//}
		
		// NormalStage�̕`��
		for (int i = 0; i < 2; i++) {
			if (mIsMovingNorSts[i]) {	// NormalStage�̉摜�𓮂����Ă���Ƃ�
				DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
			}
		}
		/*if (mMountain1X != END_LEFT_X && mMountain1X != END_RIGHT_X) {
			DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		}
		else if (mMountain2X != END_LEFT_X && mMountain2X != END_RIGHT_X) {
			DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);
		}*/

	}
	else if (!mIsAtBsSt) {	// NormalStage�ł���Ƃ��iBossStage�łȂ��Ƃ��j
		// NormalStage�̕`��
		for (int i = 0; i < 2; i++) {
			DrawGraph(mNorStXs[i], 0, mNorStHandles[i], TRUE);
		}
		//// �R�̕`��
		//for (int i = 0; i < 2; i++) {
		//	DrawGraph(mMountainXs[i], 0, mMountainHandles[i], TRUE);
		//}
		/*DrawGraph(mMountain1X, 0, mMo1Handle, TRUE);
		DrawGraph(mMountain2X, 0, mMo2Handle, TRUE);*/
	}
	else {	// BossStage�̂Ƃ�
		// BossStage�̕`��
		DrawGraph(mBsStX, 0, mBsStHandle, TRUE);
	}

	//DrawFormatString(500, 200, GetColor(255, 255, 255), "ys = %d", mBackChCnt);
}


void GameBack::UpdateNormalBack() {
	if (mIsChangingSt) {	// BossStage�ւ̕ύX���̂Ƃ�
		// NormalStage�Ɖ_�̈ʒu�̍X�V
		for (int i = 0; i < 2; i++) {
			if (mIsMovingNorSts[i]) {	// NormalStage�̉摜�𓮂����Ă���Ƃ�
				mNorStXs[i] -= 1;
			}
			
			mCloudXs[i] -= 0.5f;
		}

		//for (int i = 0; i < 2; i++) {
		//	if (mIsMovingNorSts[i] &&	// NormalStage�̉摜�𓮂����Ă���Ƃ���
		//		mNorStXs[i] < BACK_X_MAX - BRIDGE_LX && mNorStXs[i] > 0) {	// ��ʓ��ŋ����f�肱�܂Ȃ��Ƃ�
		//		// BossStage�̉摜�𓮂��n�߂�����
		//		mIsMovingBsSt = true;
		//		mBsStX = mNorStXs[i];

		//		// NormalStage�̉摜�̓������~�߂�
		//		mIsMovingNorSts[i] = false;
		//		mNorStXs[i] = BACK_X_MAX;
		//	}
		//}

		// NormalStage�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
		for (int i = 0; i < 2; i++) {
			if (mNorStXs[i] <= BACK_X_MIN) {
				// NormalStage�̉摜�̓������~�߂�
				mIsMovingNorSts[i] = false;
				mNorStXs[i] = BACK_X_MAX;
				
				//if (!mIsMovingBsSt) {	// BossStage�̉摜�𓮂��o�����Ă��Ȃ����
				//	mIsMovingBsSt = true;
				//}

				break;
			}
		}

		// �_�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
		for (int i = 0; i < 2; i++) {
			if (mCloudXs[i] <= BACK_X_MIN) {
				mCloudXs[i] = BACK_X_MAX;
			}
		}

		// BossStage�̈ʒu�̍X�V
		if (mBsStX > 0) {	// ��ʂ̍��[��BossStage�̉摜�������Ă��Ȃ����(BossStage�̔w�i�ւ̈ڍs���I����Ă��Ȃ����)
			mBsStX -= 1;
		}
		else {	// ��ʂ̍��[��BossStage�̉摜�������Ă����
			// BossStage�ւ̈ڍs���I������
			//mIsMovingBsSt = false;
			mIsChangingSt = false;
			// BossStage�ɓ��������Ƃɂ���
			mIsAtBsSt = true;
		}
	}
	else {	// BossStage�łȂ��CBossStage�֕ύX���łȂ��Ƃ�
		// �ʒu�̍X�V
		for (int i = 0; i < 2; i++) {
			mNorStXs[i] -= 1;
			mCloudXs[i] -= 0.5f;
		}

		// �R�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
		for (int i = 0; i < 2; i++) {
			if (mNorStXs[i] <= BACK_X_MIN) {
				mNorStXs[i] = BACK_X_MAX;
			}
		}

		// �_�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
		for (int i = 0; i < 2; i++) {
			if (mCloudXs[i] <= BACK_X_MIN) {
				mCloudXs[i] = BACK_X_MAX;
			}
		}
	}

	// �ʒu�̍X�V
	/*mMountain1X -= 1;
	mMountain2X -= 1;
	mClouds1X -= 0.5f;
	mClouds2X -= 0.5f;*/

	// �R�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
	/*if (mMountain1X <= END_LEFT_X) {
		mMountain1X = END_RIGHT_X;
		mBackChCnt++;
	}
	else if (mMountain2X <= END_LEFT_X) {
		mMountain2X = END_RIGHT_X;
		mBackChCnt++;
	}*/

	// �_�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
	/*if (mClouds1X <= END_LEFT_X) {
		mClouds1X = END_RIGHT_X;
	}
	else if (mClouds2X <= END_LEFT_X) {
		mClouds2X = END_RIGHT_X;
	}*/

	// BossStage�Ɉڍs���邩���Ȃ����̔���
	/*if (mBackChCnt == 1) {
		mIsBossStage = true;
		PlayerData::SetBossFlag(true);
		EnemyData::SetBossFlag(true);
	}*/
}

void GameBack::UpdateBossBack() {
	// �_�̈ʒu�̍X�V
	for (int i = 0; i < 2; i++) {
		mCloudXs[i] -= 0.5f;
	}

	// �_�̉摜���ړ��͈͂̍��[�ɍs���Ă����ۂ̏���
	for (int i = 0; i < 2; i++) {
		if (mCloudXs[i] <= BACK_X_MIN) {
			mCloudXs[i] = BACK_X_MAX;
		}
	}

	//if (mUpdFraCnt <= END_RIGHT_X) { //mountain�̔w�i���[����[�܂ňړ����I���̂ɂ����鎞��
	//	if (mUpdFraCnt % UPDATE_FRAME_NUM == 0) {
	//		mClouds1X -= 1;
	//		mClouds2X -= 1;
	//		mBoStX -= 2;

	//		if (mMountain1X == END_RIGHT_X) {//END_LEFT_X����END_RIGHT_X�Ɉړ�����Ă���͂�������
	//			mMountain2X -= 2;
	//		}
	//		else { //mMountain2X == END_RIGHT_X�@�̂Ƃ�
	//			mMountain1X -= 2;
	//		}

	//		if (mClouds1X == END_LEFT_X) {
	//			mClouds1X = END_RIGHT_X;
	//		}
	//		else if (mClouds2X == END_LEFT_X) {
	//			mClouds2X = END_RIGHT_X;
	//		}
	//	}
	//}
	//else {
	//	if (mUpdFraCnt % UPDATE_FRAME_NUM == 0) {
	//		mClouds1X -= 1;
	//		mClouds2X -= 1;

	//		if (mClouds1X == END_LEFT_X) {
	//			mClouds1X = END_RIGHT_X;
	//		}
	//		else if (mClouds2X == END_LEFT_X) {
	//			mClouds2X = END_RIGHT_X;
	//		}

	//		mUpdFraCnt = END_RIGHT_X; //�������Ă����mUpdFraCnt�� 1281��1282��1281�@�ƃ��[�v���Ă����悤�ɂł���
	//	}
	//}

	//mUpdFraCnt++;
}


void GameBack::StartChangingSt() {
	// BossStage�̔w�i�摜��x���W���Z�b�g����
	bool hasSetBsStX = false;	// BossStage�̔w�i�摜��x���W���Z�b�g�������ǂ���
	// NormalStage�̔w�i�摜�Ɠ���ւ�����ʒu��NormalStage�̔w�i�摜������Ό�������
	for (int i = 0; i < 2; i++) {
		if (mIsMovingNorSts[i] &&	// NormalStage�̉摜�𓮂����Ă���Ƃ���
			mNorStXs[i] < BACK_X_MAX && mNorStXs[i] > BACK_X_MAX - BRIDGE_LX) {	// ��ʓ��ŋ����f�肱�܂Ȃ��Ƃ�
			// BossStage�̉摜���Z�b�g����
			mBsStX = mNorStXs[i];
			hasSetBsStX = true;

			// BossStage�Ƃ��ꂩ���ĉf���K�v�̂Ȃ��Ȃ���NormalStage�̉摜�̓������~�߂�
			mIsMovingNorSts[i] = false;
			mNorStXs[i] = BACK_X_MAX;
		}
	}
	if (!hasSetBsStX) {	// BossStage�̉摜��x���W���Z�b�g���Ă��Ȃ�������
		// 2��NormalStage�̉摜�E���ɂ���摜�̉E�[��x���W��BossStage��x���W�Ƃ��ăZ�b�g����
		if (mNorStXs[0] > mNorStXs[1]) {
			mBsStX = mNorStXs[0] + STAGE_IMG_W;
		}
		else {
			mBsStX = mNorStXs[1] + STAGE_IMG_W;
		}
	}

	// BossStage�ֈڍs�����n�߂�
	mIsChangingSt = true;
}


int GameBack::GetBsStX() {
	return mBsStX;
}


bool GameBack::GetIsAtBsSt() {
	return mIsAtBsSt;
}