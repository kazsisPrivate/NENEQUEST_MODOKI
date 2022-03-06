#include "DxLib.h"
#include "GameScene.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"
#include "EffectGraphics.h"
#include "SceneMgr.h"
#include <mutex>
#include <vector>
#include <algorithm>


GameScene* GameScene::mGameScene;


GameScene::GameScene(SceneChanger* changer) : BaseScene(changer) {
}


GameScene* GameScene::GetInstance() {
	if (!GameScene::mGameScene) {
		SceneMgr* sceneMgr = SceneMgr::GetInstance();
		GameScene::mGameScene = new GameScene(sceneMgr);
		GameScene::mGameScene->Initialize();
	}

	return GameScene::mGameScene;
}


void GameScene::Initialize() {
	// 情報を保持するためのmap(vector)の初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneIntDataMaps.push_back({});
		mEneBoolDataMaps.push_back({});
		mEneIsHits[i] = false;
		mPlIsHitMap["enemy"].push_back(false);
		mPlIsHitMap["enemyAttack"].push_back(false);
		mPlIsHitMap["plAToEnemy"].push_back(false);
		mEneAXYMapVecs.push_back(std::vector<std::map<std::string, int>>());

		for (int j = 0; j < ENEMY_ATTACK_NUM; j++) {
			mEneAXYMapVecs.at(i).push_back({});
		}
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mIteIntDataMaps.push_back({});
		mIteBoolDataMaps.push_back({});
		mIteIsHitMaps.push_back({});
		mPlIsHitMap["item"].push_back(false);
		mPlIsHitMap["plAToItem"].push_back(false);
	}

	// 画面の各構成要素のインスタンスの取得
	mGameBack = new GameBack();
	mPlayerMgr = PlayerMgr::GetInstance();
	mEnemyMgr = EnemyMgr::GetInstance();
	mItemMgr = ItemMgr::GetInstance();
	mPlHpGauge = new PlayerHpGauge();
	mTimeCounter = new TimeCounter();
	mScoreCounter = new ScoreCounter();
	mGameOver = new GameOver();
	mGameClear = new GameClear();

	// 画面の各構成要素の初期化
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	mEnemyMgr->Initialize();
	mItemMgr->Initialize();
	mPlHpGauge->Initialize();
	mTimeCounter->Initialize();
	mScoreCounter->Initialize();
	mGameOver->Initialize();
	mGameClear->Initialize();

	// 音源の初期化
	mSoundHandle = LoadSoundMem("sounds/NENEQUEST.ogg");
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);

	// フレーム数のカウントの初期化
	mFrameCnt = 0;

	// Playerは死んでいない状態として設定
	mPlIsDead = false;

	// Stage関連の設定
	mIsChangingSt = false;
	mIsAtBsSt = false;

	// Timerを開始する
	mTimeCounter->StartTime();
}

void GameScene::Finalize() {
	// 画面の各構成要素の終了処理
	mGameBack->Finalize();
	mPlayerMgr->Finalize();
	mEnemyMgr->Finalize();
	mItemMgr->Finalize();
	mPlHpGauge->Finalize();
	mTimeCounter->Finalize();
	mScoreCounter->Finalize();
	mGameOver->Finalize();
	mGameClear->Finalize();

	// ゲームの音楽の削除
	StopSoundMem(mSoundHandle);
	DeleteSoundMem(mSoundHandle);

	delete mGameScene;
	mGameScene = NULL;
}

