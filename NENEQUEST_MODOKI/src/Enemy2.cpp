// イノシシ2（hp2）
#include "Enemy2.h"
#include "DxLib.h"
#include "CharaGraphics.h"


Enemy2::Enemy2(EnemyChanger* changer, const int itemIdx, const int x, const int y)
	: EnemyBoar(changer, CharaGraphics::GetGraHandle(1, 2), itemIdx, x, y) {
}


void Enemy2::Initialize() {
	EnemyBoar::Initialize();

	// 当たり判定関連の設定
	mImgW = 250, mImgH = 177;

	// 攻撃や体力の設定
	mEneANum = 0;	// 体当たりするだけだから0
	mHp = 2;
}


void Enemy2::Update() {
	if (mHp > 0 && mX >= ENE_BOAR_DELETE_X) {	// 生きていて，画面内にいるときの処理
		// hpの更新
		UpdateHp();

		Walk();

		if (mIsGod) {	// 攻撃を受けた後の無敵時間のとき
			if (mGodFrameCnt == GOD_FRAME_NUM) {	// 無敵時間が終わったら
				mIsGod = false;
				mGodFrameCnt = 0;
			}
			else {	// 無敵時間中なら
				// 無敵時間であることを表す画像にする
				if ((mGodFrameCnt / 20) % 2 == 0) {	// 点滅処理
					mHandleId += 2;
				}

				mGodFrameCnt++;
			}
		}

		mExistingFrameCnt++;
	}
	else {	// 画面外に行くか，死んだときの処理（死んだときは死んだことを認識させるための10フレームの硬直を行う）
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM || mX < ENE_BOAR_DELETE_X) {
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -1000, -1000);	// -1000は適当に画面外の数値にしている
		}

		// ダメージをくらったことがわかる画像にする
		mHandleId = 2;

		mGodFrameCnt++;
	}
}


void Enemy2::Draw() {
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2, mEneHandle[mHandleId], TRUE);
}

