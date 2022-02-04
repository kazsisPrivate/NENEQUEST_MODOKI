//#include "DxLib.h"
#include "ConfigScene.h"
#include "GameScene.h"
#include "MenuScene.h"
//#include "GameOver.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr() :
	mSceneNext(eSceneNone) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new MenuScene(this);
}


void SceneMgr::Initialize() {
	mScene->Initialize();
}


void SceneMgr::Finalize() {
	mScene->Finalize();
}


void SceneMgr::Update() {
	if (mSceneNext != eSceneNone) { // ���̃V�[�����Z�b�g����Ă���Ƃ�
		// ���݂̃V�[���̏I�����������s
		mScene->Finalize(); 
		delete mScene;

		switch (mSceneNext) { // mScenNext�Ŏw�肳�ꂽ�V�[���ɕύX
			case eSceneMenu:
				mScene = (BaseScene*) new MenuScene(this);
				break;
			case eSceneGame:
				mScene = (BaseScene*) new GameScene(this);
				break;
			case eSceneConfig:
				mScene = (BaseScene*) new ConfigScene(this);
				break;
		}
		// ���̃V�[��������ɂ���
		mSceneNext = eSceneNone;    

		// �V�[����������
		mScene->Initialize();    
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