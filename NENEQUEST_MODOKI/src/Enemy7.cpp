// Enemy4～6の魔法使いの敵の基底クラス
#include "Enemy7.h"
#include "DxLib.h"
#include "CharaGraphics.h"
#include <random>


Enemy7::Enemy7(EnemyChanger* changer, const int eneIdx, const int x, const int y)
	: Enemy(changer, CharaGraphics::GetGraHandle(1, 7), eneIdx, x, y) {
}


void Enemy7::Initialize() {
	Enemy::Initialize();

	// 位置に合わせた画像idの設定
	if (mX > 600) {	// 右側にいるとき
		mHandleId = 0;
		mAttackDirec = -1;
	}
	else {	// 左側にいるとき
		mHandleId = 2;
		mAttackDirec = 1;
	}

	// 当たり判定関連の設定
	mImgW = 303, mImgH = 151;
	mHitRangeW = 29, mHitRangeH = 64;

	// 体力と攻撃力の設定
	mHp = 1;
	mAttack = 2;
	// 攻撃の数の設定
	mEneANum = 1;	// 斬撃攻撃及び切りつけ攻撃どちらにおいても数は1

	// 斬撃攻撃で使用するクラスのオブジェクトを取得する
	mSlash = new Slash();

	// 動作回数の設定
	mDeleteRoDoneNum = 2;

	// その他
	mIsFadingIn = true;	// 最初はフェードインで入ってくるため，true
	mIsFadingOut = false;
	mIsHiding = false;
	mAlphaValue = 0;	// 最初は消えていて，フェードインで入ってくるため，α値は0
	mHidingFrameCnt = 0;
	mAttackFrameCnt = 0;
	mRoutineDoneCnt = 0;
	mHasFinishedRos = false;
	mIsAttacking = false;
	mEne7IsDead = false;
	mIsBoss = false;

	// 倒したら得られるスコアの設定
	mScore = 2000;
}


void Enemy7::Finalize() {
	delete mSlash;
}


void Enemy7::Update() {
	if (mEne7IsDead || mHasFinishedRos) {	// 動作が終わっているか，Enemy7が死んでいるとき
		if (!mIsAttacking) {	// 火の玉攻撃が終わっているとき
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -3000, -3000);	// -3000は適当に画面外の数値にしている
		}
	}

	// 斬撃攻撃が終わっているかどうかを取得する
	mIsAttacking = mSlash->GetSlashExist();

	// 斬撃攻撃の更新を行う
	if (mIsAttacking) {	// 斬撃攻撃中だったら
		mSlash->Update();
		std::tie(mAX, mAY) = mSlash->GetSlashXY();
	}

	// Enemy7の位置に合わせたEnemy7の画像idの設定
	if (mAttackDirec == -1) {	// 左側を向いているとき
		mHandleId = 0;
	}
	else {	// 右側をむいているとき
		mHandleId = 2;
	}

	// Enemy7自体の更新を行う
	if (!mEne7IsDead && !mHasFinishedRos) {	// 動作をし終えていなくて，死んでいなければ
		// hpの更新
		UpdateHp();

		if (mIsFadingIn) {	// フェードインしているとき（動作順番1）
			FadeIn();
		}
		else if (mIsFadingOut) {	// フェードアウトしているとき（動作順番3）
			FadeOut();
		}
		else if (mIsHiding) {	// 姿を隠しているとき（動作順番4）
			Hide();
		}
		else {	// 姿を現しているとき（動作順番2）
			//if (mHp <= 0) {	// 体力が0以下となったとき
			//	// 死んだことを認識させるための10フレームの硬直
			//	if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			//		mEne7IsDead = true;
			//	}

			//	// ダメージをくらったことがわかる画像にする
			//	mHandleId += 4;

			//	mGodFrameCnt++;
			//}
			if (mRoutineDoneCnt == 0) {	// 1回目の動作のとき（ただy座標移動している（敵を倒すための猶予時間））
				if (mAttackFrameCnt == STOP_FRAME_NUM) {
					// フェードアウトを始める
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					mAttackFrameCnt++;
				}
			}
			else {	// 2回目以降の動作のとき（斬撃攻撃する）
				if (mAttackFrameCnt == ATTACK_STATE_FRAME_NUM) {
					// フェードアウトを始める
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					// 攻撃動作の画像にする
					mHandleId += 1;

					mAttackFrameCnt++;
				}
			}
		}

		// 無敵時間の際の画像の点滅処理
		if (mIsGod) {
			if (mHp > 0) {	// hp > 0 のとき
				if (mGodFrameCnt == GOD_FRAME_NUM) {	// 無敵時間が終わったら
					mIsGod = false;
					mGodFrameCnt = 0;
				}
				else {	// 無敵時間中なら
					// 無敵時間であることを表す画像にする
					if ((mGodFrameCnt / 20) % 2 == 0) {	// 点滅処理
						mHandleId += 4;
					}

					mGodFrameCnt++;
				}
			}
			else {	// hpが0以下となったとき
					// 死んだことを認識させるための10フレームの硬直
				if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
					mEne7IsDead = true;
				}
				else if (mGodFrameCnt == 0) {	// 倒した瞬間，スコアが入るようにする
					mIsDead = true;
				}
				else {
					mIsDead = false;
				}

				// ダメージをくらったことがわかる画像にする
				mHandleId += 4;
				mAlphaValue = 255;

				mGodFrameCnt++;
			}
		}
	}
}


