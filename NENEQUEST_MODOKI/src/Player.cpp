#include "Player.h"
#include "DxLib.h"
//#include <map>
//#include <string>
//#include "HitJudge0.h"
//#include "HitJudge1.h"
//#include "HitJudge2.h"
//#include "PlayerData.h"
//#include "PowerBox.h"
#include "PlayerMgr.h"
#include "EffectGraphics.h"


Player::Player(PlayerChanger* changer, const int* graph) : mPlHandle(graph) {
	mPlayerChanger = changer;
	mPlayerMgr = PlayerMgr::GetInstance();
}


void Player::Initialize() {
	// 位置，当たり判定の範囲関連設定
	mAX = mX + 160;
	mAY = mY + 20;
	//mHitRangeW = 33, mHitRangeH = 60;
	//mHitRangeAW = 50, mHitRangeAH = 60;
	mImgW = 500, mImgH = 283;
	//mIsGod = false;
	//mGodFrameCnt = 0;

	// Playerの攻撃，ジャンプなどの状態設定
	mXFrameCnt = 0, mYFrameCnt = 0;
	mAFrameCnt = 0;
	mIsJumping = false;
	mIsAttacking = false;
	mHandleId = 0;
	mSpeed = 4.0f;
	//mAttack = 1;

	// アイテムや使用武器の設定
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

	// 情報保持に使用するmap(vector), 配列の初期化
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
	// 効果の画像を削除
	//DeleteGraph(mEffectHandle);
}


void Player::Draw() {
	// Playerの画像表示
	DrawGraph(mX - mImgW / 2, mY - mImgH / 2 - 13, mPlHandle[mHandleId], TRUE);

	// 当たり判定の描画（デバッグ用）
	/*DrawBox(mX - mHitRangeW, mY - mHitRangeH,
		mX + mHitRangeW, mY + mHitRangeH, GetColor(255, 0, 0), FALSE);*/

	// Effectの画像表示
	if (mIsEffected) {	// Itemの効果中のとき
		DrawGraph(mX - 114, mY - 113, *mEffectHandle, TRUE);
	}
}


void Player::UpdateSAP() {
	// 移動速度の更新
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// 左右の入力があるとき
		if (mIsJumping) {	// ジャンプしているとき
			mSpeed = 4 * 0.8f * mSpeedRate;
		}
		else if (mIsAttacking) {	// 攻撃しているとき
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
			mSpeed = 4 * 0.625f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 1.0f * mSpeedRate;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
		if (mIsAttacking) {	// 攻撃しているとき
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 0.80f * mSpeedRate;
		}
	}

	// 攻撃力の更新
	mAttack = mAttackBase;

	// 移動速度（アイテム効果）の更新
	mSpeed *= mIteSP;
	//if (mHasIteS) {
	//	if (mIteSFrameCnt != 0) {	// 効果中のとき
	//		mSpeed *= mIteSP;
	//		mIteSFrameCnt--;
	//	}
	//	else {	// 効果切れのとき4 * mSpeed
	//		mIteSP = 1.0f;
	//		mEffectHandle = 0;
	//		mHasIteS = false;
	//	}
	//}

	// 攻撃力（アイテム効果）の更新
	mAttack *= mIteAP;
	//if (mHasIteA) {
	//	if (mIteAFrameCnt != 0) {	// 効果中のとき
	//		mAttack *= mIteAP;
	//		mIteAFrameCnt--;
	//	}
	//	else {	// 効果切れのとき
	//		mIteAP = 0;
	//		mEffectHandle = 0;
	//		mHasIteA = false;
	//	}
	//}
}


