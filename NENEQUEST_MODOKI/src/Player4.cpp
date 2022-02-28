// 弓（攻撃力：普通，攻撃範囲：広い，攻撃持続時間：長い（次の攻撃までにかかる時間：長い），扱い難易度：難しい）

#include "Player4.h"
#include "DxLib.h"
#include "PlayerMgr.h"


Player4* Player4::mPlayer4;


Player4::Player4(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 4)) {
	//mPlayerMgr = PlayerMgr::GetInstance();
}


Player4* Player4::GetInstance() {
	if (!mPlayer4) {
		PlayerMgr* playerMgr = PlayerMgr::GetInstance();
		mPlayer4 = new Player4(playerMgr);
		// InitializeはGetInstanceの呼び出し側にSetPlParamsとともに行ってもらう
	}

	return mPlayer4;
}


void Player4::Initialize() {
	Player::Initialize();

	// 位置，当たり判定の範囲関連設定
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 20, mHitRangeAH = 20;	// 弓矢の当たり判定

	// Playerの攻撃の状態設定
	mAttackBase = 1;
	mAttack = mAttackBase;
	// mAFrameNum は強い弓：120，弱い弓：90

	// Playerの移動速度倍率
	mSpeedRate = 1.0f;

	// アイテムや使用武器の設定
	mIteKindId = 4;
	// 弓関連の設定
	mIsPreparingWA = false;
	mIsPreparingSA = false;
	mArrow = new Arrow();
	mArrow->Initialize();
	mArrowExists = false;
	mArrowIsHit = false;
}


void Player4::Finalize() {
	Player::Finalize();

	delete mArrow;
	delete mPlayer4;
	mPlayer4 = NULL;
}


void Player4::Update() {
	if (mHp <= 0) {	// 死んだときの処理（死んだことを認識させるための120フレームの硬直）
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		else if (mGodFrameCnt == 0) {	// 最初に通ったとき
			// ダメージをくらったことがわかる画像にする
			mHandleId += 16;
		}

		mGodFrameCnt++;
	}
	else {	// 生きているときの処理
		// boss stageに突入しているかしていないかチェック
		//mIsAtBsSt = PlayerData::GetBossFlag();

		if (mIsChangingSt) {	// BossStageの始まる際の強制的な移動処理
			StartBossStage();
		}
		else {
			// Enemyとの当たり判定を考慮したEnemyから受けるダメージの更新
			UpdateEneDamage();

			// アイテムとの当たり判定を考慮したアイテムの効果の更新
			UpdateIteEffect();

			// hpの更新
			UpdateHp();

			// 武器交換をするとき
			if (mIteKindId == 1) {
				mPlayerChanger->ChangePlayer(ePlayer1);
			}
			else if (mIteKindId == 2) {
				mPlayerChanger->ChangePlayer(ePlayer2);
			}
			else if (mIteKindId == 3) {
				mPlayerChanger->ChangePlayer(ePlayer3);
			}

			// キー入力の取得
			gpUpdateKey();

			// 左右上下方向のキーを連続で押しているフレーム数の更新
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0) {
				mXFrameCnt = 0;
			}
			if (key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				mYFrameCnt = 0;
			}

			// 立ち止まったら立ち止まりの画像番号にする
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0 && key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
					mHandleId = 8;
				}
				else {
					mHandleId = 0;
				}
			}

			// playerの行う動作に対応した移動速度，攻撃力に更新
			UpdateSAP();

			// キー入力があった際は移動処理をする
			if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0 || key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
				Walk();
			}

			// 弓矢の攻撃効果が残っているか確認
			mArrowExists = mArrow->GetArrowExists();

			// ジャンプと攻撃の処理
			if (!mIsAttacking && (mIsJumping || key[KEY_INPUT_A] == 1)) {	// 攻撃中でなく，かつジャンプ中，もしくはジャンプ入力キーを押しているとき
				Jump();
			}
			else if (mIsAttacking) {	// 攻撃中であるとき（弓矢を放ったあと）
				Attack();

				if (mArrowExists) {	// 弓矢の攻撃が残っているとき
					mArrow->Update();

					// 攻撃座標の更新
					std::tie(mAX, mAY) = mArrow->GetArrowXY();

					if (!mArrowIsHit) {	// 弓矢が何にもあたっていないとき
						UpdateArrowIsHit();
					}
				}

				// 攻撃時間が終わったら次の攻撃ができるようにする
				if (mAFrameCnt == mAFrameNum) {
					mIsAttacking = false;
					mArrowIsHit = false;
				}
			}
			else if ((key[KEY_INPUT_S] == 1 || mIsPreparingWA) && !mIsPreparingSA) {	//	弱い弓を打とうとしているとき
				PrepareWAttack();
			}
			else if (key[KEY_INPUT_D] == 1 || mIsPreparingSA) {	// 強い弓を打とうとしているとき
				PrepareSAttack();
			}

			// ダメージを受けた後の少しの間の無敵時間の処理
			if (mIsGod) {	// 攻撃を受けた後の無敵時間のとき
				if (mGodFrameCnt == GOD_FRAME_NUM) {	// 無敵時間が終わったら
					mIsGod = false;
					mGodFrameCnt = 0;
				}
				else {	// 無敵時間中なら
					// 無敵時間であることを表す画像にする
					if ((mGodFrameCnt / 20) % 2 == 0) {	// 点滅処理
						mHandleId += 16;
					}
				}

				mGodFrameCnt++;
			}
		}
	}
}


