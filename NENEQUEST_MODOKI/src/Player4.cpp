// 弓（攻撃力：普通，攻撃範囲：広い，攻撃持続時間：長い（次の攻撃までにかかる時間：長い），扱い難易度：難しい）

#include "Player4.h"
#include "DxLib.h"
#include "PlayerMgr.h"

Player4* Player4::mPlayer4;


Player4::Player4(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 4)) {
	mPlayerMgr = PlayerMgr::GetInstance();
}


Player4::~Player4() {
	delete mPlayer4;
}


Player4* Player4::GetInstance() {
	if (mPlayer4 == NULL) {
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
	mHitRangeAW = 45, mHitRangeAH = 60;

	// Playerの攻撃の状態設定
	mAttack = 1;
	// mAFrameNum は強い弓：120，弱い弓：90

	// アイテムや使用武器の設定
	mIteKindId = 4;
	// 弓関連の設定
	mIsPreparingWA = false;
	mIsPreparingSA = false;
	mArrow = new Arrow();
	mArrow->Initialize();
	mArrowExists = false;
}


void Player4::Finalize() {
	Player::Finalize();

	delete mArrow;
}

void Player4::Update() {
	if (mHp == 0) {	// 死んだときの処理（死んだことを認識させるための120フレームの硬直）
		if (mDeadFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		mHandleId = 0;

		mDeadFrameCnt++;
	}
	else {	// 生きているときの処理
		// boss stageに突入しているかしていないかチェック
		//mIsAtBsSt = PlayerData::GetBossFlag();

		if (mIsAtBsSt == true && mBsStopFrameCnt <= 1280) {	// boss stageの始まる際の強制的な移動処理
			StartBossStage();
		}
		else {
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
			if (!mIsAttacking && (mIsJumping == true || key[KEY_INPUT_A] == 1)) {	// 攻撃中でなく，かつジャンプ中，もしくはジャンプ入力キーを押しているとき
				Jump();
			}
			else if (mIsAttacking) {	// 攻撃中であるとき（弓矢を放ったあと）
				Attack();

				if (mArrowExists) {	// 弓矢の攻撃が残っているとき
					mArrow->Update();
				}

				// 攻撃時間が終わったら次の攻撃ができるようにする
				if (mAFrameCnt == 0) mIsAttacking = false;
			}
			else if ((key[KEY_INPUT_S] == 1 || mIsPreparingWA) && !mIsPreparingSA) {	//	弱い弓を打とうとしているとき
				PrepareWAttack();
			}
			else if (key[KEY_INPUT_D] == 1 || mIsPreparingSA) {	// 強い弓を打とうとしているとき
				PrepareSAttack();
			}

			//HitJudge();
		}
	}

	// ダメージを受けた後の少しの間の無敵時間の処理
	if (mIsGod == true) {
		if (mGodFrameCnt == -1) {
			mIsGod = false;
		}
		else if (mGodFrameCnt > 80 || (mGodFrameCnt <= 60 && mGodFrameCnt > 40) || mGodFrameCnt <= 20) {	// Playerを白くする
			mHandleId += 16;
			--mGodFrameCnt;
		}
		else {
			--mGodFrameCnt;
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
		if (mIsJumping == true) {	// ジャンプしているとき
			mSpeed = 0.8f;
		}
		else if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// 攻撃しているときor攻撃準備中のとき
			mSpeed = 0.5f;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
			mSpeed = 0.625f;
		}
		else {
			mSpeed = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {	// 上下の入力があるとき
		if (mIsAttacking || mIsPreparingWA || mIsPreparingSA) {	// 攻撃しているときor攻撃準備中のとき
			mSpeed = 0.5f;
		}
		else {
			mSpeed = 0.80f;
		}
	}

	// 移動速度（アイテム効果）の更新
	if (mHasIteS) {
		if (mIteSFrameCnt != 0) {	// 効果中のとき
			mSpeed *= mIteSP;
			mIteSFrameCnt--;
		}
		else {	// 効果切れのとき
			mIteSP = 1.0f;
			mEffectHandle = 0;
			mHasIteS = false;
		}
	}

	// 攻撃力（アイテム効果）の更新
	if (mHasIteA) {
		if (mIteAFrameCnt != 0) {	// 効果中のとき
			mAttack *= mIteAP;
			mIteAFrameCnt--;
		}
		else {	// 効果切れのとき
			mIteAP = 1;
			mEffectHandle = 0;
			mHasIteA = false;
		}
	}
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
	
	--mAFrameCnt;
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
		mAFrameCnt = 90; //矢を放った後の硬直する時間も含んでいる
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
		mAFrameCnt = 120;
	}
}

void Player4::UpdateHit() {
	//HitJudge0::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge1::SetPlRange(x, y, hitRangeX, hitRangeY);
	//HitJudge2::SetPlRange(x, y, hitRangeX, hitRangeY);

	//if (godFlag == false) {
	//	eneJudge0 = HitJudge0::PEJudge();
	//	eneJudge1 = HitJudge1::PEJudge();
	//	eneJudge2 = HitJudge2::PEJudge();
	//	eneAJudge0 = HitJudge0::EaPJudge();
	//	eneAJudge1 = HitJudge1::EaPJudge();
	//	eneAJudge2 = HitJudge2::EaPJudge();
	//}

	//if (icount == 1) {
	//	iJudge0 = false;
	//	iJudge1 = false;
	//	icount++;
	//}
	//else if (icount == 2) {
	//	icount = 0;
	//}
	//else {
	//	iJudge0 = HitJudge0::PIJudge();
	//	iJudge1 = HitJudge1::PIJudge();
	//}

	//if (iJudge0 == true || iJudge1 == true) {
	//	if (iJudge0 == true) {
	//		weaponNum = PowerBox::GetWpn0Num();

	//		if (weaponNum == 6) { //6は自強化系のItemを表す
	//			iPower = PowerBox::GetIPower0();
	//			isPower = PowerBox::GetISPower0();
	//		}

	//		ihPower = PowerBox::GetIHPower0();
	//	}
	//	else {
	//		weaponNum = PowerBox::GetWpn1Num();

	//		if (weaponNum == 6) { //6は自強化系のItemを表す
	//			iPower = PowerBox::GetIPower1();
	//			isPower = PowerBox::GetISPower1();
	//		}

	//		ihPower = PowerBox::GetIHPower1();
	//	}

	//	hp = hp + ihPower;
	//	if (hp < 0) {
	//		hp = 0;
	//	}
	//	else if (hp > 10) {
	//		hp = 10;
	//	}
	//	PlayerData::SetPlayerHP(hp);

	//	if (isPower != 1 && weaponNum == 6) {
	//		iscount = 600;

	//		if (isPower == 2) {
	//			effectHandle = LoadGraph("images/effect_1.png");
	//		}
	//		else {
	//			isPower = 0.5;
	//			effectHandle = LoadGraph("images/effect_2.png");
	//		}
	//	}
	//	else if (iPower != 1 && weaponNum == 6) {
	//		ipcount = 600;
	//		PowerBox::SetPlPower(iPower);
	//		effectHandle = LoadGraph("images/effect_3.png");
	//	}

	//	icount++;
	//}

	//if (eneJudge0 == true || eneJudge1 == true || eneJudge2 == true || eneAJudge0 == true || eneAJudge1 == true || eneAJudge2 == true) {
	//	if (eneJudge0 == true) {
	//		enePower = PowerBox::GetEnePower0();
	//		eneJudge0 = false;
	//	}
	//	else if (eneJudge1 == true) {
	//		enePower = PowerBox::GetEnePower1();
	//		eneJudge1 = false;
	//	}
	//	else if (eneJudge2 == true) {
	//		enePower = PowerBox::GetEnePower2();
	//		eneJudge2 = false;
	//	}
	//	else if (eneAJudge0 == true) {
	//		enePower = PowerBox::GetEneAPower0();
	//		eneAJudge0 = false;
	//	}
	//	else if (eneAJudge1 == true) {
	//		enePower = PowerBox::GetEneAPower1();
	//		eneAJudge1 = false;
	//	}
	//	else {
	//		enePower = PowerBox::GetEneAPower2();
	//		eneAJudge2 = false;
	//	}

	//	hp = hp - enePower;
	//	if (hp < 0) {
	//		hp = 0;
	//	}
	//	else if (hp > 10) {
	//		hp = 10;
	//	}
	//	PlayerData::SetPlayerHP(hp);
	//	godCount = 100;
	//	godFlag = true;
	//}
}

void Player4::StartBossStage() {

	//attackFlag = mArrow->GetArrowFlag();

	//if (attackFlag == true) {
	//	mArrow->Update();
	//}

	//prev_x = x;
	//prev_y = y;
	//prev_xcount = xcount;
	//prev_ycount = ycount;

	//if (x > 353) {
	//	x -= 2;

	//	/*if (xcount > 0) {
	//	xcount = 0;
	//	}*/
	//	--xcount;
	//}
	//if (x < 349) {
	//	x += 2;

	//	/*if (xcount < 0) {
	//	xcount = 0;
	//	}*/
	//	++xcount;
	//}
	//if (y > 453) {
	//	y -= 2;

	//	/*if (ycount > 0) {
	//	ycount = 0;
	//	}*/
	//	--ycount;
	//}
	//if (y < 449) {
	//	prev_y = y;
	//	y += 2;

	//	/*if (ycount < 0) {
	//	ycount = 0;
	//	}*/
	//	++ycount;
	//}


	//if (y == prev_y && x == prev_x) {
	//	handleNumber = 0;
	//}
	//else {
	//	if (xcount != prev_xcount) {
	//		ix = abs(xcount) % 40 / 20;

	//		if (xcount > 0) {
	//			ix += 0;
	//			handleNumber = ix;
	//		}
	//		else if (xcount < 0) {
	//			ix += 8;
	//			handleNumber = ix;
	//		}
	//	}

	//	if (prev_ycount != prev_ycount && ycount != 0) {
	//		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
	//			iy += 8;
	//		}

	//		handleNumber = iy;
	//	}
	//}

	//PlayerData::SetBscount(bscount + 1);
	//bscount++;
}