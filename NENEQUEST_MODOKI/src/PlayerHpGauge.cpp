#include "PlayerHpGauge.h"
#include "DxLib.h"


void PlayerHpGauge::Initialize() {
	mPlHp = 10;
	mPlFaceHandle = LoadGraph("images/playerface.png");
}


void PlayerHpGauge::Finalize() {
	DeleteGraph(mPlFaceHandle);
}


void PlayerHpGauge::Update() {
	if (mPlHp >= 6) {	// hp�ɗ]�T������Ƃ�
		mGaugeColor = GetColor(82, 237, 84);	// �ΐF
	}
	else if (mPlHp >= 3) {	// hp�ɂ��܂�]�T���Ȃ���
		mGaugeColor = GetColor(220, 220, 60);	// ���F
	}
	else {	// hp�ɗ]�T���Ȃ��Ƃ�
		mGaugeColor = GetColor(237, 40, 40);	// �ԐF
	}
}


void PlayerHpGauge::Draw() {
	DrawBox(195, 75, 505, 115, GetColor(255, 255, 255), TRUE);
	DrawBox(200, 80, 500, 110, GetColor(70, 72, 82), TRUE);
	DrawBox(200, 80, 200 + 30 * mPlHp, 110, mGaugeColor, TRUE);
	DrawGraph(120, 30, mPlFaceHandle, TRUE);
}


void PlayerHpGauge::SetPlayerHp(const int plHp) {
	mPlHp = plHp;
}