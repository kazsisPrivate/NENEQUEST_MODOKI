#pragma once

#include "BasicFunc.h"
#include "SceneChanger.h"

class BaseScene : public BasicFunc {
protected:
	int mImageHandle;	// 画像
	int mFontHandle;	// 文字フォント
	SceneChanger* mSceneChanger;	// シーンチェンジの際に使用する

public:
	BaseScene(SceneChanger* changer);
	virtual void Initialize() override {};
	virtual void Finalize() override;
	virtual void Update() override {};
	virtual void Draw() override;
};
