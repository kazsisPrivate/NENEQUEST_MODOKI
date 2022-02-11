#include "DxLib.h"
#include "GameScene.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"
#include "EffectGraphics.h"
#include "SceneMgr.h"
//#include "PlayerMgr.h"
////#include "EnemyMgr.h"
//#include "ItemMgr.h"
#include <mutex>
#include <vector>
#include <algorithm>


GameScene* GameScene::mGameScene;
int GameScene::tmpNum = 0;


GameScene::GameScene(SceneChanger* changer) : BaseScene(changer) {
}


GameScene* GameScene::GetInstance() {
	if (!GameScene::mGameScene) {
		SceneMgr* sceneMgr = SceneMgr::GetInstance();
		GameScene::mGameScene = new GameScene(sceneMgr);
		GameScene::mGameScene->Initialize();
		GameScene::tmpNum++;
	}

	if (GameScene::tmpNum == 2) {
		GameScene::tmpNum = 100;
	}

	return GameScene::mGameScene;
}


void GameScene::Initialize() {
	mImageHandle = NULL;//LoadGraph("images/clouds1.png");
	/*for (int i = 0; i < 5; i++) {
		dnCheck[i] = false;
	}*/

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
		mIteDataMaps.push_back({});
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

	/*appear = new Appearance();
	appear->GetEnemyAppear(eneAppear);
	appear->GetItemAppear(itAppear);
	enemyMgr = new EnemyMgr(eneAppear);*/
	
	//iNum = appear->GetItNum();

	
	// 画面の各構成要素の初期化
	CharaGraphics::Initialize();
	ItemGraphics::Initialize();
	EffectGraphics::Initialize();
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	mEnemyMgr->Initialize();
	mItemMgr->Initialize();
	mPlHpGauge->Initialize();

	/*m_plDeadFlag = false;
	m_bsDeadFlag = false;*/

	mSoundHandle = LoadSoundMem("sounds/NENEQUEST.ogg");
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
}

void GameScene::Finalize() {
	// 画面の各構成要素の終了処理
	CharaGraphics::Finalize();
	ItemGraphics::Finalize();
	EffectGraphics::Finalize();
	mGameBack->Finalize();
	mPlayerMgr->Finalize();
	mEnemyMgr->Finalize();
	mItemMgr->Finalize();
	mPlHpGauge->Finalize();
	//delete mCharaGraphics;
	//delete mGameBack;
	//delete mPlayerMgr;
	//delete enemyMgr;
	//delete mItemMgr;
	//delete hpGauge;
	//delete appear;

	// ゲームの音楽の削除
	StopSoundMem(mSoundHandle);
	DeleteSoundMem(mSoundHandle);

	delete mGameScene;
	mGameScene = NULL;
}

void GameScene::Update() {
	//if (m_plDeadFlag) {
	//	gameOver.Update();

	//	if (gameOver.IsChangeScene()) {
	//		mSceneChanger->ChangeScene(eSceneMenu);
	//	}
	//}
	//else if (m_bsDeadFlag) {
	//	//ここでGameClear関連の処理をする
	//	gameClear->Update();

	//	if (!gameClear->IsGmClear()) {
	//		mSceneChanger->ChangeScene(eSceneMenu);
	//	}
	//}
	//else {
	//	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
	//		mSceneChanger->ChangeScene(eSceneMenu);
	//	}

	//	mGameBack.Update();
	//	enemyMgr->Update();
	//	itemMgr->Update();
	//	mPlayerMgr->Update();
	//	hpGauge->Update();
	//	gameCtrs.Update();

	//	m_plDeadFlag = mPlayerMgr->GetDead();
	//	m_bsDeadFlag = enemyMgr->GetBossDead();

	//	if (m_bsDeadFlag) {
	//		gameClear = std::make_unique<GameClear>(gameCtrs.GetTime(), gameCtrs.GetScore());
	//	}

	//	if (CheckSoundMem(mSoundHandle) == 0) {
	//		PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
	//	}
	//}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		mSceneChanger->ChangeScene(eSceneMenu);
	}

	// Player, Enemy, Itemの情報を取得
	mPlayerMgr->GetPlData(&mPlIntDataMap, &mPlBoolDataMap);
	mEnemyMgr->GetEneData(&mEneIntDataMaps, &mEneAXYMapVecs, &mEneBoolDataMaps, mEneIsExistings);
	mItemMgr->GetIteData(&mIteDataMaps, mIteIsExistings);

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
	mPlayerMgr->SetIteDataMaps(mIteDataMaps);
	mPlayerMgr->SetEneAPowers(eneAPs);
	mEnemyMgr->SetPlAPower(mPlIntDataMap["attack"]);
	mPlHpGauge->SetPlayerHp(mPlIntDataMap["hp"]);

	// 各オブジェクトの当たり判定を確認
	UpdateHit();

	// 当たり判定の確認結果のデータを各オブジェクトに渡す
	mPlayerMgr->SetIsHitMap(&mPlIsHitMap);
	mEnemyMgr->SetIsHits(mEneIsHits);
	mItemMgr->SetIsHitMaps(mIteIsHitMaps);

	// 各オブジェクトの描画順を更新する
	UpdateDOrder();

	// 更新
	mGameBack->Update();
	mPlayerMgr->Update();
	mEnemyMgr->Update();
	mItemMgr->Update();
	mPlHpGauge->Update();
	

	if (CheckSoundMem(mSoundHandle) == 0) {
		PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
	}
}

