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
	mGameClear = new GameClear();

	// ��ʂ̊e�\���v�f�̏�����
	mGameBack->Initialize();
	mPlayerMgr->Initialize();
	mEnemyMgr->Initialize();
	mItemMgr->Initialize();
	mPlHpGauge->Initialize();
	mTimeCounter->Initialize();
	mScoreCounter->Initialize();
	mGameOver->Initialize();
	mGameClear->Initialize();

	// �����̏�����
	mSoundHandle = LoadSoundMem("sounds/NENEQUEST.ogg");
	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);

	// �t���[�����̃J�E���g�̏�����
	mFrameCnt = 0;

	// Player�͎���ł��Ȃ���ԂƂ��Đݒ�
	mPlIsDead = false;

	// Stage�֘A�̐ݒ�
	mIsChangingSt = false;
	mIsAtBsSt = false;

	// Timer���J�n����
	mTimeCounter->StartTime();
}

void GameScene::Finalize() {
	// ��ʂ̊e�\���v�f�̏I������
	mGameBack->Finalize();
	mPlayerMgr->Finalize();
	mEnemyMgr->Finalize();
	mItemMgr->Finalize();
	mPlHpGauge->Finalize();
	mTimeCounter->Finalize();
	mScoreCounter->Finalize();
	mGameOver->Finalize();
	mGameClear->Finalize();

	// �Q�[���̉��y�̍폜
	StopSoundMem(mSoundHandle);
	DeleteSoundMem(mSoundHandle);

	delete mGameScene;
	mGameScene = NULL;
}

void GameScene::Update() {
	// Esc�L�[�ŃQ�[�����~�߂���悤�ɂ���
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		mSceneChanger->ChangeScene(eSceneMenu);
	}

	if (mHasClearedGame) {	// �Q�[���N���A���āiEnemyBoss��|���āj������
		// GameClear��ʂ̍X�V
		mGameClear->Update();
	}
	else if (mPlIsDead) {	// Player������ł�����
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

		// Enemy��Boss�������ۂ̓��ʂȏ���
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mEneIsExistings[i]) {
				if (mEneBoolDataMaps.at(i)["isBoss"]) {	// Boss�������Ƃ�
					if (mEneBoolDataMaps.at(i)["isDead"]) {	// Boss���|���ꂽ�Ƃ�
						// �Q�[���N���A�Ƃ���
						mHasClearedGame = true;
						mTimeCounter->StopTime();
					}

					if (mEneBoolDataMaps.at(i)["isCreatingIteB"]) {	// ItemBox�𐶐����Ăق����Ƃ���������
						mItemMgr->CreateItem(mEneIntDataMaps.at(i)["itemBoxKind"],
							mEneIntDataMaps.at(i)["itemBoxX"], mEneIntDataMaps.at(i)["itemBoxY"]);
					}
				}
			}
		}

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
		if (mFrameCnt >= 300 &&	// �ŏ���300�J�E���g�̓Q�[�������Ă���l�ɗ]�T���������邽�߂ɉ����o�������Ȃ�
			mFrameCnt < BOSS_START_FRAME_NUM) {	// BossStage�̈ڍs���n�߂悤�Ƃ��Ă��Ȃ�������
			// Enemy��Item�̏o���͓��t���[���̏������y�����邽�߂ɈႤ�t���[���ŏo��������������
			if (mFrameCnt % ITE_CREATION_FRAME_NUM == 0) {
				mItemMgr->CreateItem();
			}
			
			if ((mFrameCnt + ITE_CREATION_FRAME_NUM / 2) % ENE_CREATION_FRAME_NUM == 0) {
				mEnemyMgr->CreateEnemy();
			}
		}

		// BossStage�ւ̈ڍs���n�߂邩�ǂ��������߂�
		if (!mIsAtBsSt) {	// BossStage�ɓ����Ă��Ȃ��Ƃ�
			if (!mIsChangingSt) {	// BossStage�ւ̈ڍs���n�߂Ă��Ȃ��Ƃ�
				if (mFrameCnt >= BOSS_START_FRAME_NUM) {	// BossStage�̈ڍs���n�߂������Ԃ𒴂��Ă���Ƃ�
					bool eneIteIsExisting = false;
					for (int i = 0; i < ENEMY_NUM; i++) {
						if (mEneIsExistings[i]) eneIteIsExisting = true;
					}
					for (int i = 0; i < ITEM_NUM; i++) {
						if (mIteIsExistings[i]) eneIteIsExisting = true;
					}

					if (!eneIteIsExisting) {	// Enemy��Item�����݂��Ȃ���ԂɂȂ�����
						// BossStage�ւ̈ڍs���n�߂�
						mIsChangingSt = true;
						mGameBack->StartChangingSt();
						mPlayerMgr->SetIsChangingSt(mIsChangingSt);
						mEnemyMgr->CreateEnemyBoss(mGameBack->GetBsStX());
					}
				}
			}
			else {	// BossStage�ւ̈ڍs���̂Ƃ�
				// BossStage�ւ̈ڍs�������������ǂ������m�F����
				mIsAtBsSt = mGameBack->GetIsAtBsSt();

				if (mIsAtBsSt) {	// �ڍs���������Ă�����
					mIsChangingSt = false;
					mPlayerMgr->SetIsChangingSt(mIsChangingSt);
					mPlayerMgr->SetIsAtBsSt(mIsAtBsSt);
				}
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

		if (mPlIsDead || mHasClearedGame) {	// ���̃t���[����GameOver��ʂ�GameClear��ʂɈڍs����Ƃ�
			// �������~�߂�
			StopSoundMem(mSoundHandle);

			if (mHasClearedGame) {	// ���̃t���[����GameClear��ʂɈڍs����Ƃ�
				// �N���A��ʂŕ\������X�R�A��n��
				mGameClear->SetScores(mScoreCounter->GetTotalScore(), 50 * (999 - mTimeCounter->GetClearTime()));
			}
		}
	}

	mFrameCnt++;
}

void GameScene::Draw() {
	if (mHasClearedGame) {	// �Q�[���N���A���āiEnemyBoss��|���āj������
		mGameClear->Draw();
	}
	else if (mPlIsDead) {	// Player������ł�����
		mGameOver->Draw();
	}
	else {	// Player������ł��Ȃ�������
		int tmpA = 0;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (mIteIsExistings[i]) {
				tmpA += 1;
			}
		}

		// �w�i�̕`��
		mGameBack->Draw();
		//DrawFormatString(500, 300, GetColor(255, 255, 255), "px = %d, ex = %d, %d, %d", mPlIntDataMap["hp"], mPlIntDataMap["x"], tmpA, mFrameCnt);	// �f�o�b�O�p

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
}

void GameScene::UpdateDOrder() {
	using namespace std;

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
}


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