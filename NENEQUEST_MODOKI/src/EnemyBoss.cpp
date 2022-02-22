#include "EnemyBoss.h"
#include "DxLib.h"
#include "ItemGraphics.h"
#include <random>
//#include <math.h>


EnemyBoss::EnemyBoss(EnemyChanger* changer, const int eneIdx, const int x, const int y)
	: Enemy(changer, CharaGraphics::GetGraHandle(1, 8), eneIdx, x, y) {
}


void EnemyBoss::Initialize() {
	Enemy::Initialize();

	// 当たり判定関連の設定
	mHitRangeW = 78, mHitRangeH = 220;

	// 最初の表示画像のidの設定
	mHandleId = 0;

	// 体力と攻撃力の設定
	mHp = 45;
	mAttack = 1;	// 怒り状態の前の攻撃力
	// 攻撃の数の設定
	mEneANum = 0;	// 攻撃の種類によって変化する（FireBall: 3, FireBreath: 5, SummonItem: 1）

	// 攻撃の当たり判定関連の設定
	for (int i = 0; i < ENEBOSS_ATTACK_NUM_MAX; i++) {
		mAXs.push_back(0);
		mAYs.push_back(0);
		mHitRangeAWs.push_back(0);
		mHitRangeAHs.push_back(0);
	}

	// 移動速度関連の設定
	mSpeed = 2.0f;
	mDirecX = 1;

	// 火の玉攻撃で使用するクラスのオブジェクトを取得する
	mBossFire = new BossFire();

	// その他
	mAlphaValue = 255;
	mWatingFrameCnt = 0;
	mAFrameCnt = 0;
	mIsAttacking = false;
	mIsFireAttacking = false;
	mIsSummoningEne = false;
	mIsDroppingIteB = false;
	mIsJumping = false;
	mIteBHandle = NULL;
	mIsCreatingIteB = false;
	mCreIteBFrameCnt = 0;
	mIsChangingSt = true;	// EnemyBossが作成されるのはBossStageへの移行中なのでtrue
	mIsBoss = true;	// EnemyBossなのでtrue

	// スコアの設定
	mScore = 10000;
}


void EnemyBoss::Finalize() {

}


void EnemyBoss::Update() {
	if (mIsChangingSt) {	// BossStageへの移行中だったら
		// 画面外右側から規定の位置までの移動
		if (mX > ENEBOSS_FIRST_X) {	// 規定の位置についていなければ
			mX -= 1;
		}
		else {	// 規定の位置への移動が終わったら
			// BossStageを始める
			mIsChangingSt = false;
		}
	}
	else {
		// ベースの画像の設定
		if (mHp > HP_ANGRY) {	// 通常モードのとき
			mHandleId = 0;
		}
		else {	// 怒りモードのとき
			mHandleId = 12;
		}

		// hpの更新
		UpdateHp();

		// 攻撃力と移動速度の更新
		UpdateSAP();

		if (mIsAttacking) {	// 攻撃中のとき
			Attack();
		}
		else {	// 攻撃中でないとき
			// 移動
			Walk();

			// 攻撃をするかどうかを決める
			if (mWatingFrameCnt % ATTACK_FRAME_NUM == 0 && mWatingFrameCnt != 0) {
				// 行う攻撃を決める
				SelectAttack();
			}

			mWatingFrameCnt++;
		}


		if (mIsGod) {	// 攻撃を受けた後の無敵時間のとき
			if (mGodFrameCnt == GOD_FRAME_NUM) {	// 無敵時間が終わったら
				mIsGod = false;
				mGodFrameCnt = 0;
			}
			else {	// 無敵時間中なら
				// 無敵時間であることを表す画像にする
				if ((mGodFrameCnt / 20) % 2 == 0) {	// 点滅処理
					mHandleId += 6;
				}

				mGodFrameCnt++;
			}
		}
	}
}


