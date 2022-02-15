#include "Slash.h"
#include "DxLib.h"
#include "EffectGraphics.h"
#include <math.h>


#define PI 3.14159265358979323846


void Slash::Initialize() {
	mSlashExist = false;
}


void Slash::Finalize() {
	mSlashExist = false;
}


void Slash::StartSlash(const int eneX, const int eneY, const int direc, const int attackType) {
	// aŒ‚‰æ‘œ‚Ì“Ç‚İ‚İ
	mSlashHandle = EffectGraphics::GetGraHandle(7);

	// UŒ‚‚Ìí—Ş‚ğ“ü‚ê‚é
	mAttackType = attackType;

	// UŒ‚‚Ì•ûŒü‚ğƒZƒbƒg‚·‚é
	mDirec = direc;	// ‰EŒü‚«‚È‚ç1, ¶Œü‚«‚È‚ç-1

	// UŒ‚‚É‡‚í‚¹‚½‰Šú‰»‚ğs‚¤
	if (mAttackType == 1) {	// ŒÅ’èˆÊ’u‚ÌaŒ‚UŒ‚
		// aŒ‚‚ÌxyÀ•W
		mX = eneX + mDirec * 100;
		mY = eneY;

		// aŒ‚‚Ì“–‚½‚è”»’è
		mHitRangeW = 63;
		mHitRangeH = 50;

		// aŒ‚‚Ì‰æ‘œid
		mHandleId = 1 + mDirec * 0.5;	// ¶Œü‚«‚È‚ç0‚ª“ü‚èC‰EŒü‚«‚È‚ç1‚ª“ü‚é
	}
	else {	// ‰ñ“]UŒ‚
		// aŒ‚‚ÌxyÀ•W
		mX = eneX + mDirec * 100;
		mY = eneY;

		// aŒ‚‚Ì“–‚½‚è”»’è
		mHitRangeW = 63;
		mHitRangeH = 50;

		// aŒ‚‚ÌxÀ•W‚Ì‘‰Á•ª
		mDX = mDirec * 40;

		// aŒ‚‚Ì‰æ‘œid
		mHandleId = 3 + mDirec * 0.5;	// ¶Œü‚«‚È‚ç0‚ª“ü‚èC‰EŒü‚«‚È‚ç1‚ª“ü‚é
	}

	mFrameCnt = 0;
	mSlashExist = true;
}


void Slash::Update() {
	if (mAttackType == 1) {	// ŒÅ’èˆÊ’u‚ÌaŒ‚UŒ‚‚Ì‚Æ‚«
		if (mFrameCnt == SLASH_DELETE_FRAME_NUM) {	// “Á’è‚ÌƒtƒŒ[ƒ€”‚É‚È‚Á‚½‚ç
			Finalize();
		}
		else {
			mFrameCnt++;
		}
	}
	else {	// ”ò‚Î‚·aŒ‚UŒ‚‚Ì‚Æ‚«
		if (mX < SLASH_DELETE_LX || mX > SLASH_DELETE_RX) {	// aŒ‚‚ª‰æ–ÊŠO‚Éo‚Ä‚¢‚½‚ç 
			Finalize();
		}
		else {
			Move();

			mFrameCnt++;
		}
	}
}


void Slash::Draw() {
	DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mSlashHandle[mHandleId], TRUE);
}


void Slash::Move() {
	mX += mDX;
}


std::pair<int, int> Slash::GetSlashHitRange() {
	return { mHitRangeW, mHitRangeH };
}


bool Slash::GetSlashExist() const {
	return mSlashExist;
}


std::pair<int, int> Slash::GetSlashXY() {
	return { mX, mY };
}
