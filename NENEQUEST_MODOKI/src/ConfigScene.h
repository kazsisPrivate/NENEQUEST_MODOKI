#pragma once

#include "BaseScene.h"


//class SceneMgr;


class ConfigScene : public BaseScene {
public :
	ConfigScene(SceneChanger* changer);
	static ConfigScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	static ConfigScene* mConfigScene;
};