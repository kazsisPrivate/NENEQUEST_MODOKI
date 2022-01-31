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
	int mTriY;	// �I���Ɏg�p����O�p�`�̒��S��y���W
	const int mTriYs[3] = { 525, 590, 655 };
	int mTriYId = 0;
};