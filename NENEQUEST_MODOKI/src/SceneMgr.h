#pragma once
/*
* ���j���[��ʁiMenuScene�j�C�Q�[���v���C��ʁiGameScene�j�C���������ʁiConfigScene�j
* �̊Ǘ����s���N���X
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
	void ChangeScene(const EScene sceneNext) override;	// ����SceneNext�ɃV�[����ύX����

private:
	BaseScene* mScene;    // �V�[���Ǘ��ϐ�
	EScene mSceneNext;    // ���̃V�[���Ǘ��ϐ�

private:
	static SceneMgr* mSceneMgr;
};
