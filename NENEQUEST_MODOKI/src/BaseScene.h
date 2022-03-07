#pragma once
/*
* ���j���[��ʁiMenuScene�j�C�Q�[���v���C��ʁiGameScene�j�C���������ʁiConfigScene�j
* �̊��N���X�Ƃ���N���X
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
	SceneChanger* mSceneChanger;	// �V�[���`�F���W�̍ۂɎg�p����
};
