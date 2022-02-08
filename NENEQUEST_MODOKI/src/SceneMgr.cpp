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
	if (mSceneNext != eSceneNone) { // 次のシーンがセットされているとき
		// 現在のシーンの終了処理を実行
		mScene->Finalize(); 
		//delete mScene;

		switch (mSceneNext) { // mScenNextで指定されたシーンに変更
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
		// 次のシーン情報を空にする
		mSceneNext = eSceneNone;    

		// シーンを初期化
		//mScene->Initialize();    
	}

	// シーンの更新
	mScene->Update(); 
}


void SceneMgr::Draw() {
	mScene->Draw();
}


void SceneMgr::ChangeScene(const EScene sceneNext) {
	// 次のシーンをセットする
	mSceneNext = sceneNext;    
}