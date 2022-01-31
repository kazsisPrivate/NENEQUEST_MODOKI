#pragma once

#include "SceneChanger.h"
#include "BasicFunc.h"
#include "BaseScene.h"

class SceneMgr : public SceneChanger, BasicFunc {

private:
	BaseScene* mScene;    //�V�[���Ǘ��ϐ�
	EScene mSceneNext;    //���̃V�[���Ǘ��ϐ�

public:
	SceneMgr();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void ChangeScene(const EScene sceneNext) override;	// ����SceneNext�ɃV�[����ύX����

};