void Player4::Draw() {
	Player::Draw();

	if (mArrowExists) {
		mArrow->Draw();
	}
}


void Player4::UpdateSAP() {
	// 移動速度の更新
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {	// 左右の入力があるとき
		if (mIsJumping) {	// ジャンプしているとき
			mSpeed = 4 * 0.8f * mSpeedRate;
		}
		else if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// 攻撃しているときor攻撃準備中のとき
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
		if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// 攻撃しているときor攻撃準備中のとき
			mSpeed = 4 * 0.5f * mSpeedRate;
		}
		else {
			mSpeed = 4 * 0.80f * mSpeedRate;
		}
	}

	// 移動速度（アイテム効果）の更新
	mSpeed *= mIteSP;
	//if (mHasIteS) {
	//	if (mIteSFrameCnt != 0) {	// 効果中のとき
	//		mSpeed *= mIteSP;
	//		mIteSFrameCnt--;
	//	}
	//	else {	// 効果切れのとき
	//		mIteSP = 1.0f;
	//		mEffectHandle = 0;
	//		mHasIteS = false;
	//	}
	//}

	// 攻撃力の更新
	mAttack = mAttackBase;

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


void Player4::Walk() {
	// stageごとに構成が変わるため，stageの移動範囲に合わせたplayerの座標更新を行う
	Player::Walk();

	// 表示するplayerの画像番号の更新を行う
	int ix = abs(mXFrameCnt) % 40 / 20;
	int iy = abs(mYFrameCnt) % 40 / 20;

	if (mXFrameCnt > 0) {
		ix += 0;
		mHandleId = ix;
	}
	else if (mXFrameCnt < 0) {
		ix += 8;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// 左を向いているとき
			iy += 8;
		}

		mHandleId = iy;
	}
}


void Player4::Attack() {
	mHandleId += 4;
	
	mAFrameCnt++;
}


void Player4::Jump() {
	// 表示するplayerの画像番号の更新を行う
	if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// 左を向いているとき
		mHandleId = 14;
	}
	else {	// 右を向いているとき
		mHandleId = 6;
	}

	// playerの座標の更新を行う
	Player::Jump();
}


void Player4::PrepareWAttack() {	// 弱い攻撃（弓矢が近くに落ちる，入力Dキー）
	mHandleId += 2;

	if (key[KEY_INPUT_S] >= 1) {	// 弓矢を構えているとき
		mIsPreparingWA = true;
	}
	else {	// 弓矢を放つとき
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
			mAX = mX - 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 2);
		}
		else {
			mAX = mX + 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 1);
		}

		mIsPreparingWA = false;
		mIsAttacking = true;
		mAFrameCnt = 0;
		mAFrameNum = 90; //矢を放った後の硬直する時間も含んでいる
	}
}


void Player4::PrepareSAttack() {	// 強い攻撃（弓矢が遠くまで飛ぶ，入力Sキー）
	mHandleId += 2;

	if (key[KEY_INPUT_D] >= 1) {
		mIsPreparingSA = true;
	}
	else {	// 弓矢を放つとき
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {
			mAX = mX - 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 4);
		}
		else {
			mAX = mX + 20;
			mAY = mY + 20;

			mArrow->StartArrow(mAX, mAY, 3);
		}

		mIsPreparingSA = false;
		mIsAttacking = true;
		mAFrameCnt = 0;
		mAFrameNum = 120;
	}
}


void Player4::UpdateArrowIsHit() {
	// 弓矢-Enemy間
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mPlAIsHitMap["enemy"].at(i)) {
			mArrowIsHit = true;
		}
	}
	// 弓矢-Item間
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mPlAIsHitMap["item"].at(i)) {
			mArrowIsHit = true;
		}
	}

	mArrow->SetIsHit(mArrowIsHit);
}


