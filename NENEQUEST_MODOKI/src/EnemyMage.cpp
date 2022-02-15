// Enemy4～6の魔法使いの敵の基底クラス
#include "EnemyMage.h"
#include "DxLib.h"
#include <time.h>


EnemyMage::EnemyMage(EnemyChanger* changer, const int* graph, const int eneIdx, const int x, const int y)
	: Enemy(changer, graph, eneIdx, x, y) {
}


void EnemyMage::Initialize() {
	Enemy::Initialize();

	// 位置に合わせた画像idの設定
	if (mX > 600) {	// 右側にいるとき
		mHandleId = 0;
	}
	else {	// 左側にいるとき
		mHandleId = 2;
	}

	// 当たり判定関連の設定
	mHitRangeW = 29, mHitRangeH = 64;

	// 移動速度や攻撃力の設定
	mSpeed = 3.0f;
	mDirecY = 1;

	// 火の玉攻撃で使用するクラスのオブジェクトを取得する
	mMageFire = new MageFire();
	// 火の玉の数を受け取る
	mFireNum = mMageFire->GetFireNum();
	mEneANum = mFireNum;
	// 各火の玉のxy座標を入れるvectorを初期化する
	for (int i = 0; i < mFireNum; i++) {
		mAXs.push_back(0);
		mAYs.push_back(0);
	}
	// 火の玉の当たり判定範囲を受け取る
	std::tie(mHitRangeAW, mHitRangeAH) = mMageFire->GetFiresHitRange();

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
	mMageIsDead = false;
}


void EnemyMage::Finalize() {
	delete mMageFire;
}


void EnemyMage::Update() {
	if (mMageIsDead || mHasFinishedRos) {	// 動作が終わっているか，EnemyMageが死んでいるとき
		if (!mIsAttacking) {	// 火の玉攻撃が終わっているとき
			mEnemyChanger->ChangeEnemy(mEneIdx, eEnemyNULL, -3000, -3000);	// -3000は適当に画面外の数値にしている
		}	
	}

	// 火の玉攻撃が終わっているかどうかを取得する
	mIsAttacking = mMageFire->GetFiresExist();

	// 火の玉攻撃の更新を行う
	if (mIsAttacking) {	// 火の玉攻撃中だったら
		mMageFire->Update();
		mMageFire->GetFiresXYs(mAXs, mAYs);
	}

	// EnemyMageの位置に合わせたEnemyMageの画像idの設定
	if (mX > 600) {	// 右側にいるとき
		mHandleId = 0;
	}
	else {	// 左側にいるとき
		mHandleId = 2;
	}

	// EnemyMage自体の更新を行う
	if (!mMageIsDead && !mHasFinishedRos) {	// 動作をし終えていなくて，死んでいなければ
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
			//		mMageIsDead = true;
			//	}

			//	// ダメージをくらったことがわかる画像にする
			//	mHandleId += 4;

			//	mGodFrameCnt++;
			//}
			if (mRoutineDoneCnt == 0) {	// 1回目の動作のとき（ただy座標移動している（敵を倒すための猶予時間））
				if (mAttackFrameCnt == WALK_FRAME_NUM) {
					// フェードアウトを始める
					mIsFadingOut = true;
					mAttackFrameCnt = 0;
				}
				else {
					// y座標の移動をする
					Walk();

					mAttackFrameCnt++;
				}
			}
			else {	// 2回目以降の動作のとき（火の玉攻撃する）
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
					mMageIsDead = true;
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


void EnemyMage::Draw() {
	// EnemyMageの描画
	if (!mMageIsDead && !mHasFinishedRos) {	// 動作をし終えていなくて，死んでいなければ
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
		DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 11, mEneHandle[mHandleId], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	//DrawBox(x - hitRangeX, y - hitRangeY, x + hitRangeX, y + hitRangeY, GetColor(0, 0, 0), TRUE);
	//DrawFormatString(800, 300, GetColor(255, 255, 255), "px = %d", count);

	// 火の玉攻撃の描画
	if (mIsAttacking) {	// 火の玉攻撃をしているとき（画面内に1つでも火の玉があるとき）
		mMageFire->Draw();
	}
}


void EnemyMage::Walk() {
	if (mY > ENE_MAGE_Y_MAX || mY < ENE_MAGE_Y_MIN) {	// 範囲外に移動したら
		// 移動方向を反転する
		mDirecY *= -1;
	}

	// y座標の更新
	mY += (int)(mDirecY * mSpeed);
}


void EnemyMage::FadeIn() {
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
			// 使用する火の玉攻撃の種類を決める
			// (1: ジグザグ攻撃，2: 回転攻撃)
			// 1～2のランダムな数値を生成
			srand((unsigned int)time(NULL));
			int attackType;
			for (int i = 0; i < mEneIdx + 1; i++) {
				attackType = rand() % 2 + 1;
			}

			// 火の玉攻撃を始める
			mMageFire->StartFire(mX, mY, mFireType, attackType);
		}
	}
}


void EnemyMage::FadeOut() {
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


void EnemyMage::Hide() {
	if (!mIsAttacking && mHidingFrameCnt >= HIDING_FRAME_NUM_MIN) {	// 火の玉攻撃が終わっていて，かつ特定の時間以上隠れていたら
		// 隠れるのを終了する
		mIsHiding = false;
		mHidingFrameCnt = 0;

		// 次のxy座標を決める
		srand((unsigned int)time(NULL));
		
		int xNext, yNext;
		// Playerから遠い側のx座標にする
		if (mPlX > 600) {	// 右側にいたら
			for (int i = 0; i < mEneIdx + 1; i++) {	// for文は同じフレームにおいてrand()の値が他のmIdxのEnemyと一致しないようにするため
				xNext = rand() % (150 + 1) + 80;
				yNext = rand() % (ENE_MAGE_Y_MAX - ENE_MAGE_Y_MIN + 1) + ENE_MAGE_Y_MIN;
			}
		}
		else {	// 左側にいたら
			for (int i = 0; i < mEneIdx + 1; i++) {
				xNext = rand() % (150 + 1) + 1000;
				yNext = rand() % (ENE_MAGE_Y_MAX - ENE_MAGE_Y_MIN + 1) + ENE_MAGE_Y_MIN;
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


void EnemyMage::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
	std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// フェードアウトしているときと姿を消しているとき，
	// 動作を終えたとき，EnemyMageは死んでいるとき（しかし火の玉は残っているとき）は
	// 敵の当たり判定は画面外に設定する
	if (mIsFadingOut || mIsHiding || mMageIsDead || mHasFinishedRos) {
		(*eneIntDataMap)["x"] = -3000;
		(*eneIntDataMap)["y"] = -3000;
	}
	
	// 各火の玉の当たり判定関連の情報を渡す
	if (mIsAttacking) {	// 攻撃中のとき
		for (int i = 0; i < mFireNum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAXs.at(i);
			(*eneAXYMapVec).at(i)["ay"] = mAYs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAW;
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAH;
		}
	}
}