void GameScene::Update() {
	// Escキーでゲームを止められるようにする
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		mSceneChanger->ChangeScene(eSceneMenu);
	}

	if (mHasClearedGame) {	// ゲームクリアして（EnemyBossを倒して）いたら
		// GameClear画面の更新
		mGameClear->Update();
	}
	else if (mPlIsDead) {	// Playerが死んでいたら
		// GameOver画面の更新
		mGameOver->Update();
	}
	else {	// Playerが死んでいなかったら
		// Player, Enemy, Itemの情報を取得
		mPlayerMgr->GetPlData(&mPlIntDataMap, &mPlBoolDataMap);
		mEnemyMgr->GetEneData(&mEneIntDataMaps, &mEneAXYMapVecs, &mEneBoolDataMaps, mEneIsExistings);
		mItemMgr->GetIteData(&mIteIntDataMaps, &mIteBoolDataMaps, mIteIsExistings);

		// Playerに渡すEnemyの攻撃力を一つの配列にまとめる
		int eneAPs[3];	// ENEMY_NUM = 3
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mEneIsExistings) {
				eneAPs[i] = mEneIntDataMaps.at(i)["attack"];
			}
			else {
				eneAPs[i] = 0;
			}
		}

		// Player, Enemy, Item間で使用する情報をお互いに渡す
		mPlayerMgr->SetIteDataMaps(mIteIntDataMaps);
		mPlayerMgr->SetEneAPowers(eneAPs);
		mEnemyMgr->SetPlDataMap(&mPlIntDataMap);
		mPlHpGauge->SetPlayerHp(mPlIntDataMap["hp"]);

		// Playerが死んでいるかどうかを入れる
		mPlIsDead = mPlBoolDataMap["isDead"];

		// EnemyがBossだった際の特別な処理
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mEneIsExistings[i]) {
				if (mEneBoolDataMaps.at(i)["isBoss"]) {	// Bossだったとき
					if (mEneBoolDataMaps.at(i)["isDead"]) {	// Bossが倒されたとき
						// ゲームクリアとする
						mHasClearedGame = true;
						mTimeCounter->StopTime();
					}

					if (mEneBoolDataMaps.at(i)["isCreatingIteB"]) {	// ItemBoxを生成してほしいときだったら
						mItemMgr->CreateItem(mEneIntDataMaps.at(i)["itemBoxKind"],
							mEneIntDataMaps.at(i)["itemBoxX"], mEneIntDataMaps.at(i)["itemBoxY"]);
					}
				}
			}
		}

		// 各オブジェクトの当たり判定を確認
		UpdateHit();

		// 当たり判定の確認結果のデータを各オブジェクトに渡す
		mPlayerMgr->SetIsHitMap(&mPlIsHitMap);
		mEnemyMgr->SetIsHits(mEneIsHits);
		mItemMgr->SetIsHitMaps(mIteIsHitMaps);

		// スコアを更新する
		UpdateScore();

		// 各オブジェクトの描画順を更新する
		UpdateDOrder();

		// 新しいEnemyとItemを出現させる（かどうかを決める）
		if (mFrameCnt >= 300 &&	// 最初の300カウントはゲームをしている人に余裕を持たせるために何も出現させない
			mFrameCnt < BOSS_START_FRAME_NUM) {	// BossStageの移行を始めようとしていなかったら
			// EnemyとItemの出現は同フレームの処理を軽くするために違うフレームで出現処理をさせる
			if (mFrameCnt % ITE_CREATION_FRAME_NUM == 0) {
				mItemMgr->CreateItem();
			}
			
			if ((mFrameCnt + ITE_CREATION_FRAME_NUM / 2) % ENE_CREATION_FRAME_NUM == 0) {
				mEnemyMgr->CreateEnemy();
			}
		}

		// BossStageへの移行を始めるかどうかを決める
		if (!mIsAtBsSt) {	// BossStageに入っていないとき
			if (!mIsChangingSt) {	// BossStageへの移行を始めていないとき
				if (mFrameCnt >= BOSS_START_FRAME_NUM) {	// BossStageの移行を始めたい時間を超えているとき
					bool eneIteIsExisting = false;
					for (int i = 0; i < ENEMY_NUM; i++) {
						if (mEneIsExistings[i]) eneIteIsExisting = true;
					}
					for (int i = 0; i < ITEM_NUM; i++) {
						if (mIteIsExistings[i]) eneIteIsExisting = true;
					}

					if (!eneIteIsExisting) {	// EnemyとItemが存在しない状態になったら
						// BossStageへの移行を始める
						mIsChangingSt = true;
						mGameBack->StartChangingSt();
						mPlayerMgr->SetIsChangingSt(mIsChangingSt);
						mEnemyMgr->CreateEnemyBoss(mGameBack->GetBsStX());
					}
				}
			}
			else {	// BossStageへの移行中のとき
				// BossStageへの移行が完了したかどうかを確認する
				mIsAtBsSt = mGameBack->GetIsAtBsSt();

				if (mIsAtBsSt) {	// 移行が完了していたら
					mIsChangingSt = false;
					mPlayerMgr->SetIsChangingSt(mIsChangingSt);
					mPlayerMgr->SetIsAtBsSt(mIsAtBsSt);
				}
			}
		}

		// 更新
		mGameBack->Update();
		mPlayerMgr->Update();
		mEnemyMgr->Update();
		mItemMgr->Update();
		mPlHpGauge->Update();
		mTimeCounter->Update();
		mScoreCounter->Update();

		// 音源がループするようにする
		if (CheckSoundMem(mSoundHandle) == 0) {	// 音源が最後まで終わっていたら
			// 再度最初から流す
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}

		if (mPlIsDead || mHasClearedGame) {	// 次のフレームでGameOver画面かGameClear画面に移行するとき
			// 音源を止める
			StopSoundMem(mSoundHandle);

			if (mHasClearedGame) {	// 次のフレームでGameClear画面に移行するとき
				// クリア画面で表示するスコアを渡す
				mGameClear->SetScores(mScoreCounter->GetTotalScore(), 50 * (999 - mTimeCounter->GetClearTime()));
			}
		}
	}

	mFrameCnt++;
}