void Player4::GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	Player::GetPlDataMap(plIntDataMap, plBoolDataMap);

	// 弓矢が動いている間のみ当たり判定のある攻撃中とみなす
	(*plBoolDataMap)["isAttacking"] = mArrow->GetIsMoving();
}


//void Player4::StartBossStage() {
//
//	//attackFlag = mArrow->GetArrowFlag();
//
//	//if (attackFlag == true) {
//	//	mArrow->Update();
//	//}
//
//	//prev_x = x;
//	//prev_y = y;
//	//prev_xcount = xcount;
//	//prev_ycount = ycount;
//
//	//if (x > 353) {
//	//	x -= 2;
//
//	//	/*if (xcount > 0) {
//	//	xcount = 0;
//	//	}*/
//	//	--xcount;
//	//}
//	//if (x < 349) {
//	//	x += 2;
//
//	//	/*if (xcount < 0) {
//	//	xcount = 0;
//	//	}*/
//	//	++xcount;
//	//}
//	//if (y > 453) {
//	//	y -= 2;
//
//	//	/*if (ycount > 0) {
//	//	ycount = 0;
//	//	}*/
//	//	--ycount;
//	//}
//	//if (y < 449) {
//	//	prev_y = y;
//	//	y += 2;
//
//	//	/*if (ycount < 0) {
//	//	ycount = 0;
//	//	}*/
//	//	++ycount;
//	//}
//
//
//	//if (y == prev_y && x == prev_x) {
//	//	handleNumber = 0;
//	//}
//	//else {
//	//	if (xcount != prev_xcount) {
//	//		ix = abs(xcount) % 40 / 20;
//
//	//		if (xcount > 0) {
//	//			ix += 0;
//	//			handleNumber = ix;
//	//		}
//	//		else if (xcount < 0) {
//	//			ix += 8;
//	//			handleNumber = ix;
//	//		}
//	//	}
//
//	//	if (prev_ycount != prev_ycount && ycount != 0) {
//	//		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
//	//			iy += 8;
//	//		}
//
//	//		handleNumber = iy;
//	//	}
//	//}
//
//	//PlayerData::SetBscount(bscount + 1);
//	//bscount++;
//}

void Player4::StartBossStage() {
	// 弓矢の更新
	mArrowExists = mArrow->GetArrowExists();

	if (mArrowExists) {
		mArrow->Update();
	}

	// x座標の更新
	if (mX < PL_FIRST_X_AT_BSST - SPEED_CHANGING_ST) {	// セットしたい位置付近より左側にいたら
		mX += SPEED_CHANGING_ST;
		mHandleId = 0;

		if (mXFrameCnt < 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが左側に移動中だったとき）
			mXFrameCnt = 0;
		}

		mXFrameCnt++;
	}
	else if (mX > PL_FIRST_X_AT_BSST + SPEED_CHANGING_ST) {	// セットしたい位置付近より右側にいたら
		mX -= SPEED_CHANGING_ST;
		mHandleId = 8;

		if (mXFrameCnt > 0) {	// BossStageに入ったときにmXFrameCntが0より大きいとき（Playerが右側に移動中だったとき）
			mXFrameCnt = 0;
		}

		mXFrameCnt--;
	}
	else {
		mHandleId = 0;
		mXFrameCnt = 0;
	}

	// y座標の更新
	if (mY < PL_FIRST_Y_AT_BSST - SPEED_CHANGING_ST) {	// セットしたい位置付近より上側にいたら
		mY += SPEED_CHANGING_ST;

		if (mYFrameCnt < 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが上側に移動中だったとき）
			mYFrameCnt = 0;
		}

		mYFrameCnt++;
	}
	else if (mY > PL_FIRST_Y_AT_BSST + SPEED_CHANGING_ST) {	// セットしたい位置付近より下側にいたら
		mY -= SPEED_CHANGING_ST;

		if (mYFrameCnt > 0) {	// BossStageに入ったときにmXFrameCntが0より小さいとき（Playerが下側に移動中だったとき）
			mYFrameCnt = 0;
		}

		mYFrameCnt--;
	}
	else {
		mYFrameCnt = 0;
	}

	// 表示するplayerの画像番号の更新を行う
	int ix = abs(mXFrameCnt) % 40 / 20;
	int iy = abs(mYFrameCnt) % 40 / 20;

	if (mXFrameCnt != 0) {
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		mHandleId = iy;
	}

	if (mXFrameCnt > 0) {
		ix += 0;
		mHandleId = ix;
	}
	else if (mXFrameCnt < 0) {
		ix += 8;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 7 && mHandleId < 16) || mHandleId > 23) {	// 左を向いているとき
			iy += 8;
		}

		mHandleId = iy;
	}

	mIsAttacking = false;
	mIsJumping = false;
}