void EnemyBoss::Draw() {
	// 透明度の設定
	if (mHp <= 0) { //倒されたとき
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaValue);
	}

	// EnemyBossの画像の描画
	DrawGraph(mX - IMG_W / 2, mY - IMG_H / 2, mEneHandle[mHandleId], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(mX - mHitRangeW, mY - mHitRangeH, mX + mHitRangeW, mY + mHitRangeH, GetColor(255, 0, 0), FALSE);

	// DropItemBoxで行うItemBox落とし攻撃のItemBoxの画像の描画
	if (mIteBHandle) {	// 描画するItemBoxがセットされていたら
		DrawGraph(mIteBX - mIteBImgW / 2, mIteBY - mIteBImgH / 2, mIteBHandle[0], TRUE);
		DrawBox(mIteBX - mIteBHitRangeW, mIteBY - mIteBHitRangeH,
			mIteBX + mIteBHitRangeW, mIteBY + mIteBHitRangeH, GetColor(255, 0, 0), FALSE);
	}

	// 火の玉攻撃の画像の描画
	if (mIsFireAttacking) {	// 火の玉攻撃中のとき
		mBossFire->Draw();
	}
}


void EnemyBoss::UpdateSAP() {
	if (mHp > HP_ANGRY) {	// 通常モードのとき
		mSpeed = 2.0f;
		mAttack = 1;
	}
	else {	// 怒りモードのとき
		mSpeed = 3.0f;
		mAttack = 2;
	}
}


void EnemyBoss::Walk() {
	// x座標の更新
	mX -= (int)(mSpeed * mDirecX);

	if (mX < ENEBOSS_X_MIN || mX > ENEBOSS_X_MAX) {	// 移動範囲を超えたら
		// 方向切り替え
		mDirecX *= -1;
	}

	int ix = abs(mX) % 40 / 20;
	mHandleId += ix;
}


void EnemyBoss::Attack() {
	if (mIsSummoningEne) {	// Enemy呼び出し攻撃中のとき
		SummonEnemy();
	}
	else if (mIsDroppingIteB) {	// ItemBox落とし攻撃中のとき
		DropItemBox();
	}
	else {	// 火の玉攻撃中のとき
		FireAttack();
	}
}


void EnemyBoss::SelectAttack() {
	// 行う攻撃を選択する
	// 何か攻撃をする確率（0～10000, 10000で100%）を求める
	int attackProb = 10000 - std::pow(5000, ATTACK_FRAME_NUM/ mWatingFrameCnt);

	// 1～10000のランダムな数値を生成
	std::random_device rnd;
	int randNum = rnd() % 10000 + 1;

	// 行う攻撃を選択（10000 - attackProbの確率で攻撃をしない）
	if (randNum >= 10000 - attackProb) {	// 何か攻撃をするとき
		// randNumを1～attackProbの範囲にしたのち，1～100の範囲の値に正規化する
		randNum = 10000 - randNum + 1;
		randNum = (randNum / (float)attackProb) * 100;

		if (randNum <= 25) {	// 50%の確率で
			// Enemy呼び出し攻撃
			mIsSummoningEne = true;
			mEneANum = 0;
		}
		else if (randNum <= 50) {	// 50%の確率で
			// ItemBox落とし攻撃
			mIsDroppingIteB = true;
			mEneANum = 1;
		}
		else {	// 50%の確率で
			// 火の玉攻撃
			int fireType;
			if (mHp > HP_ANGRY) {	// 通常モードのとき
				// 赤い火の玉
				fireType = 1;
			}
			else {	// 怒りモードのとき
				// 青い火の玉
				fireType = 2;
			}
			if (randNum <= 75) {	// 25%の確率で
				// 火の玉吐き出し攻撃
				mBossFire->StartFire(mX, mY, fireType, 1);
				mEneANum = mBossFire->GetFireNum(1);
			}
			else {	// 25%の確率で
				// ブレス攻撃
				mBossFire->StartFire(mX, mY, fireType, 2);
				mEneANum = mBossFire->GetFireNum(2);
			}
			
			mIsFireAttacking = true;
		}

		mIsAttacking = true;
		mWatingFrameCnt = 0;
	}
}


void EnemyBoss::SummonEnemy() {
	if (mAFrameCnt == 300) {
		// 次の攻撃をできるようにする
		mIsAttacking = false;
		mIsSummoningEne = false;
		mAFrameCnt = 0;
	}
	else if (mAFrameCnt >= 30 && mAFrameCnt <= 90) {	// 呼びだしているとき
		// 呼び出しをしている画像にする
		mHandleId += 4;

		// Enemyをセットする
		if (mAFrameCnt == 90) {
			CreateEnemy();
		}

		mAFrameCnt++;
	}
	else {	// 敵を呼びだし前と呼び出し後に少し静止させるとき
		mAFrameCnt++;
	}
}


