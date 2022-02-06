#include "DxLib.h"
#include "GameScene.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"
//#include "CharaY.h"
#include <mutex>
#include <vector>
#include <algorithm>


GameScene::GameScene(SceneChanger* changer) : BaseScene(changer) {
}

void GameScene::Initialize() {
	mImageHandle = 0;//LoadGraph("images/clouds1.png");
	/*for (int i = 0; i < 5; i++) {
		dnCheck[i] = false;
	}*/

	//mCharaGraphics = new CharaGraphics();
	mGameBack = new GameBack();
	mPlayerMgr = PlayerMgr::GetInstance();

	/*appear = new Appearance();
	appear->GetEnemyAppear(eneAppear);
	appear->GetItemAppear(itAppear);
	enemyMgr = new EnemyMgr(eneAppear);
	itemMgr = new ItemMgr(itAppear);
	iNum = appear->GetItNum();*/

	//hpGauge = new HpGauge();

	CharaGraphics::Initialize();
	ItemGraphics::Initialize();
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	/*enemyMgr->Initialize();
	itemMgr->Initialize();
	hpGauge->Initialize();*/

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
	delete mGameBack;
	//delete mPlayerMgr;
	/*delete enemyMgr;
	delete itemMgr;
	delete hpGauge;
	delete appear;*/
	StopSoundMem(mSoundHandle);
	DeleteSoundMem(mSoundHandle);
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
	mPlayerMgr->GetPlIntDataMap(&mPlIntDataMap);

	// 各オブジェクトの当たり判定を確認


	// 当たり判定の確認結果のデータを各オブジェクトに渡す


	// 更新
	mGameBack->Update();
	mPlayerMgr->Update();

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
	DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", yJudge[1], yJudge[2], yJudge[3], yJudge[4]);

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

	//DrawFormatString(400, 500, GetColor(255, 255, 255), "eneapp = %d", iNum);
}

void GameScene::SetDrawingOrder() {
	using namespace std;

	vector<pair<int, pair<int, int>>> charaYVec;	// firstにy座標，secondにキャラの種類とキャラ番号を入れたpairのvector

	charaY[0] = mPlIntDataMap["y"] - 73;
	/*charaY[1] = CharaY::GetEnemy0Y();
	charaY[2] = CharaY::GetEnemy1Y();
	charaY[3] = CharaY::GetEnemy2Y();
	charaY[4] = CharaY::GetItem0Y() - 100;
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