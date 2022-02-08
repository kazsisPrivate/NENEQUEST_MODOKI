//#include "DxLib.h"
#include "ConfigScene.h"
#include "GameScene.h"
#include "MenuScene.h"
//#include "GameOver.h"
#include "SceneMgr.h"


SceneMgr* SceneMgr::mSceneMgr;


SceneMgr::SceneMgr() : mSceneNext(eSceneNone) {
}


SceneMgr* SceneMgr::GetInstance() {
	if (!SceneMgr::mSceneMgr) {
		SceneMgr::mSceneMgr = new SceneMgr();
		SceneMgr::mSceneMgr->Initialize();
	}

	return SceneMgr::mSceneMgr;
}


void SceneMgr::Initialize() {
	mScene = (BaseScene*)MenuScene::GetInstance();
	//mScene->Initialize();
}


void SceneMgr::Finalize() {
	mScene->Finalize();

	delete mSceneMgr;
	mSceneMgr = NULL;
}


void SceneMgr::Update() {
	if (mSceneNext != eSceneNone) { // ���̃V�[�����Z�b�g����Ă���Ƃ�
		// ���݂̃V�[���̏I�����������s
		mScene->Finalize(); 
		//delete mScene;

		switch (mSceneNext) { // mScenNext�Ŏw�肳�ꂽ�V�[���ɕύX
			case eSceneMenu:
				mScene = (BaseScene*) MenuScene::GetInstance();
				break;
			case eSceneGame:
				mScene = (BaseScene*) GameScene::GetInstance();
				break;
			case eSceneConfig:
				mScene = (BaseScene*) ConfigScene::GetInstance();
				break;
		}
		// ���̃V�[��������ɂ���
		mSceneNext = eSceneNone;    

		// �V�[����������
		//mScene->Initialize();    
	}

	// �V�[���̍X�V
	mScene->Update(); 
}


void SceneMgr::Draw() {
	mScene->Draw();
}


void SceneMgr::ChangeScene(const EScene sceneNext) {
	// ���̃V�[�����Z�b�g����
	mSceneNext = sceneNext;    
}