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
	//mImageHandle = NULL;//LoadGraph("images/clouds1.png");
	/*for (int i = 0; i < 5; i++) {
		dnCheck[i] = false;
	}*/

	// ����ێ����邽�߂�map(vector)�̏�����
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


	// ��ʂ̊e�\���v�f�̃C���X�^���X�̎擾
	mGameBack = new GameBack();
	mPlayerMgr = PlayerMgr::GetInstance();
	mEnemyMgr = EnemyMgr::GetInstance();
	mItemMgr = ItemMgr::GetInstance();
	mPlHpGauge = new PlayerHpGauge();
	mTimeCounter = new TimeCounter();
	mScoreCounter = new ScoreCounter();
	mGameOver = new GameOver();

	/*appear = new Appearance();
	appear->GetEnemyAppear(eneAppear);
	appear->GetItemAppear(itAppear);
	enemyMgr = new EnemyMgr(eneAppear);*/
	
	//iNum = appear->GetItNum();

	
	// ��ʂ̊e�\���v�f�̏�����
	CharaGraphics::Initialize();
	ItemGraphics::Initialize();
	EffectGraphics::Initialize();
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	mEnemyMgr->Initialize();
	mItemMgr->Initialize();
	mPlHpGauge->Initialize();
	mTimeCounter->Initialize();
	mScoreCounter->Initialize();
	mGameOver->Initialize();

	/*m_plDeadFlag = false;
	m_bsDeadFlag = false;*/

	// �����̏�����
	mSoundHandle = LoadSoundMem("sounds/NENEQUEST.ogg");
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);

	// �t���[�����̃J�E���g�̏�����
	mFrameCnt = 0;

	// Player�͎���ł��Ȃ���ԂƂ��Đݒ�
	mPlIsDead = false;

	// Timer���J�n����
	mTimeCounter->StartTime();
}

void GameScene::Finalize() {
	// ��ʂ̊e�\���v�f�̏I������
	CharaGraphics::Finalize();
	ItemGraphics::Finalize();
	EffectGraphics::Finalize();
	mGameBack->Finalize();
	mPlayerMgr->Finalize();
	mEnemyMgr->Finalize();
	mItemMgr->Finalize();
	mPlHpGauge->Finalize();
	mTimeCounter->Finalize();
	mScoreCounter->Finalize();
	mGameOver->Finalize();
	//delete mCharaGraphics;
	//delete mGameBack;
	//delete mPlayerMgr;
	//delete enemyMgr;
	//delete mItemMgr;
	//delete hpGauge;
	//delete appear;

	// �Q�[���̉��y�̍폜
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
	//	//������GameClear�֘A�̏���������
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

	if (mPlIsDead) {	// Player������ł�����
		// GameOver��ʂ̍X�V
		mGameOver->Update();
	}
	else {	// Player������ł��Ȃ�������
		// Player, Enemy, Item�̏����擾
		mPlayerMgr->GetPlData(&mPlIntDataMap, &mPlBoolDataMap);
		mEnemyMgr->GetEneData(&mEneIntDataMaps, &mEneAXYMapVecs, &mEneBoolDataMaps, mEneIsExistings);
		mItemMgr->GetIteData(&mIteIntDataMaps, &mIteBoolDataMaps, mIteIsExistings);

		// Player�ɓn��Enemy�̍U���͂���̔z��ɂ܂Ƃ߂�
		int eneAPs[3];	// ENEMY_NUM = 3
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mEneIsExistings) {
				eneAPs[i] = mEneIntDataMaps.at(i)["attack"];
			}
			else {
				eneAPs[i] = 0;
			}
		}

		// Player, Enemy, Item�ԂŎg�p����������݂��ɓn��
		mPlayerMgr->SetIteDataMaps(mIteIntDataMaps);
		mPlayerMgr->SetEneAPowers(eneAPs);
		mEnemyMgr->SetPlDataMap(&mPlIntDataMap);
		mPlHpGauge->SetPlayerHp(mPlIntDataMap["hp"]);

		// Player������ł��邩�ǂ���������
		mPlIsDead = mPlBoolDataMap["isDead"];

		// �e�I�u�W�F�N�g�̓����蔻����m�F
		UpdateHit();

		// �����蔻��̊m�F���ʂ̃f�[�^���e�I�u�W�F�N�g�ɓn��
		mPlayerMgr->SetIsHitMap(&mPlIsHitMap);
		mEnemyMgr->SetIsHits(mEneIsHits);
		mItemMgr->SetIsHitMaps(mIteIsHitMaps);

		// �X�R�A���X�V����
		UpdateScore();

		// �e�I�u�W�F�N�g�̕`�揇���X�V����
		UpdateDOrder();

		// �V����Enemy��Item���o��������i���ǂ��������߂�j
		if (mFrameCnt >= 300) {	// �ŏ���300�J�E���g�̓Q�[�������Ă���l�ɗ]�T���������邽�߂ɉ����o�������Ȃ�
			// Enemy��Item�̏o���͓��t���[���̏������y�����邽�߂ɈႤ�t���[���ŏo��������������
			if (mFrameCnt % CREATION_FRAME_NUM == 0) {
				mItemMgr->CreateItem();
			}
			else if ((mFrameCnt + CREATION_FRAME_NUM / 2) % CREATION_FRAME_NUM == 0) {
				mEnemyMgr->CreateEnemy();
			}
		}

		// �X�V
		mGameBack->Update();
		mPlayerMgr->Update();
		mEnemyMgr->Update();
		mItemMgr->Update();
		mPlHpGauge->Update();
		mTimeCounter->Update();
		mScoreCounter->Update();

		// ���������[�v����悤�ɂ���
		if (CheckSoundMem(mSoundHandle) == 0) {	// �������Ō�܂ŏI����Ă�����
			// �ēx�ŏ����痬��
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}

		if (mPlIsDead) {	// ���̃t���[����GameOver��ʂɈڍs����Ƃ�
			// �������~�߂�
			StopSoundMem(mSoundHandle);
		}
	}


	
	

	mFrameCnt++;
}

