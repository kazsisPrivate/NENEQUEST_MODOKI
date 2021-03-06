//#include "DxLib.h"
#include "ConfigScene.h"
#include "GameScene.h"
#include "MenuScene.h"
//#include "GameOver.h"
#include "SceneMgr.h"
#include "CharaGraphics.h"
#include "ItemGraphics.h"
#include "EffectGraphics.h"


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

	// 使用する画像の読み込みをしておく
	CharaGraphics::Initialize();
	ItemGraphics::Initialize();
	EffectGraphics::Initialize();
}


void SceneMgr::Finalize() {
	// 使用していたシーンの削除
	mScene->Finalize();

	// 画像の削除
	CharaGraphics::Finalize();
	ItemGraphics::Finalize();
	EffectGraphics::Finalize();

	delete mSceneMgr;
	mSceneMgr = NULL;
}


void SceneMgr::Update() {
	if (mSceneNext != eSceneNone) { // 次のシーンがセットされているとき
		// 現在のシーンの終了処理を実行
		mScene->Finalize(); 

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