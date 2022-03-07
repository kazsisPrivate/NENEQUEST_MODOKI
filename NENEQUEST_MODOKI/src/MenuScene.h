#pragma once
/*
* ���j���[��ʁiGameScene�j�̃N���X
*/
#include "BaseScene.h"
#include "UpdateKey.h"
#include "SceneChanger.h"
#include <string>


class MenuScene : public BaseScene, UpdateKey {
public :
	MenuScene(SceneChanger* changer);
	static MenuScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	int mTitleFontHandle;	// �^�C�g���̕����̃t�H���g
	int mOptionFontHandle;	// �I�����̕����t�H���g

	std::string mTitleStrs[2];
	int mTitleXs[2];// = { 100, 300 };	// �^�C�g���̕�����x���W
	int mTitleYs[2];// = { 30, 150};	// �^�C�g���̕�����y���W
	int mTriY;	// �I���Ɏg�p����O�p�`�̒��S��y���W
	const int TRI_YS[3] = { 525, 590, 655 };
	int mTriYId = 0;

private:
	static MenuScene* mMenuScene;
};