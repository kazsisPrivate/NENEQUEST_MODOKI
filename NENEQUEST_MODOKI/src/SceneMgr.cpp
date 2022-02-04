//#include "DxLib.h"
#include "ConfigScene.h"
#include "GameScene.h"
#include "MenuScene.h"
//#include "GameOver.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr() :
	mSceneNext(eSceneNone) //次のシーン管理変数
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
	if (mSceneNext != eSceneNone) { // 次のシーンがセットされているとき
		// 現在のシーンの終了処理を実行
		mScene->Finalize(); 
		delete mScene;

		switch (mSceneNext) { // mScenNextで指定されたシーンに変更
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
		// 次のシーン情報を空にする
		mSceneNext = eSceneNone;    

		// シーンを初期化
		mScene->Initialize();    
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