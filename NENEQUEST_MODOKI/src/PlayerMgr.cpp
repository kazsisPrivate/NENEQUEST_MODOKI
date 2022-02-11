#include "PlayerMgr.h"
#include "DxLib.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
//#include "GameScene.h"
#include "Player.h"
#include <string>
#include <map>


PlayerMgr* PlayerMgr::mPlayerMgr;


PlayerMgr::PlayerMgr() : mPlayerNext(ePlayerNone) {
	//PlInitialize::SetPlayer(290, 500, 10, -1, -1, 0, 0, false); //Playerの初期状態の設定
}


PlayerMgr* PlayerMgr::GetInstance() {
	if (!PlayerMgr::mPlayerMgr) {
		PlayerMgr::mPlayerMgr = new PlayerMgr();
		PlayerMgr::mPlayerMgr->Initialize();
	}

	return PlayerMgr::mPlayerMgr;
}


void PlayerMgr::Initialize() {
	// 初期値で使用する
	std::map<std::string, int> plIntDataMap;
	std::map<std::string, bool> plBoolDataMap;
	plIntDataMap["x"] = 290;
	plIntDataMap["y"] = 500;
	plIntDataMap["hp"] = 5;
	plIntDataMap["effectFrameCnt"] = 0;
	plIntDataMap["bsStopFrameCnt"] = 0;
	plIntDataMap["effectId"] = 0;
	plIntDataMap["godFrameCnt"] = 0;
	plBoolDataMap["isDead"] = false;
	plBoolDataMap["isGod"] = false;

	// 最初に使用するPlayerの初期化
	mPlayer = (Player*)Player1::GetInstance();
	mPlayer->SetPlParams(&plIntDataMap, &plBoolDataMap);
	mPlayer->Initialize();

	// 情報やり取りのためにGameSceneクラスのインスタンスを取得
	//mGameScene = GameScene::GetInstance();

	// 情報を保持するためのmap(vector), 配列の初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneAPs[i] = 0;
		mPlIsHitMap["enemy"].push_back(false);
		mPlIsHitMap["enemyAttack"].push_back(false);
		mPlIsHitMap["plAToEnemy"].push_back(false);
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.push_back({});
		mPlIsHitMap["item"].push_back(false);
		mPlIsHitMap["plAToItem"].push_back(false);
	}
}


void PlayerMgr::Finalize() {
	mPlayer->Finalize();

	delete mPlayerMgr;
	mPlayerMgr = NULL;
}


void PlayerMgr::Update() {
	if (mPlayerNext != ePlayerNone) {
		// データの引継ぎに使用するデータの取得
		std::map<std::string, int> plIntDataMap;
		std::map<std::string, bool> plBoolDataMap;
		mPlayer->GetPlDataMap(&plIntDataMap, &plBoolDataMap);

		// 終了処理
		mPlayer->Finalize();

		switch (mPlayerNext) {
			case ePlayer1:
				mPlayer = (Player*) Player1::GetInstance();
				break;
			case ePlayer2:
				mPlayer = (Player*) Player2::GetInstance();
				break;
			case ePlayer3:
				mPlayer = (Player*) Player3::GetInstance();
				break;
			default:	// case ePlayer4
				mPlayer = (Player*) Player4::GetInstance();
				break;
		}
		mPlayerNext = ePlayerNone;

		// データの引継ぎ
		mPlayer->SetPlParams(&plIntDataMap, &plBoolDataMap);
		mPlayer->Initialize();
	}

	// 当たり判定情報やItemやEnemyの情報を渡したのちに更新
	mPlayer->SetEneAPowers(mEneAPs);
	mPlayer->SetIteParams(mIteDataMaps);
	mPlayer->SetIsHits(&mPlIsHitMap);

	mPlayer->Update();
}


void PlayerMgr::Draw() {
	mPlayer->Draw();
}


void PlayerMgr::ChangePlayer(EPlayer playerNext) {
	mPlayerNext = playerNext;
}


//bool PlayerMgr::GetDead() {
//	return PlayerData::GetDeadFlag();
//}


//void PlayerMgr::GetPlDataMap(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
//	// 当たり判定確認に使用するデータの取得
//	mPlayer->GetPlDataMap(plIntDataMap, plBoolDataMap);
//}


void PlayerMgr::GetPlData(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	mPlayer->GetPlDataMap(plIntDataMap, plBoolDataMap);
}


void PlayerMgr::GetPlIntDataMap(std::map<std::string, int>* plIntDataMap) {
	mPlayer->GetPlIntDataMap(plIntDataMap);
}


void PlayerMgr::SetIsHitMap(std::map<std::string, std::vector<bool>>* isHitMap) {
	// 各Enemyの身体と攻撃との当たり判定をセット
	for (int i = 0; i < ENEMY_NUM; i++) {
		mPlIsHitMap["enemy"].at(i) = (*isHitMap)["enemy"].at(i);
		mPlIsHitMap["enemyAttack"].at(i) = (*isHitMap)["enemyAttack"].at(i);
		mPlIsHitMap["plAToEnemy"].at(i) = (*isHitMap)["plAToEnemy"].at(i);
	}

	// 各Itemとの当たり判定をセット
	for (int i = 0; i < ITEM_NUM; i++) {
		mPlIsHitMap["item"].at(i) = (*isHitMap)["item"].at(i);
		mPlIsHitMap["plAToItem"].at(i) = (*isHitMap)["plAToItem"].at(i);
	}
}


void PlayerMgr::SetEneAPowers(const int* const eneAPs) {
	// 各Enemyの攻撃力のセット
	for (int i = 0; i < ENEMY_NUM; i++) {
		mEneAPs[i] = eneAPs[i];
	}
}


void PlayerMgr::SetIteDataMaps(std::vector<std::map<std::string, float>>& iteDataMaps) {
	// 各Itemの効果の情報をセット
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.at(i)["healPower"] = iteDataMaps.at(i)["healPower"];
		mIteDataMaps.at(i)["speedPower"] = iteDataMaps.at(i)["speedPower"];
		mIteDataMaps.at(i)["attackPower"] = iteDataMaps.at(i)["attackPower"];
		mIteDataMaps.at(i)["itemId"] = iteDataMaps.at(i)["itemId"];
	}
}
