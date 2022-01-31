#pragma once

#include "SceneChanger.h"
#include "BasicFunc.h"
#include "BaseScene.h"

class SceneMgr : public SceneChanger, BasicFunc {

private:
	BaseScene* mScene;    //シーン管理変数
	EScene mSceneNext;    //次のシーン管理変数

public:
	SceneMgr();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangeScene(const EScene sceneNext) override;	// 引数SceneNextにシーンを変更する

};