void GameScene::Draw() {
	BaseScene::Draw();
	DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));

	//if (m_plDeadFlag) {
	//	gameOver.Draw();
	//}
	//else if (m_bsDeadFlag) {
	//	//gameClear関連
	//	gameClear->Draw();
	//}
	//else {
	//	YJudge();

	//	mGameBack.Draw();
	//	DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", yJudge[1], yJudge[2], yJudge[3], yJudge[4]);

	//	for (int i = 1; i < 7; i++) {
	//		if (drawNum[0] == i) {
	//			mPlayerMgr->Draw();
	//		}
	//		else if (drawNum[1] == i) {
	//			enemyMgr->Draw0();
	//		}
	//		else if (drawNum[2] == i) {
	//			enemyMgr->Draw1();
	//		}
	//		else if (drawNum[3] == i) {
	//			enemyMgr->Draw2();
	//		}
	//		else if (drawNum[4] == i) {
	//			itemMgr->Draw0();
	//		}
	//		else {
	//			itemMgr->Draw1();
	//		}
	//	}

	//	hpGauge->Draw();
	//	gameCtrs.Draw();
	//}

	int tmpA = 0;
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {
			tmpA = 1;
		}
	}
	

	mGameBack->Draw();
	DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", mPlIntDataMap["hp"], mEneIntDataMaps.at(1)["x"], tmpA, mEneIntDataMaps.at(1)["hp"]);

	/*for (int i = 1; i < 7; i++) {
		if (drawNum[0] == i) {
			mPlayerMgr->Draw();
		}
		else if (drawNum[1] == i) {
			enemyMgr->Draw0();
		}
		else if (drawNum[2] == i) {
			enemyMgr->Draw1();
		}
		else if (drawNum[3] == i) {
			enemyMgr->Draw2();
		}
		else if (drawNum[4] == i) {
			itemMgr->Draw0();
		}
		else {
			itemMgr->Draw1();
		}
	}*/

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

	//DrawFormatString(400, 500, GetColor(255, 255, 255), "eneapp = %d", iNum);
}

void GameScene::UpdateDOrder() {
	using namespace std;

	//vector<pair<int, pair<int, int>>> yVec(3);	// firstにy座標，secondに物体の種類とインデックス番号を入れたpairのvector
												// キャラの種類（0: Player, 1: Enemy, 2: Item）

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
			mDOrderVec.push_back({ (int)mIteDataMaps.at(i)["y"], {2, i} });
		}
	}

	// y座標の昇順に並び替え
	sort(mDOrderVec.begin(), mDOrderVec.end());

	/*yVec[0] = { mPlIntDataMap["y"] - 73, {0, 0} };
	yVec[0] = { mIteDataMaps.at(0)["y"], {2, 0} };
	yVec[0] = { mIteDataMaps.at(1)["y"], {2, 1} };*/


	//charaY[1] = CharaY::GetEnemy0Y();
	//charaY[2] = CharaY::GetEnemy1Y();
	/*charaY[3] = CharaY::GetEnemy2Y();
	charaY[4] = CharaY::GetItem0Y();
	charaY[5] = CharaY::GetItem1Y();*/

	
	//for (int i = 0; i < 6; i++) {
	//	yJudge[i] = charaY[i];
	//}

	//Sort(yJudge);

	//for (int i = 0; i < 6; i++) { //y座標の小さいほうから順に描画するようにするために描画する順番を入れ込んでいる
	//	if (yJudge[i] == charaY[0] && dnCheck[0] == false) {
	//		drawNum[0] = i + 1;
	//		dnCheck[0] = true;
	//	}
	//	else if (yJudge[i] == charaY[1] && dnCheck[1] == false) {
	//		drawNum[1] = i + 1;
	//		dnCheck[1] = true;
	//	}
	//	else if (yJudge[i] == charaY[2] && dnCheck[2] == false) {
	//		drawNum[2] = i + 1;
	//		dnCheck[2] = true;
	//	}
	//	else if (yJudge[i] == charaY[3] && dnCheck[3] == false) {
	//		drawNum[3] = i + 1;
	//		dnCheck[3] = true;
	//	}
	//	else if (yJudge[i] == charaY[4] && dnCheck[4] == false) {
	//		drawNum[4] = i + 1;
	//		dnCheck[4] = true;
	//	}
	//	else {
	//		drawNum[5] = i + 1;
	//	}
	//}

	//for (int i = 0; i < 5; i++) {
	//	dnCheck[i] = false;
	//}
}

//void GameScene::Sort(int num[]) {
//	for (int i = 0; i < 5; i++) {
//		for (int j = i + 1; j < 6; j++) {
//			if (num[i] > num[j]) {
//				int cmp = num[j];
//				num[j] = num[i];
//				num[i] = cmp;
//			}
//		}
//	}
//}


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
			int iteLX = mIteDataMaps.at(i)["x"] - mIteDataMaps.at(i)["hitRangeW"];
			int iteRX = mIteDataMaps.at(i)["x"] + mIteDataMaps.at(i)["hitRangeW"];
			int iteTY = mIteDataMaps.at(i)["y"] - mIteDataMaps.at(i)["hitRangeH"];
			int iteBY = mIteDataMaps.at(i)["y"] + mIteDataMaps.at(i)["hitRangeH"];
			int itePs[] = { iteLX, iteRX, iteTY, iteBY };

			// 当たり判定チェックをする
			mPlIsHitMap["item"].at(i) = IsHit(plPs, itePs);
			
			// PlayerAttack-Item間の当たり判定
			if (mPlBoolDataMap["isAttacking"] && mIteDataMaps.at(i)["itemId"] >= 12) {	// Playerが攻撃中で箱系アイテムだったら
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