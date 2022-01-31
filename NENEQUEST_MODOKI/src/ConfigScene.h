#pragma once

#include "BaseScene.h"

class ConfigScene : public BaseScene {
public :
	ConfigScene(SceneChanger* changer);
	void Initialize() override;
	void Finalize() override {};
	void Update() override;
	void Draw() override;
};