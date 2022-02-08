#include "DxLib.h"
#include "GameScene.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"
#include "SceneMgr.h"
#include "PlayerMgr.h"
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
	mImageHandle = 0;//LoadGraph("images/clouds1.png");
	/*for (int i = 0; i < 5; i++) {
		dnCheck[i] = false;
	}*/

	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.push_back({});
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mPlIsHitMap["item"].push_back(false);
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mIteIsHitMaps.push_back({});
	}


	//mCharaGraphics = new CharaGraphics();
	mGameBack = new GameBack();
	mPlayerMgr = PlayerMgr::GetInstance();
	//enemyMgr = new EnemyMgr(eneAppear);
	mItemMgr = ItemMgr::GetInstance();

	/*appear = new Appearance();
	appear->GetEnemyAppear(eneAppear);
	appear->GetItemAppear(itAppear);
	enemyMgr = new EnemyMgr(eneAppear);*/
	
	//iNum = appear->GetItNum();

	//hpGauge = new HpGauge();

	CharaGraphics::Initialize();
	ItemGraphics::Initialize();
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	//enemyMgr->Initialize();
	mItemMgr->Initialize();
	//hpGauge->Initialize();

	/*m_plDeadFlag = false;
	m_bsDeadFlag = false;*/

	mSoundHandle = LoadSoundMem("sounds/NENEQUEST.ogg");
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
}

void GameScene::Finalize() {
	DeleteGraph(mImageHandle);
	CharaGraphics::Finalize();
	ItemGraphics::Initialize();
	mGameBack->Finalize();
	mPlayerMgr->Finalize();
	/*enemyMgr->Finalize();
	itemMgr->Finalize();
	hpGauge->Finalize();*/
	//delete mCharaGraphics;
	//delete mGameBack;
	//delete mPlayerMgr;
	//delete enemyMgr;
	//delete mItemMgr;
	//delete hpGauge;
	//delete appear;
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
	mPlayerMgr->GetPlDataMaps(&mPlIntDataMap, &mPlBoolDataMap);
	mItemMgr->GetIteDataMaps(&mIteDataMaps, mIteIsExistings);

	// Player, Enemy, Item間で使用する情報をお互いに渡す
	mPlayerMgr->SetIteDataMaps(mIteDataMaps);

	// 各オブジェクトの当たり判定を確認
	UpdateHit();


	// 当たり判定の確認結果のデータを各オブジェクトに渡す
	mPlayerMgr->SetIsHitMap(&mPlIsHitMap);
	mItemMgr->SetIsHitMaps(mIteIsHitMaps);

	// 更新
	mGameBack->Update();
	mPlayerMgr->Update();
	mItemMgr->Update();

	

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

	SetDrawingOrder();


	mGameBack->Draw();
	DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %f, %f, %f", mPlIntDataMap["hp"], mIteDataMaps.at(0)["healPower"], mIteDataMaps.at(1)["x"], 0);

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

	mPlayerMgr->Draw();
	mItemMgr->Draw();

	//DrawFormatString(400, 500, GetColor(255, 255, 255), "eneapp = %d", iNum);
}

void GameScene::SetDrawingOrder() {
	using namespace std;

	vector<pair<int, pair<int, int>>> charaYVec(3);	// firstにy座標，secondにキャラの種類とインデックス番号を入れたpairのvector

	//charaYVec[0] = { mPlIntDataMap["y"] - 73, {0, 0} };
	//charaY[1] = CharaY::GetEnemy0Y();
	//charaY[2] = CharaY::GetEnemy1Y();
	/*charaY[3] = CharaY::GetEnemy2Y();
	charaY[4] = CharaY::GetItem0Y();
	charaY[5] = CharaY::GetItem1Y();*/

	sort(charaYVec.begin(), charaYVec.end());

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
	// Player-Item間の当たり判定更新
	for (int i = 0; i < 2; i++) {
		if (mIteIsExistings[i]) {	// Itemが存在していたら
			// Playerの身体の当たり判定範囲
			int plLX = mPlIntDataMap["x"] - mPlIntDataMap["hitRangeW"];
			int plRX = mPlIntDataMap["x"] + mPlIntDataMap["hitRangeW"];
			int plTY = mPlIntDataMap["y"] - mPlIntDataMap["hitRangeH"];
			int plBY = mPlIntDataMap["y"] + mPlIntDataMap["hitRangeH"];
			int plPs[] = { plLX, plRX, plTY, plBY };

			// Itemの当たり判定範囲
			int iteLX = mIteDataMaps.at(i)["x"] - mIteDataMaps.at(i)["hitRangeW"];
			int iteRX = mIteDataMaps.at(i)["x"] + mIteDataMaps.at(i)["hitRangeW"];
			int iteTY = mIteDataMaps.at(i)["y"] - mIteDataMaps.at(i)["hitRangeH"];
			int iteBY = mIteDataMaps.at(i)["y"] + mIteDataMaps.at(i)["hitRangeH"];
			int itePs[] = { iteLX, iteRX, iteTY, iteBY };

			// 当たり判定チェックをする
			mPlIsHitMap["item"].at(i) = IsHit(plPs, itePs);
			

			if (mPlBoolDataMap["isAttacking"]) {	// Playerが攻撃中だったら
				// Playerの攻撃の当たり判定範囲
				int plALX = mPlIntDataMap["ax"] - mPlIntDataMap["hitRangeAW"];
				int plARX = mPlIntDataMap["ax"] + mPlIntDataMap["hitRangeAW"];
				int plATY = mPlIntDataMap["ay"] - mPlIntDataMap["hitRangeAH"];
				int plABY = mPlIntDataMap["ay"] + mPlIntDataMap["hitRangeAH"];
				int plAPs[] = { plALX, plARX, plATY, plABY };

				// Itemに攻撃が当たったかどうか確認する（箱などのItemに必要，Playerには不要）
				mIteIsHitMaps.at(i)["playerAttack"] = IsHit(plAPs, itePs);
			}
			else {	// Playerが攻撃中でなければ
				mIteIsHitMaps.at(i)["playerAttack"] = false;
			}
		}
		else {	// Itemが存在していなかったら
			mPlIsHitMap["item"].at(i) = false;
		}

		// Item側の判定にも同じ結果を入れる
		mIteIsHitMaps.at(i)["player"] = mPlIsHitMap["item"].at(i);
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