#include "PlayerMgr.h"
#include "DxLib.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
//#include "HitJudge0.h"
//#include "HitJudge1.h"
//#include "HitJudge2.h"
//#include "PowerBox.h"
//#include "PlayerData.h"
//#include "PlInitialize.h"
#include "Player.h"
#include <string>
#include <map>


PlayerMgr* PlayerMgr::mPlayerMgr;


PlayerMgr::PlayerMgr() : mPlayerNext(ePlayerNone) {
	//PlInitialize::SetPlayer(290, 500, 10, -1, -1, 0, 0, false); //Playerの初期状態の設定
}


PlayerMgr::~PlayerMgr() {
	delete mPlayerMgr;
}


PlayerMgr* PlayerMgr::GetInstance() {
	if (!PlayerMgr::mPlayerMgr) {
		PlayerMgr::mPlayerMgr = new PlayerMgr();
		PlayerMgr::mPlayerMgr->Initialize();
	}

	return PlayerMgr::mPlayerMgr;
}


void PlayerMgr::Initialize() {
	mPlayer = (Player*)Player4::GetInstance();
	mPlayer->SetPlParams(290, 500, 10, 0, 0, 0, 0, 0, false);
	mPlayer->Initialize();

	//mPlayer->Initialize();
}


void PlayerMgr::Finalize() {
	mPlayer->Finalize();
}


void PlayerMgr::Update() {
	if (mPlayerNext != ePlayerNone) {
		mPlayer->Finalize();

		// データの引継ぎに使用するデータの取得
		std::map<std::string, int> plIntDataMap;
		std::map<std::string, bool> plBoolDataMap;
		mPlayer->GetPlDataMap(&plIntDataMap, &plBoolDataMap);

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
			/*case ePlayer4:
				mPlayer = (Player*) new Player_4(this);
				break;*/
		}
		mPlayerNext = ePlayerNone;

		// データの引継ぎ
		mPlayer->SetPlParams(plIntDataMap["x"], plIntDataMap["y"], plIntDataMap["hp"], plIntDataMap["iteSFrameCnt"], plIntDataMap["iteAFrameCnt"],
			plIntDataMap["bsStopFrameCnt"], plIntDataMap["effectId"], plIntDataMap["deadFrameCnt"], plBoolDataMap["isDead"]);
		mPlayer->Initialize();
	}

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


void PlayerMgr::GetPlIntDataMap(std::map<std::string, int>* plIntDataMap) {
	mPlayer->GetPlIntDataMap(plIntDataMap);
}
