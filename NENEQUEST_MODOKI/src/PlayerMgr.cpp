#include "PlayerMgr.h"
#include "DxLib.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "GameScene.h"
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
	//PlInitialize::SetPlayer(290, 500, 10, -1, -1, 0, 0, false); //Player�̏�����Ԃ̐ݒ�
}


PlayerMgr* PlayerMgr::GetInstance() {
	if (!PlayerMgr::mPlayerMgr) {
		PlayerMgr::mPlayerMgr = new PlayerMgr();
		PlayerMgr::mPlayerMgr->Initialize();
	}

	return PlayerMgr::mPlayerMgr;
}


void PlayerMgr::Initialize() {
	// �����l�Ŏg�p����
	std::map<std::string, int> plIntDataMap;
	std::map<std::string, bool> plBoolDataMap;
	plIntDataMap["x"] = 290;
	plIntDataMap["y"] = 500;
	plIntDataMap["hp"] = 5;
	plIntDataMap["effectFrameCnt"] = 0;
	plIntDataMap["bsStopFrameCnt"] = 0;
	plIntDataMap["effectId"] = 0;
	plBoolDataMap["isDead"] = false;

	// �ŏ��Ɏg�p����Player�̏�����
	mPlayer = (Player*)Player1::GetInstance();
	mPlayer->SetPlParams(&plIntDataMap, &plBoolDataMap);
	mPlayer->Initialize();

	// �������̂��߂�GameScene�N���X�̃C���X�^���X���擾
	mGameScene = GameScene::GetInstance();

	// ����ێ����邽�߂�map(vector)�̏�����
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.push_back({});
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		mPlIsHitMap["item"].push_back(false);
	}
}


void PlayerMgr::Finalize() {
	mPlayer->Finalize();

	delete mPlayerMgr;
	mPlayerMgr = NULL;
}


void PlayerMgr::Update() {
	if (mPlayerNext != ePlayerNone) {
		// �f�[�^�̈��p���Ɏg�p����f�[�^�̎擾
		std::map<std::string, int> plIntDataMap;
		std::map<std::string, bool> plBoolDataMap;
		mPlayer->GetPlDataMap(&plIntDataMap, &plBoolDataMap);

		// �I������
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
			case ePlayer4:
				mPlayer = (Player*) Player4::GetInstance();
				break;
		}
		mPlayerNext = ePlayerNone;

		// �f�[�^�̈��p��
		mPlayer->SetPlParams(&plIntDataMap, &plBoolDataMap);
		mPlayer->Initialize();
	}

	// �����蔻�����Item��Enemy�̏���n�����̂��ɍX�V
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
//	// �����蔻��m�F�Ɏg�p����f�[�^�̎擾
//	mPlayer->GetPlDataMap(plIntDataMap, plBoolDataMap);
//}


void PlayerMgr::GetPlDataMaps(std::map<std::string, int>* plIntDataMap, std::map<std::string, bool>* plBoolDataMap) {
	mPlayer->GetPlDataMap(plIntDataMap, plBoolDataMap);
}


void PlayerMgr::GetPlIntDataMap(std::map<std::string, int>* plIntDataMap) {
	mPlayer->GetPlIntDataMap(plIntDataMap);
}


void PlayerMgr::SetIsHitMap(std::map<std::string, std::vector<bool>>* isHitMap) {
	// �eItem�Ƃ̓����蔻����Z�b�g
	for (int i = 0; i < ITEM_NUM; i++) {
		mPlIsHitMap["item"].at(i) = (*isHitMap)["item"].at(i);
	}
}


void PlayerMgr::SetIteDataMaps(std::vector<std::map<std::string, float>>& iteDataMaps) {
	// �eItem�̌��ʂ̏����Z�b�g
	for (int i = 0; i < ITEM_NUM; i++) {
		mIteDataMaps.at(i)["healPower"] = iteDataMaps.at(i)["healPower"];
		mIteDataMaps.at(i)["speedPower"] = iteDataMaps.at(i)["speedPower"];
		mIteDataMaps.at(i)["attackPower"] = iteDataMaps.at(i)["attackPower"];
		mIteDataMaps.at(i)["itemId"] = iteDataMaps.at(i)["itemId"];
	}
}
