#pragma once
/*
* メニュー画面（MenuScene），ゲームプレイ画面（GameScene），操作説明画面（ConfigScene）
* の管理を行うクラス
*/
#include "SceneChanger.h"
#include "BasicFunc.h"
#include "BaseScene.h"


class MenuScene;
class GameScene;
class ConfigScene;


class SceneMgr : public SceneChanger, BasicFunc {
public:
	SceneMgr();
	static SceneMgr* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangeScene(const EScene sceneNext) override;	// 引数SceneNextにシーンを変更する

private:
	BaseScene* mScene;    // シーン管理変数
	EScene mSceneNext;    // 次のシーン管理変数

private:
	static SceneMgr* mSceneMgr;
};
