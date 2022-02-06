#include "Arrow.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <math.h>

#define PI 3.14159265358979323846


void Arrow::Initialize() {
	// �|����݂��Ă��Ȃ���Ԃɏ�����
	mArrowExists = false;

	// �|��̉摜�ⓖ�������Ƃ��̃G�t�F�N�g�摜�̎擾
}

void Arrow::Finalize() {
	DeleteGraph(mHitEffectHandle);

	mArrowExists = false;
	mAExistingFrameCnt = 0;
}

void Arrow::StartArrow(const int x, const int y, const int type) {
	// �ʒu
	mXCenter = x;
	mYCenter = y;
	// �|��̎��
	mType = type;

	// �|����݂��Ă��邩�ǂ����̐ݒ�
	mArrowExists = true;

	// �|��̓��������Ƃ��Ɏg�p����ϐ�
	mHitEffectHandle = LoadGraph("images/hit.png");
	mIsHit = false;
	mHitFrameCnt = 0;

	// �|��̎�ނɑΉ������l�̐ݒ�
	if (mType == 1 || mType == 3) {	// �E����
		mArrowHandle = ItemGraphics::GetGraHandle(16);
		mDX = 20;
		
		if (mType == 1) {	// �ア�|��
			mDTh = 2.0f;
			mTheta = -PI * (10 / (float)180);
			mDYFirst = 10;
		}
		else {	// �����|��
			mDTh = 1.5f;
			mTheta = -PI * (50 / (float)180);
			mDYFirst = 20;
		}
	}
	else {	// ������
		mArrowHandle = ItemGraphics::GetGraHandle(17);
		mDX = -20;

		if (mType == 2) {	// �ア�|��
			mDTh = -2.0f;
			mTheta = PI * (40 / (float)180);
			mDYFirst = 10;
		}
		else {	// �����|��
			mDTh = -1.5f;
			mTheta = PI * (50 / (float)180);
			mDYFirst = 20;
		}
	}

	// �|��̓����Ɏg�p����ϐ��̐ݒ�
	mIsMoving = true;
	mYStart = mYCenter;
	mYPrev = mYCenter;
	mYCenter = mYCenter - mDYFirst;
}

void Arrow::Update() {
	if (mIsHit) {
		if (mHitFrameCnt == 20) {	// �������Ă���20�t���[����
			Finalize();	// �|��i���������G�t�F�N�g�j������
		}
	}
	else if (mAExistingFrameCnt == 80) {	// �����Ă���80�t���[����
		Finalize();	// �|�������
	}

	/*if (mIsHit == true) {
		if (mHitFrameCnt == 0) {
			HitJudge0::SetPlARange(-3000, -3000, 0, 0);
			HitJudge1::SetPlARange(-3000, -3000, 0, 0);
			HitJudge2::SetPlARange(-3000, -3000, 0, 0);
		}

		mHitFrameCnt++;
	}
	else {
		if (mhFlag == true) {
			Move();

			HitJudge();
		}
		

		mAExistingFrameCnt++;
	}*/

	if (mIsMoving) {	// �|������Ă���Ƃ��i���ɂ��������Ă��Ȃ��Ƃ��j
		Move();
	}
	

	//HitJudge();


	mAExistingFrameCnt++;
}

void Arrow::Draw() {
	if (mIsHit) {	// �����ɂ��������Ƃ�
		// ���������G�t�F�N�g�̉摜�̕`��
		DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mHitEffectHandle, TRUE);
	}
	else {
		// �|��̕`��
		DrawRotaGraph(mXCenter, mYCenter, 1, mTheta, *mArrowHandle, TRUE);
	}
}

void Arrow::Move() {
	// x���W�̍X�V
	mXCenter += mDX;

	// y���W�̍X�V
	int yTemp = mYCenter;
	mYCenter += (mYCenter - mYPrev) + 1;
	mYPrev = yTemp;

	if (mYCenter >= mYStart + 80 || mIsHit) {		// ����̈ʒu�܂ŉ����邩�C�����ɓ�����Γ������~�߂�
		mIsMoving = false;
	}
	
	// ��]�p�̍X�V
	mTheta += PI * (mDTh / (float)180);
	
	if (mType == 1 || mType == 3) {	// �E�����̂Ƃ�
		mX = mXCenter + (36 * cos(-mTheta));
		mY = mYCenter - (36 * sin(-mTheta));
	}
	else {	// �������̂Ƃ�
		mX = mXCenter - 36 * cos(mTheta);
		mY = mYCenter - 36 * sin(mTheta);
	}
}

void Arrow::UpdateHit() {
	/*if (mIsMoving == true) {
		HitJudge0::SetPlARange(mX, mY, hitRangeAX, hitRangeAY);
		HitJudge1::SetPlARange(mX, mY, hitRangeAX, hitRangeAY);
		HitJudge2::SetPlARange(mX, mY, hitRangeAX, hitRangeAY);
	}
	else {
		HitJudge0::SetPlARange(-3000, -3000, 0, 0);
		HitJudge1::SetPlARange(-3000, -3000, 0, 0);
		HitJudge2::SetPlARange(-3000, -3000, 0, 0);
	}

	bool eneJudge0 = HitJudge0::PaEJudge();
	bool eneJudge1 = HitJudge1::PaEJudge();
	bool eneJudge2 = HitJudge2::PaEJudge();

	if (eneJudge0 == true || eneJudge1 == true || eneJudge2 == true) {
		mIsHit = true;
	}*/
}

bool Arrow::GetArrowExists() const {
	return mArrowExists;
}