void GameScene::Draw() {
	if (mHasClearedGame) {	// ゲームクリアして（EnemyBossを倒して）いたら
		mGameClear->Draw();
	}
	else if (mPlIsDead) {	// Playerが死んでいたら
		mGameOver->Draw();
	}
	else {	// Playerが死んでいなかったら
		int tmpA = 0;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mIteIsExistings[i]) {
				tmpA += 1;
			}
		}

		// 背景の描画
		mGameBack->Draw();
		//DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", mPlIntDataMap["hp"], mPlIntDataMap["x"], tmpA, mFrameCnt);	// デバッグ用

		for (const auto& dOrder : mDOrderVec) {
			int objId = dOrder.second.first;
			int idx = dOrder.second.second;

			if (objId == 0) {	// Playerの描画
				mPlayerMgr->Draw();
			}
			else if (objId == 1) {	// Enemyの描画
				mEnemyMgr->Draw(idx);
			}
			else {	// Itemの描画
				mItemMgr->Draw(idx);
			}
		}

		// Playerのhpゲージの描画
		mPlHpGauge->Draw();

		// 経過時間の表示
		mTimeCounter->Draw();

		// 合計スコアの表示
		mScoreCounter->Draw();
	}
}

void GameScene::UpdateDOrder() {
	using namespace std;

	// 順序を入れるvectorを空にする
	mDOrderVec.clear();

	// Playerのy座標情報をセット
	mDOrderVec.push_back({ mPlIntDataMap["y"], {0, 0} });

	// Enemyのy座標情報をセット
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {
			mDOrderVec.push_back({ (int)mEneIntDataMaps.at(i)["y"], {1, i} });
		}
	}

	// Itemのy座標情報をセット
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {
			mDOrderVec.push_back({ (int)mIteIntDataMaps.at(i)["y"], {2, i} });
		}
	}

	// y座標の昇順に並び替え
	sort(mDOrderVec.begin(), mDOrderVec.end());
}


