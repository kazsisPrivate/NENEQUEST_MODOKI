#pragma once

#include "BasicFunc.h"
#include "SceneChanger.h"

class BaseScene : public BasicFunc {
protected:
	int mImageHandle;	// �摜
	int mFontHandle;	// �����t�H���g
	SceneChanger* mSceneChanger;	// �V�[���`�F���W�̍ۂɎg�p����

public:
	BaseScene(SceneChanger* changer);
	virtual void Initialize() override {};
	virtual void Finalize() override;
	virtual void Update() override {};
	virtual void Draw() override;
};
