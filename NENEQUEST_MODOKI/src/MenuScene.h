#pragma once

#include "BaseScene.h"
#include "UpdateKey.h"
#include "SceneChanger.h"

class MenuScene : public BaseScene, UpdateKey {
public :
	MenuScene(SceneChanger* changer);
	void Initialize() override;
	void Finalize() override {};
	void Update() override;
	void Draw() override;
private:
	int mTriY;	// 選択に使用する三角形の中心のy座標
	const int mTriYs[3] = { 525, 590, 655 };
	int mTriYId = 0;
};