void GameScene::UpdateHit() {
	// Playerの身体の当たり判定範囲
	int plLX = mPlIntDataMap["x"] - mPlIntDataMap["hitRangeW"];
	int plRX = mPlIntDataMap["x"] + mPlIntDataMap["hitRangeW"];
	int plTY = mPlIntDataMap["y"] - mPlIntDataMap["hitRangeH"];
	int plBY = mPlIntDataMap["y"] + mPlIntDataMap["hitRangeH"];
	int plPs[] = { plLX, plRX, plTY, plBY };

	// Player-Enemy間の当たり判定
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {	// Enemyが存在していたら
			// Enemyの身体の当たり判定範囲
			int eneLX = mEneIntDataMaps.at(i)["x"] - mEneIntDataMaps.at(i)["hitRangeW"];
			int eneRX = mEneIntDataMaps.at(i)["x"] + mEneIntDataMaps.at(i)["hitRangeW"];
			int eneTY = mEneIntDataMaps.at(i)["y"] - mEneIntDataMaps.at(i)["hitRangeH"];
			int eneBY = mEneIntDataMaps.at(i)["y"] + mEneIntDataMaps.at(i)["hitRangeH"];
			int enePs[] = { eneLX, eneRX, eneTY, eneBY };

			// 当たり判定チェックをする（Playerに必要，Enemyには不要）
			mPlIsHitMap["enemy"].at(i) = IsHit(plPs, enePs);

			// PlayerAttack-Enemy間の当たり判定
			if (mPlBoolDataMap["isAttacking"]) {	// Playerが攻撃中だったら
				// Playerの攻撃の当たり判定範囲
				int plALX = mPlIntDataMap["ax"] - mPlIntDataMap["hitRangeAW"];
				int plARX = mPlIntDataMap["ax"] + mPlIntDataMap["hitRangeAW"];
				int plATY = mPlIntDataMap["ay"] - mPlIntDataMap["hitRangeAH"];
				int plABY = mPlIntDataMap["ay"] + mPlIntDataMap["hitRangeAH"];
				int plAPs[] = { plALX, plARX, plATY, plABY };

				// Enemyに攻撃が当たったかどうか確認する
				mPlIsHitMap["plAToEnemy"].at(i) = IsHit(plAPs, enePs);
			}
			else {	// Playerが攻撃中でなければ
				mPlIsHitMap["plAToEnemy"].at(i) = false;
			}

			// Player-EnemyAttack間の当たり判定
			if (mEneBoolDataMaps.at(i)["isAttacking"]) {	// Enemyが攻撃中だったら
				mPlIsHitMap["enemyAttack"].at(i) = false;
				
				int eneANum = mEneIntDataMaps.at(i)["attackNum"];
				for (int j = 0; j < eneANum; j++) {	// 各Enemyの攻撃数の分だけ
					int eneALX = mEneAXYMapVecs.at(i).at(j)["ax"] - mEneAXYMapVecs.at(i).at(j)["hitRangeAW"];
					int eneARX = mEneAXYMapVecs.at(i).at(j)["ax"] + mEneAXYMapVecs.at(i).at(j)["hitRangeAW"];
					int eneATY = mEneAXYMapVecs.at(i).at(j)["ay"] - mEneAXYMapVecs.at(i).at(j)["hitRangeAH"];
					int eneABY = mEneAXYMapVecs.at(i).at(j)["ay"] + mEneAXYMapVecs.at(i).at(j)["hitRangeAH"];
					int eneAPs[] = { eneALX, eneARX, eneATY, eneABY };

					// Enemyの攻撃が当たったかどうか確認する（Playerに必要，Enemyには不要）
					if (IsHit(plPs, eneAPs)) {	// Enemyの攻撃が当たっていたら
						mPlIsHitMap["enemyAttack"].at(i) = true;
					}
				}
			}
			else {	// Enemyが攻撃中でなければ
				mPlIsHitMap["enemyAttack"].at(i) = false;
			}
			
		}
		else {	// Enemyが存在していなかったら
			mPlIsHitMap["enemy"].at(i) = false;
			mPlIsHitMap["plAToEnemy"].at(i) = false;
			mPlIsHitMap["enemyAttack"].at(i) = false;
		}

		// Enemy側の判定にも同じ結果を入れる
		mEneIsHits[i] = mPlIsHitMap["plAToEnemy"].at(i);
	}


	// Player-Item間の当たり判定更新
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {	// Itemが存在していたら
			// Itemの当たり判定範囲
			int iteLX = mIteIntDataMaps.at(i)["x"] - mIteIntDataMaps.at(i)["hitRangeW"];
			int iteRX = mIteIntDataMaps.at(i)["x"] + mIteIntDataMaps.at(i)["hitRangeW"];
			int iteTY = mIteIntDataMaps.at(i)["y"] - mIteIntDataMaps.at(i)["hitRangeH"];
			int iteBY = mIteIntDataMaps.at(i)["y"] + mIteIntDataMaps.at(i)["hitRangeH"];
			int itePs[] = { iteLX, iteRX, iteTY, iteBY };

			// 当たり判定チェックをする
			mPlIsHitMap["item"].at(i) = IsHit(plPs, itePs);
			
			// PlayerAttack-Item間の当たり判定
			if (mPlBoolDataMap["isAttacking"] && mIteIntDataMaps.at(i)["itemId"] >= 12) {	// Playerが攻撃中で箱系アイテムだったら
				// Playerの攻撃の当たり判定範囲
				int plALX = mPlIntDataMap["ax"] - mPlIntDataMap["hitRangeAW"];
				int plARX = mPlIntDataMap["ax"] + mPlIntDataMap["hitRangeAW"];
				int plATY = mPlIntDataMap["ay"] - mPlIntDataMap["hitRangeAH"];
				int plABY = mPlIntDataMap["ay"] + mPlIntDataMap["hitRangeAH"];
				int plAPs[] = { plALX, plARX, plATY, plABY };

				// Itemに攻撃が当たったかどうか確認する（箱などのItemに必要，Playerには不要）
				mPlIsHitMap["plAToItem"].at(i) = IsHit(plAPs, itePs);
			}
			else {	// Playerが攻撃中でなければ
				mPlIsHitMap["plAToItem"].at(i) = false;
			}
		}
		else {	// Itemが存在していなかったら
			mPlIsHitMap["item"].at(i) = false;
			mPlIsHitMap["plAToItem"].at(i) = false;
		}

		// Item側の判定にも同じ結果を入れる
		mIteIsHitMaps.at(i)["player"] = mPlIsHitMap["item"].at(i);
		mIteIsHitMaps.at(i)["playerAttack"] = mPlIsHitMap["plAToItem"].at(i);
	}
}


bool GameScene::IsHit(const int (&ps1)[4], const int(&ps2)[4]) {
	bool isHit;	// 返す値

	// 当たり判定チェックをする
	if (ps1[0] < ps2[1] && ps1[2] < ps2[3] && ps1[1] > ps2[0] && ps1[3] > ps2[2]) {
		isHit = true;
	}
	else {
		isHit = false;
	}

	return isHit;
}


void GameScene::UpdateScore() {
	// Enemy
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {
			if (mEneBoolDataMaps.at(i)["isDead"]) {	// EnemyがPlayerに倒され，消えるとき
				// 取得（破壊）下アイテムのスコアを追加する
				mScoreCounter->AddScore(mEneIntDataMaps.at(i)["score"]);
			}
		}
	}

	// Item
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {
			if (mIteBoolDataMaps.at(i)["isDead"]) {	// ItemがPlayerに取得（破壊）され，消えるとき
				// 取得（破壊）下アイテムのスコアを追加する
				mScoreCounter->AddScore(mIteIntDataMaps.at(i)["score"]);
			}
		}
	}
}