void GameScene::Draw() {
	//BaseScene::Draw();
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));

	//if (m_plDeadFlag) {
	//	gameOver.Draw();
	//}
	//else if (m_bsDeadFlag) {
	//	//gameClear�֘A
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


	if (mPlIsDead) {	// Player������ł�����
		mGameOver->Draw();
	}
	else {	// Player������ł��Ȃ�������
		int tmpA = 0;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mIteIsExistings[i]) {
				tmpA += 1;
			}
		}


		mGameBack->Draw();
		DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", mPlIntDataMap["hp"], mPlIntDataMap["x"], tmpA, mFrameCnt);

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

			if (objId == 0) {	// Player�̕`��
				mPlayerMgr->Draw();
			}
			else if (objId == 1) {	// Enemy�̕`��
				mEnemyMgr->Draw(idx);
			}
			else {	// Item�̕`��
				mItemMgr->Draw(idx);
			}
		}

		// Player��hp�Q�[�W�̕`��
		mPlHpGauge->Draw();

		// �o�ߎ��Ԃ̕\��
		mTimeCounter->Draw();

		// ���v�X�R�A�̕\��
		mScoreCounter->Draw();
	}

	

	//DrawFormatString(400, 500, GetColor(255, 255, 255), "eneapp = %d", iNum);
}