void EnemyBoss::CreateEnemy() {
	std::random_device rnd;

	int eneX, eneY;	// 生成する敵のxy座標
	eneY = rnd() % (ENEMY_FIRST_Y_MAX - ENEMY_FIRST_Y_MIN) + ENEMY_FIRST_Y_MIN;
	
	// 呼びだす敵の種類を決める
	EEnemy eneKind;
	int randNum = rnd() % 100 + 1;	// 1～100の乱数
	if (mHp > HP_ANGRY) {	// 通常モードのとき
		if (randNum <= 60) {	// 60%の確率で
			// イノシシの敵
			eneX = 1400;

			if (randNum <= 30) {	// 30%の確率で
				// Enemy1
				eneKind = eEnemy1;
			}
			else if (randNum <= 50) {	// 20%の確率で
				// Enemy2
				eneKind = eEnemy2;
			}
			else {	// 10%の確率で
				// Enemy3
				eneKind = eEnemy3;
			}
		}
		else {	// 40%の確率で
			// 魔法使いの敵
			// x座標はPlayerから離れた位置にする
			if (mPlX > 600) {	// Playerが右側にいたら
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Playerが左側にいたら
				eneX = rand() % (150 + 1) + 1000;
			}
			
			if (randNum <= 90) {	// 30%の確率で
				// Enemy4
				eneKind = eEnemy4;
			}
			else {	// 10%の確率で
				// Enemy5
				eneKind = eEnemy5;
			}
		}
	}
	else {	// 怒りモードのとき
		if (randNum <= 30) {	// 30%の確率で
			// イノシシの敵
			eneX = 1400;

			// Enemy3
			eneKind = eEnemy3;
		}
		else if (randNum <= 60) {	// 30%の確率で
			// 魔法使いの敵
			// x座標はPlayerから離れた位置にする
			if (mPlX > 600) {	// Playerが右側にいたら
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Playerが左側にいたら
				eneX = rand() % (150 + 1) + 1000;
			}

			// Enemy6
			eneKind = eEnemy6;
		}
		else {	// 40%の確率で
			// 鎌使い
			// x座標はPlayerから離れた位置にする
			if (mPlX > 600) {	// Playerが右側にいたら
				eneX = rand() % (150 + 1) + 80;
			}
			else {	// Playerが左側にいたら
				eneX = rand() % (150 + 1) + 1000;
			}

			// Enemy7
			eneKind = eEnemy7;
		}
	}

	// 敵を生成する
	mEnemyChanger->ChangeEnemy(-1, eneKind, eneX, eneY);
}