void Player::Walk() {
	// stageごとに構成が変わるため，stageの移動範囲に合わせたplayerの座標更新を行う
	if (!mIsAtBsSt) {	// boss stageではないとき
		if (key[KEY_INPUT_LEFT] != 0) {	// 左側に移動するとき
			if (mX > X_MIN_N) {	// 左端でないとき
				mX -= (int)(mSpeed);
			}

			if (mX < X_MIN_N) mX = X_MIN_N;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {	// 右側に移動するとき
			if (mX < X_MAX_N) {	// 右端でないとき
				mX += (int)(mSpeed);
			}

			if (mX > X_MAX_N) mX = X_MAX_N;

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && !mIsJumping) {	// 上側に移動するときでジャンプ中でないとき
			if (mY > Y_MIN_N) {	// 上端でないとき
				mY -= (int)(mSpeed);
			}

			if (mY < Y_MIN_N) mY = Y_MIN_N;

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && !mIsJumping) {	// 下側に移動するときでジャンプ中でないとき
			if (mY < Y_MAX_N) {	// 下端でないとき
				mY += (int)(mSpeed);
			}

			if (mY > Y_MAX_N) mY = Y_MAX_N;

			if (mYFrameCnt < 0) {
				mYFrameCnt = 0;
			}
			++mYFrameCnt;
		}
	}
	else {	// boss stageのとき
		if (key[KEY_INPUT_LEFT] != 0) {	// 左側に移動するとき
			if (mX > X_MIN_B) {	// 左端でないとき
				mX -= (int)(mSpeed);
			}

			if (mX < X_MIN_B) mX = X_MIN_B;

			if (mXFrameCnt > 0) {
				mXFrameCnt = 0;
			}
			--mXFrameCnt;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {	// 右側に移動するとき
			if (mIsJumping) {	// ジャンプ中のとき
				if (mX < X_MAX_B) {	// 右端でないとき
					mX += (int)(mSpeed);

					if (mX > X_MAX_B) mX = X_MAX_B;
				}
				else if (mX < X_MAX_BR && mYStart >= Y_MIN_BR && mYStart <= Y_MAX_BR) {	// ジャンプ前に橋の上にいたとき
					mX += (int)(mSpeed);

					if (mX > X_MAX_BR) mX = X_MAX_BR;
				}
			}
			else {	// ジャンプ中でないとき
				if (mX < X_MAX_B) {	// 右端でないとき
					mX += (int)(mSpeed);

					if (mX > X_MAX_B) mX = X_MAX_B;
				}
				else if (mX < X_MAX_BR && mY >= Y_MIN_BR && mY <= Y_MAX_BR) {	// 橋の上にいるとき
					mX += (int)(mSpeed);

					if (mX > X_MAX_BR) mX = X_MAX_BR;
				}
			}

			if (mXFrameCnt < 0) {
				mXFrameCnt = 0;
			}
			++mXFrameCnt;
		}
		if (key[KEY_INPUT_UP] != 0 && !mIsJumping) {	// 上側に移動するときでジャンプ中でないとき
			if (mY > Y_MIN_B && mX <= X_MAX_B) {	// 橋にいなくて，上端でないとき
				mY -= (int)(mSpeed);

				if (mY < Y_MIN_B) mY = Y_MIN_B;	// 更新して
			}
			else if (mY > Y_MIN_BR && mX <= X_MAX_BR) {	// 橋の上にいて，橋の右端でないとき
				mY -= (int)(mSpeed);

				if (mY < Y_MIN_BR) mY = Y_MIN_BR;
			}

			if (mYFrameCnt > 0) {
				mYFrameCnt = 0;
			}
			--mYFrameCnt;
		}
		if (key[KEY_INPUT_DOWN] != 0 && !mIsJumping) {	// 下側に移動するときでジャンプ中でないとき
			if (mY < Y_MAX_B && mX <= X_MAX_B) {	// 橋にいなくて，下端でないとき
				mY += (int)(mSpeed);

				if (mY > Y_MAX_B) mY = Y_MAX_B;
			}
			else if (mY < Y_MAX_BR && mX <= X_MAX_BR) {	// 橋の上にいて，橋の左端でないとき
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
	// playerの座標の更新を行う
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
	// Player4以外このAttack()使う
	// 表示するplayerの画像番号の更新を行う
	mHandleId += 2;

	if (mIsAttacking) {	// 攻撃しているとき
		if (mAFrameCnt > 0) --mAFrameCnt;
		else mIsAttacking = false;
	}
	else {
		mIsAttacking = true;
		mAFrameCnt = mAFrameNum;
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// 左を向いているとき
			mAX = mX - 160;
			mAY = mY + 20;
		}
		else {	// 右を向いているとき
			mAX = mX + 160;
			mAY = mY + 20;
		}
	}
}


//void Player::UpdateHit() {
//	//HitJudge0::SetPlRange(x, y, hitRangeX, hitRangeY);
//	//HitJudge1::SetPlRange(x, y, hitRangeX, hitRangeY);
//	//HitJudge2::SetPlRange(x, y, hitRangeX, hitRangeY);
//
//	//if (mIsAttacking == true) {
//	//	HitJudge0::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
//	//	HitJudge1::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
//	//	HitJudge2::SetPlARange(ax, ay, hitRangeAX, hitRangeAY);
//	//	mIsAttacking = false;
//	//}
//	//else {
//	//	HitJudge0::SetPlARange(-3000, -3000, 0, 0);
//	//	HitJudge1::SetPlARange(-3000, -3000, 0, 0);
//	//	HitJudge2::SetPlARange(-3000, -3000, 0, 0);
//	//}
//
//	//if (mIsGod == false) {
//	//	eneJudge0 = HitJudge0::PEJudge();
//	//	eneJudge1 = HitJudge1::PEJudge();
//	//	eneJudge2 = HitJudge2::PEJudge();
//	//	eneAJudge0 = HitJudge0::EaPJudge();
//	//	eneAJudge1 = HitJudge1::EaPJudge();
//	//	eneAJudge2 = HitJudge2::EaPJudge();
//	//}
//	//
//	//if (icount == 1) {
//	//	iJudge0 = false;
//	//	iJudge1 = false;
//	//	icount++;
//	//}
//	//else if (icount == 2) {
//	//	icount = 0;
//	//}
//	//else {
//	//	iJudge0 = HitJudge0::PIJudge();
//	//	iJudge1 = HitJudge1::PIJudge();
//	//}
//
//	//if (iJudge0 == true || iJudge1 == true) {
//	//	if (iJudge0 == true) {
//	//		weaponNum = PowerBox::GetWpn0Num();
//
//	//		if (weaponNum == 6) { //6は自強化系のItemを表す
//	//			iPower = PowerBox::GetIPower0();
//	//			isPower = PowerBox::GetISPower0();
//	//		}
//	//		
//	//		ihPower = PowerBox::GetIHPower0();
//	//	}
//	//	else {
//	//		weaponNum = PowerBox::GetWpn1Num();
//
//	//		if (weaponNum == 6) { //4は自強化系のItemを表す
//	//			iPower = PowerBox::GetIPower1();
//	//			isPower = PowerBox::GetISPower1();
//	//		}
//
//	//		ihPower = PowerBox::GetIHPower1();
//	//	}
//
//	//	hp = hp + ihPower;
//	//	if (hp < 0) {
//	//		hp = 0;
//	//	}
//	//	else if (hp > 10) {
//	//		hp = 10;
//	//	}
//	//	PlayerData::SetPlayerHP(hp);
//
//	//	if (isPower != 1 && weaponNum == 6) { //なにか効果を受けているときに武器をとってcountが600にリセットされないため
//	//		iscount = 600;
//	//		
//	//		if (isPower == 2) {
//	//			effectHandle = LoadGraph("images/effect_1.png");
//	//			PlayerData::SetEffectNum(1);
//	//		}
//	//		else {
//	//			isPower = 0.5;
//	//			effectHandle = LoadGraph("images/effect_2.png");
//	//			PlayerData::SetEffectNum(2);
//	//		}
//	//	}
//	//	else if (iPower != 1 && weaponNum == 6) {
//	//		ipcount = 600;
//	//		PowerBox::SetPlPower(iPower);
//	//		effectHandle = LoadGraph("images/effect_3.png");
//	//		PlayerData::SetEffectNum(3);
//	//	}
//
//	//	icount++;
//	//}
//
//	//if (eneJudge0 == true || eneJudge1 == true || eneJudge2 == true || eneAJudge0 == true || eneAJudge1 == true || eneAJudge2 == true) {
//	//	if (eneJudge0 == true) {
//	//		enePower = PowerBox::GetEnePower0();
//	//		eneJudge0 = false;
//	//	}
//	//	else if (eneJudge1 == true) {
//	//		enePower = PowerBox::GetEnePower1();
//	//		eneJudge1 = false;
//	//	}
//	//	else if (eneJudge2 == true) {
//	//		enePower = PowerBox::GetEnePower2();
//	//		eneJudge2 = false;
//	//	}
//	//	else if (eneAJudge0 == true) {
//	//		enePower = PowerBox::GetEneAPower0();
//	//		eneAJudge0 = false;
//	//	}
//	//	else if (eneAJudge1 == true) {
//	//		enePower = PowerBox::GetEneAPower1();
//	//		eneAJudge1 = false;
//	//	}
//	//	else {
//	//		enePower = PowerBox::GetEneAPower2();
//	//		eneAJudge2 = false;
//	//	}
//
//	//	hp = hp - enePower;
//	//	if (hp < 0) {
//	//		hp = 0;
//	//	}
//	//	else if (hp > 10) {
//	//		hp = 10;
//	//	}
//	//	PlayerData::SetPlayerHP(hp);
//	//	godCount = 100;
//	//	godFlag = true;
//	//}
//}


void Player::UpdateIteEffect() {
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsHits[i]) {	// Itemに当たっていたら
			int itemId = (int)mIteDataMaps.at(i)["itemId"];

			// 受け取ったItemの種類に合わせた更新を行う
			if (itemId <= 4) {	// 回復系アイテム
				mIteKindId = 5;

				// 回復量の設定
				mIteHP = (int)mIteDataMaps.at(i)["healPower"];
			}
			else if (itemId <= 7) {	// 自強化系アイテム
				mIteKindId = 5;

				// 効果の所持情報の設定
				mEffectId = itemId - 4;
				mIsEffected = true;
				mEffectFrameCnt = 0;
					
				// 自強化系Itemの効果の設定
				mIteAP = (int)mIteDataMaps.at(i)["attackPower"];
				mIteSP = mIteDataMaps.at(i)["speedPower"];

				// 画像の設定
				mEffectHandle = EffectGraphics::GetGraHandle(mEffectId);
			}
			else if (itemId <= 11) {	// 武器
				mIteKindId = itemId - 7;
			}
			else {	// 箱
				mIteKindId = 5;
			}
		}
	}

	// Itemの自強化系効果の更新
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
	if (!mIsGod) {	// 無敵時間でないとき
		// Enemyの身体と攻撃との当たり判定
		for (int i = 0; i < ENEMY_NUM; i++) {
			// Enemyの身体との当たり判定
			if (mEneIsHits[i]) {	// Enemyの身体にあたっていたら
				mEneDamage = 1;
			}

			// Enemyの攻撃との当たり判定
			if (mEneAIsHits[i]) {
				mEneDamage = mEneAPs[i];
			}
		}
	}
}


void Player::UpdateHp() {
	// アイテムによる回復
	if (mIteHP != 0) {
		mHp += mIteHP;

		mIteHP = 0;

		if (mIteHP < 0) {	// アイテムによってダメージを受けたら
			// 少しの間無敵になる
			mIsGod = true;
			mGodFrameCnt = 0;
		}
	}

	// 敵によるダメージ
	if (mEneDamage != 0) {
		mHp -= mEneDamage;

		mEneDamage = 0;
		// 少しの間無敵になる
		mIsGod = true;
		mGodFrameCnt = 0;
	}

	// 体力の補正
	if (mHp > HP_MAX) {	// hpの上限を超えたとき
		mHp = HP_MAX;
	}
	else if (mHp < 0) {	// hpが0未満になった時
		mHp = 0;
	}
}


//void Player::StartBossStage() {
//	// x座標の更新
//	if (mX < PL_FIRST_X_AT_BSST - SPEED_CHANGING_ST) {	// セットしたい位置付近より左側にいたら
//		mX += SPEED_CHANGING_ST;
//		mHandleId = 0;
//
//		if (mXFrameCnt < 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが左側に移動中だったとき）
//			mXFrameCnt = 0;
//		}
//
//		mXFrameCnt++;
//	}
//	else if (mX > PL_FIRST_X_AT_BSST + SPEED_CHANGING_ST) {	// セットしたい位置付近より右側にいたら
//		mX -= SPEED_CHANGING_ST;
//		mHandleId = 6;
//
//		if (mXFrameCnt > 0) {	// BossStageに入ったときにmXFrameCntが0より大きいとき（Playerが右側に移動中だったとき）
//			mXFrameCnt = 0;
//		}
//
//		mXFrameCnt--;
//	}
//	else {
//		mHandleId = 0;
//		mXFrameCnt = 0;
//	}
//
//	// y座標の更新
//	if (mY < PL_FIRST_Y_AT_BSST - SPEED_CHANGING_ST) {	// セットしたい位置付近より上側にいたら
//		mY += SPEED_CHANGING_ST;
//		
//		if (mYFrameCnt < 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが上側に移動中だったとき）
//			mYFrameCnt = 0;
//		}
//
//		mYFrameCnt++;
//	}
//	else if (mY > PL_FIRST_Y_AT_BSST + SPEED_CHANGING_ST) {	// セットしたい位置付近より下側にいたら
//		mY -= SPEED_CHANGING_ST;
//
//		if (mYFrameCnt > 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが下側に移動中だったとき）
//			mYFrameCnt = 0;
//		}
//
//		mYFrameCnt--;
//	}
//	else {
//		mYFrameCnt = 0;
//	}
//
//	// 表示するplayerの画像番号の更新を行う
//	int ix = abs(mXFrameCnt) % 40 / 20;
//	int iy = abs(mYFrameCnt) % 40 / 20;
//
//	if (mXFrameCnt != 0) {
//		mHandleId = ix;
//	}
//	if (mYFrameCnt != 0) {
//		mHandleId = iy;
//	}
//
//	if (mXFrameCnt > 0) {
//		ix += 0;
//		mHandleId = ix;
//	}
//	else if (mXFrameCnt < 0) {
//		ix += 6;
//		mHandleId = ix;
//	}
//	if (mYFrameCnt != 0) {
//		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// 左を向いているとき
//			iy += 6;
//		}
//
//		mHandleId = iy;
//	}
//}


void Player::SetPlParams(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	// パラメータで受け取った値を代入する
	mX = (*plIntDataMap)["x"];
	mY = (*plIntDataMap)["y"];
	mHp = (*plIntDataMap)["hp"];
	mEffectFrameCnt = (*plIntDataMap)["effectFrameCnt"];
	//mIteAFrameCnt = (*plIntDataMap)["iteAFrameCnt"];
	mBsStopFrameCnt = (*plIntDataMap)["bsStopFrameCnt"];
	mEffectId = (*plIntDataMap)["effectId"];
	//mDeadFrameCnt = (*plIntDataMap)["deadFrameCnt"];
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
	// 各Enemyとの当たり判定をセット
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneIsHits[i] = (*isHitMap)["enemy"].at(i);
		mEneAIsHits[i] = (*isHitMap)["enemyAttack"].at(i);
		mPlAIsHitMap["enemy"].at(i) = (*isHitMap)["plAToEnemy"].at(i);
	}

	// 各Itemとの当たり判定をセット
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteIsHits[i] = (*isHitMap)["item"].at(i);
		mPlAIsHitMap["item"].at(i) = (*isHitMap)["plAToItem"].at(i);
	}
}


void Player::SetIteParams(std::vector<std::map<std::string, float>>& iteDataMaps) {
	// 各Itemの効果の情報をセット
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.at(i)["healPower"] = iteDataMaps.at(i)["healPower"];
		mIteDataMaps.at(i)["speedPower"] = iteDataMaps.at(i)["speedPower"];
		mIteDataMaps.at(i)["attackPower"] = iteDataMaps.at(i)["attackPower"];
		mIteDataMaps.at(i)["itemId"] = iteDataMaps.at(i)["itemId"];
	}
}


void Player::SetEneAPowers(const int* const eneAPs) {
	// 各Enemyの攻撃力のセット
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneAPs[i] = eneAPs[i];
	}
}


void Player::SetIsChangingSt(const bool isChangingSt) {
	// BossStageへ変更中かどうかセット
	mIsChangingSt = isChangingSt;
}


void Player::SetIsAtBsSt(const bool isAtBsSt) {
	// BossStageに入っているかどうかセット
	mIsAtBsSt = isAtBsSt;
}