void GameScene::UpdateDOrder() {
	using namespace std;

	//vector<pair<int, pair<int, int>>> yVec(3);	// first��y���W�Csecond�ɕ��̂̎�ނƃC���f�b�N�X�ԍ�����ꂽpair��vector
												// �L�����̎�ށi0: Player, 1: Enemy, 2: Item�j

	// ����������vector����ɂ���
	mDOrderVec.clear();

	// Player��y���W�����Z�b�g
	mDOrderVec.push_back({ mPlIntDataMap["y"], {0, 0} });

	// Enemy��y���W�����Z�b�g
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {
			mDOrderVec.push_back({ (int)mEneIntDataMaps.at(i)["y"], {1, i} });
		}
	}

	// Item��y���W�����Z�b�g
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {
			mDOrderVec.push_back({ (int)mIteIntDataMaps.at(i)["y"], {2, i} });
		}
	}

	// y���W�̏����ɕ��ёւ�
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

	//for (int i = 0; i < 6; i++) { //y���W�̏������ق����珇�ɕ`�悷��悤�ɂ��邽�߂ɕ`�悷�鏇�Ԃ���ꍞ��ł���
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
	// Player�̐g�̂̓����蔻��͈�
	int plLX = mPlIntDataMap["x"] - mPlIntDataMap["hitRangeW"];
	int plRX = mPlIntDataMap["x"] + mPlIntDataMap["hitRangeW"];
	int plTY = mPlIntDataMap["y"] - mPlIntDataMap["hitRangeH"];
	int plBY = mPlIntDataMap["y"] + mPlIntDataMap["hitRangeH"];
	int plPs[] = { plLX, plRX, plTY, plBY };

	// Player-Enemy�Ԃ̓����蔻��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (mEneIsExistings[i]) {	// Enemy�����݂��Ă�����
			// Enemy�̐g�̂̓����蔻��͈�
			int eneLX = mEneIntDataMaps.at(i)["x"] - mEneIntDataMaps.at(i)["hitRangeW"];
			int eneRX = mEneIntDataMaps.at(i)["x"] + mEneIntDataMaps.at(i)["hitRangeW"];
			int eneTY = mEneIntDataMaps.at(i)["y"] - mEneIntDataMaps.at(i)["hitRangeH"];
			int eneBY = mEneIntDataMaps.at(i)["y"] + mEneIntDataMaps.at(i)["hitRangeH"];
			int enePs[] = { eneLX, eneRX, eneTY, eneBY };

			// �����蔻��`�F�b�N������iPlayer�ɕK�v�CEnemy�ɂ͕s�v�j
			mPlIsHitMap["enemy"].at(i) = IsHit(plPs, enePs);

			// PlayerAttack-Enemy�Ԃ̓����蔻��
			if (mPlBoolDataMap["isAttacking"]) {	// Player���U������������
				// Player�̍U���̓����蔻��͈�
				int plALX = mPlIntDataMap["ax"] - mPlIntDataMap["hitRangeAW"];
				int plARX = mPlIntDataMap["ax"] + mPlIntDataMap["hitRangeAW"];
				int plATY = mPlIntDataMap["ay"] - mPlIntDataMap["hitRangeAH"];
				int plABY = mPlIntDataMap["ay"] + mPlIntDataMap["hitRangeAH"];
				int plAPs[] = { plALX, plARX, plATY, plABY };

				// Enemy�ɍU���������������ǂ����m�F����
				mPlIsHitMap["plAToEnemy"].at(i) = IsHit(plAPs, enePs);
			}
			else {	// Player���U�����łȂ����
				mPlIsHitMap["plAToEnemy"].at(i) = false;
			}

			// Player-EnemyAttack�Ԃ̓����蔻��
			if (mEneBoolDataMaps.at(i)["isAttacking"]) {	// Enemy���U������������
				mPlIsHitMap["enemyAttack"].at(i) = false;
				
				int eneANum = mEneIntDataMaps.at(i)["attackNum"];
				for (int j = 0; j < eneANum; j++) {	// �eEnemy�̍U�����̕�����
					int eneALX = mEneAXYMapVecs.at(i).at(j)["ax"] - mEneAXYMapVecs.at(i).at(j)["hitRangeAW"];
					int eneARX = mEneAXYMapVecs.at(i).at(j)["ax"] + mEneAXYMapVecs.at(i).at(j)["hitRangeAW"];
					int eneATY = mEneAXYMapVecs.at(i).at(j)["ay"] - mEneAXYMapVecs.at(i).at(j)["hitRangeAH"];
					int eneABY = mEneAXYMapVecs.at(i).at(j)["ay"] + mEneAXYMapVecs.at(i).at(j)["hitRangeAH"];
					int eneAPs[] = { eneALX, eneARX, eneATY, eneABY };

					// Enemy�̍U���������������ǂ����m�F����iPlayer�ɕK�v�CEnemy�ɂ͕s�v�j
					if (IsHit(plPs, eneAPs)) {	// Enemy�̍U�����������Ă�����
						mPlIsHitMap["enemyAttack"].at(i) = true;
					}
				}
			}
			else {	// Enemy���U�����łȂ����
				mPlIsHitMap["enemyAttack"].at(i) = false;
			}
			
		}
		else {	// Enemy�����݂��Ă��Ȃ�������
			mPlIsHitMap["enemy"].at(i) = false;
			mPlIsHitMap["plAToEnemy"].at(i) = false;
			mPlIsHitMap["enemyAttack"].at(i) = false;
		}

		// Enemy���̔���ɂ��������ʂ�����
		mEneIsHits[i] = mPlIsHitMap["plAToEnemy"].at(i);
	}


	// Player-Item�Ԃ̓����蔻��X�V
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {	// Item�����݂��Ă�����
			// Item�̓����蔻��͈�
			int iteLX = mIteIntDataMaps.at(i)["x"] - mIteIntDataMaps.at(i)["hitRangeW"];
			int iteRX = mIteIntDataMaps.at(i)["x"] + mIteIntDataMaps.at(i)["hitRangeW"];
			int iteTY = mIteIntDataMaps.at(i)["y"] - mIteIntDataMaps.at(i)["hitRangeH"];
			int iteBY = mIteIntDataMaps.at(i)["y"] + mIteIntDataMaps.at(i)["hitRangeH"];
			int itePs[] = { iteLX, iteRX, iteTY, iteBY };

			// �����蔻��`�F�b�N������
			mPlIsHitMap["item"].at(i) = IsHit(plPs, itePs);
			
			// PlayerAttack-Item�Ԃ̓����蔻��
			if (mPlBoolDataMap["isAttacking"] && mIteIntDataMaps.at(i)["itemId"] >= 12) {	// Player���U�����Ŕ��n�A�C�e����������
				// Player�̍U���̓����蔻��͈�
				int plALX = mPlIntDataMap["ax"] - mPlIntDataMap["hitRangeAW"];
				int plARX = mPlIntDataMap["ax"] + mPlIntDataMap["hitRangeAW"];
				int plATY = mPlIntDataMap["ay"] - mPlIntDataMap["hitRangeAH"];
				int plABY = mPlIntDataMap["ay"] + mPlIntDataMap["hitRangeAH"];
				int plAPs[] = { plALX, plARX, plATY, plABY };

				// Item�ɍU���������������ǂ����m�F����i���Ȃǂ�Item�ɕK�v�CPlayer�ɂ͕s�v�j
				mPlIsHitMap["plAToItem"].at(i) = IsHit(plAPs, itePs);
			}
			else {	// Player���U�����łȂ����
				mPlIsHitMap["plAToItem"].at(i) = false;
			}
		}
		else {	// Item�����݂��Ă��Ȃ�������
			mPlIsHitMap["item"].at(i) = false;
			mPlIsHitMap["plAToItem"].at(i) = false;
		}

		// Item���̔���ɂ��������ʂ�����
		mIteIsHitMaps.at(i)["player"] = mPlIsHitMap["item"].at(i);
		mIteIsHitMaps.at(i)["playerAttack"] = mPlIsHitMap["plAToItem"].at(i);
	}
}


bool GameScene::IsHit(const int (&ps1)[4], const int(&ps2)[4]) {
	bool isHit;	// �Ԃ��l

	// �����蔻��`�F�b�N������
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
			if (mEneBoolDataMaps.at(i)["isDead"]) {	// Enemy��Player�ɓ|����C������Ƃ�
				// �擾�i�j��j���A�C�e���̃X�R�A��ǉ�����
				mScoreCounter->AddScore(mEneIntDataMaps.at(i)["score"]);
			}
		}
	}

	// Item
	for (int i = 0; i < ITEM_NUM; i++) {
		if (mIteIsExistings[i]) {
			if (mIteBoolDataMaps.at(i)["isDead"]) {	// Item��Player�Ɏ擾�i�j��j����C������Ƃ�
				// �擾�i�j��j���A�C�e���̃X�R�A��ǉ�����
				mScoreCounter->AddScore(mIteIntDataMaps.at(i)["score"]);
			}
		}
	}
}