void EnemyBoss::DropItemBox() {
	if (mAFrameCnt == 0) {	// 最初に通ったとき
		std::random_device rnd;

		// 落下させるItemBoxのxy座標
		mIteBX = rnd() % (ITEMBOX_FIRST_X_MAX - ITEMBOX_FIRST_X_MIN) + ITEMBOX_FIRST_X_MIN;
		mIteBY = -100;

		// 攻撃の座標をセットしておく
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		// 落下速度の初期化（後に徐々に加速していく）
		mIteBDY = 1;

		// 落下させるItemBoxを決める
		int randNum = rnd() % 100 + 1;	// 1～100の乱数
		if (randNum <= 50) {	// 50%の確率で
			// Item12（樽1）
			mIteBKind = eItem12;

			mIteBHandle = ItemGraphics::GetGraHandle(12);
			mIteBImgW = 162, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
			
		}
		else if (randNum <= 30) {	// 30%の確率で
			// Item13（樽2）
			mIteBKind = eItem13;

			mIteBHandle = ItemGraphics::GetGraHandle(13);
			mIteBImgW = 162, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
		}
		else {	// 20%の確率で
			// Item14（箱）
			mIteBKind = eItem14;

			mIteBHandle = ItemGraphics::GetGraHandle(14);
			mIteBImgW = 164, mIteBImgH = 160;
			mIteBHitRangeW = 35, mIteBHitRangeH = 35;
		}

		// 当たり判定の更新
		mHitRangeAWs.at(0) = mIteBHitRangeW;
		mHitRangeAHs.at(0) = mIteBHitRangeH;

		// ItemBoxを落下させるアクションのジャンプを始める
		mIsJumping = true;
		mYStart = mY;
		mYPrev = mY;
		mY = mY - 17;

		mAFrameCnt++;
	}
	else if (mIsJumping) {	// ジャンプ中だったら
		Jump();

		// 攻撃の座標をセットしておく
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
	}
	else if (mIteBY < 500) {
		// ItemBoxを落下させる
		mIteBY += mIteBDY;
		mIteBDY++;

		// 攻撃の座標をセットしておく
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
	}
	else if (mCreIteBFrameCnt <= 1) {	// ItemBoxを落下させ終わったら
		if (mCreIteBFrameCnt == 0) {
			// ItemMgrを落下させた位置にItemMgrの方で実際のItemBoxを作成する(2フレーム必要)
			mIsCreatingIteB = true;
		}
		else {
			mIsCreatingIteB = false;
		}

		// 攻撃の座標をセットしておく
		mAXs[0] = mIteBX;
		mAYs[0] = mIteBY;

		mAFrameCnt++;
		mCreIteBFrameCnt++;
	}
	else {	// ItemMgrの方でItemBoxを作成してもらったら
		mCreIteBFrameCnt = 0;
		mIteBHandle = NULL;

		// 攻撃の座標を画面外にしておく
		mAXs[0] = 3000;	// 適当な画面外
		mAYs[0] = 3000;
		
		// 次の攻撃をできるようにする
		mIsAttacking = false;
		mIsDroppingIteB = false;
		mAFrameCnt = 0;
	}
}


void EnemyBoss::Jump() {
	int yTemp = mY;
	mY += (mY - mYPrev) + 1;
	mYPrev = yTemp;

	if (mY == mYStart) {
		mIsJumping = false;
	}
}


void EnemyBoss::FireAttack() {
	// 火の玉攻撃が終わっているか確認する
	mIsFireAttacking = mBossFire->GetFiresExist();

	if (mIsFireAttacking) {	// 火の玉攻撃中なら
		// 口を開けている画像にする
		mHandleId += 2;

		// 火の玉を更新する
		mBossFire->Update();

		// 火の玉の当たり判定を取得する
		mBossFire->GetFiresXYs(mAXs, mAYs);
		mBossFire->GetFiresHitRangeWHs(mHitRangeAWs, mHitRangeAHs);
	}
	else {	// 火の玉攻撃が終わっていたら
		// 攻撃の座標を画面外にしておく
		for (int i = 0; i < ENEBOSS_ATTACK_NUM_MAX; i++) {
			mAXs[i] = 3000;
			mAYs[i] = 3000;
		}
		
		mIsAttacking = false;
	}
}


void EnemyBoss::GetEneDataMap(std::map<std::string, int>* eneIntDataMap, 
	std::vector<std::map<std::string, int>>* eneAXYMapVec, std::map<std::string, bool>* eneBoolDataMap) {
	Enemy::GetEneDataMap(eneIntDataMap, eneAXYMapVec, eneBoolDataMap);

	// DropItemBoxで生成したItemBoxの生成命令のセット
	(*eneBoolDataMap)["isCreatingIteB"] = mIsCreatingIteB;
	if (mIsCreatingIteB) {	// ItemMgrでItemBox生成してほしいとき
		(*eneIntDataMap)["itemBoxKind"] = mIteBKind;
		(*eneIntDataMap)["itemBoxX"] = mIteBX;
		(*eneIntDataMap)["itemBoxY"] = mIteBY;
	}

	// 攻撃の当たり判定関連
	if (mIsAttacking) {	// 攻撃中のとき
		for (int i = 0; i < mEneANum; i++) {
			(*eneAXYMapVec).at(i)["ax"] = mAXs.at(i);
			(*eneAXYMapVec).at(i)["ay"] = mAYs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAW"] = mHitRangeAWs.at(i);
			(*eneAXYMapVec).at(i)["hitRangeAH"] = mHitRangeAHs.at(i);
		}
	}
}