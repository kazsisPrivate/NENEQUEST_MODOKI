#pragma once
/*
* メニュー画面（MenuScene），ゲームプレイ画面（GameScene），操作説明画面（ConfigScene）
* の基底クラスとするクラス
*/
#include "BasicFunc.h"
#include "SceneChanger.h"

class BaseScene : public BasicFunc {
public:
	BaseScene(SceneChanger* changer);
	virtual void Initialize() override {};
	virtual void Finalize() override {};
	virtual void Update() override {};
	virtual void Draw() override {};

protected:
	SceneChanger* mSceneChanger;	// シーンチェンジの際に使用する
};