void Enemy7::Draw() {
	// Enemy7の描画
	if (!mEne7IsDead && !mHasFinishedRos) {	// 動作をし終えていなくて，死んでいなければ
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
		DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 11, mEneHandle[mHandleId], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// 斬撃攻撃の描画
	if (mIsAttacking) {	// 斬撃攻撃をしているとき
		mSlash->Draw();
	}
}


void Enemy7::FadeIn() {
	// α値の更新
	if (mAlphaValue < 255) {
		mAlphaValue += DELTA_ALPHA;
	}

	if (mAlphaValue > 255) {
		mAlphaValue = 255;
	}

	if (mAlphaValue == 255) {
		// フェードインを終了する
		mIsFadingIn = false;

		if (mRoutineDoneCnt >= 1) {	// 2回目の動作以降
			// 斬撃攻撃を始める
			// (1: 固定位置の斬撃攻撃，2: 飛ばす斬撃攻撃)
			mSlash->StartSlash(mX, mY, mAttackDirec, mAttackType);

			// 斬撃の当たり判定範囲を受け取る
			std::tie(mHitRangeAW, mHitRangeAH) = mSlash->GetSlashHitRange();
		}
	}
}


void Enemy7::FadeOut() {
	// α値の更新
	if (mAlphaValue > 0) {
		mAlphaValue -= DELTA_ALPHA;
	}

	if (mAlphaValue < 0) {
		mAlphaValue = 0;
	}

	if (mAlphaValue == 0) {
		// フェードアウトを終了する
		mIsFadingOut = false;

		// 動作を終えた回数を増やす
		mRoutineDoneCnt++;

		if (mRoutineDoneCnt < mDeleteRoDoneNum) {	// 動作の回数が終了回数に達していなかったら
			// 動作を始める前の姿を消している時間を始める
			mIsHiding = true;
		}
		else {	// 動作の回数が終了回数に達していたら
			// 動作を終えたことにする
			mHasFinishedRos = true;
		}
	}
}


void Enemy7::Hide() {
	if (!mIsAttacking && mHidingFrameCnt >= HIDING_FRAME_NUM_MIN) {	// 斬撃攻撃が終わっていて，かつ特定の時間以上隠れていたら
		// 隠れるのを終了する
		mIsHiding = false;
		mHidingFrameCnt = 0;

		// 乱数のシード値を更新
		std::random_device rnd;

		// 次の攻撃の種類を決める
		for (int i = 0; i < mEneIdx + 1; i++) {	// for文は同じフレームにおいてrand()の値が他のmIdxのEnemyと一致しないようにするため
			mAttackType = rnd() % 2 * (-2) + 1;	// 1か-1が入る
		}
		
		// 次のxy座標を決める
		int xNext, yNext;
		if (mAttackType == 1) {	// 固定位置の斬撃攻撃（Playerの目前に現れ切りつける）
			// 攻撃の向きを決める
			mAttackDirec = rnd() % 2 * (-2) + 1;	// 1か-1が入る

			xNext = mPlX - 150 * mAttackDirec;	// Playerの左側か右側に現れる
			yNext = mPlY;
		}
		else {	// 飛ばす斬撃攻撃
			// Playerから遠い側のx座標にする
			if (mPlX > 600) {	// 右側にいたら
				xNext = rnd() % (150 + 1) + 80;
				yNext = mPlY + 50;
				mAttackDirec = 1;
			}
			else {	// 左側にいたら
				xNext = rnd() % (150 + 1) + 1000;
				yNext = mPlY + 50;
				mAttackDirec = -1;
			}
		}
		
		// 新しいxy座標をセットする
		mX = xNext;
		mY = yNext;

		// フェードインを始める
		mIsFadingIn = true;
	}
	else {
		mHidingFrameCnt++;
	}
}


void Enemy7::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// フェードアウトしているときと姿を消しているとき，
	// 動作を終えたとき，Enemy7は死んでいるとき（しかし斬撃は残っているとき）は
	// 敵の当たり判定は画面外に設定する
	if (mIsFadingOut || mIsHiding || mEne7IsDead || mHasFinishedRos) {
		(*eneIntDataMap)["x"] = -3000;
		(*eneIntDataMap)["y"] = -3000;
	}
	
	// 各斬撃の当たり判定関連の情報を渡す
	if (mIsAttacking) {	// 攻撃中のとき
		for (int i = 0; i < mEneANum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAX;
			(*eneAXYMapVec).at(i)["ay"] = mAY;
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAW;
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAH;
		}
	}
}


