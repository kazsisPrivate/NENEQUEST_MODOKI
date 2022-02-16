// 剣1（攻撃力：普通，攻撃範囲：少し広い，攻撃持続時間：普通（次の攻撃までにかかる時間：普通），扱い難易度：普通）

#include "Player1.h"
#include "DxLib.h"
#include "PlayerMgr.h"

Player1* Player1::mPlayer1;


Player1::Player1(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 1)) {
	//mPlayerMgr = PlayerMgr::GetInstance();
}


Player1* Player1::GetInstance() {
	if (!mPlayer1) {
		PlayerMgr* playerMgr = PlayerMgr::GetInstance();
		mPlayer1 = new Player1(playerMgr);
		// InitializeはGetInstanceの呼び出し側にSetPlParamsとともに行ってもらう
	}

	return mPlayer1;
}


void Player1::Initialize() {
	Player::Initialize();

	// 位置，当たり判定の範囲関連設定
	mHitRangeW = 33, mHitRangeH = 60;
	mHitRangeAW = 50, mHitRangeAH = 60;

	// Playerの攻撃の状態設定
	mAttackBase = 1;
	mAttack = mAttackBase;
	mAFrameNum = 20;
	
	// アイテムや使用武器の設定
	mIteKindId = 1;
}


void Player1::Finalize() {
	Player::Finalize();

	delete mPlayer1;
	mPlayer1 = NULL;
}


void Player1::Update() {
	if (mHp <= 0) {	// 死んだときの処理（死んだことを認識させるための120フレームの硬直）
		if (mGodFrameCnt == DEAD_STOP_FRAME_NUM) {
			mIsDead = true;
		}
		else if (mGodFrameCnt == 0) {	// 最初に通ったとき
			// ダメージをくらったことがわかる画像にする
			mHandleId += 12;
		}

		mGodFrameCnt++;
	}
	else {	// 生きているときの処理
		// boss stageに突入しているかしていないかチェック
		//mIsAtBsSt = PlayerData::GetBossFlag();

		// Enemyとの当たり判定を考慮したEnemyから受けるダメージの更新
		UpdateEneDamage();

		// Itemとの当たり判定を考慮したアイテムの効果の更新
		UpdateIteEffect();

		// hpの更新
		UpdateHp();
		
		if (mIsAtBsSt == true && mBsStopFrameCnt <= 1280) {	// boss stageの始まる際の強制的な移動処理
			StartBossStage();
		}
		else {
			// 武器交換をするとき
			if (mIteKindId == 2) {
				mPlayerChanger->ChangePlayer(ePlayer2);
			}
			else if (mIteKindId == 3) {
				mPlayerChanger->ChangePlayer(ePlayer3);
			}
			else if (mIteKindId == 4) {
				mPlayerChanger->ChangePlayer(ePlayer4);
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
				if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {
					mHandleId = 6;
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

			// ジャンプと攻撃の処理
			if (!mIsAttacking && (mIsJumping == true || key[KEY_INPUT_A] == 1)) {	// 攻撃中でなく，かつジャンプ中，もしくはジャンプ入力キーを押しているとき
				Jump();
			}
			else if (mIsAttacking || key[KEY_INPUT_S] == 1) {	// 攻撃中であるか，攻撃キーを押しているとき
				Attack();
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
						mHandleId += 12;
					}
				}

				mGodFrameCnt++;
			}
		}
	}

}


//void Player1::Draw() {
//	Player::Draw();
//}
//
//
//void Player1::UpdateSAP() {
//	Player::UpdateSAP();
//}


void Player1::Walk() {
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
		ix += 6;
		mHandleId = ix;
	}
	if (mYFrameCnt != 0) {
		if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// 左を向いているとき
			iy += 6;
		}
		
		mHandleId = iy;
	}
}


//void Player1::Attack() {
//	Player::Attack();
//}


void Player1::Jump() {
	// 表示するplayerの画像番号の更新を行う
	if ((mHandleId > 5 && mHandleId < 12) || mHandleId > 17) {	// 左を向いているとき
		mHandleId = 10;
	}
	else {	// 右を向いているとき
		mHandleId = 4;
	}

	// playerの座標の更新を行う
	Player::Jump();
}