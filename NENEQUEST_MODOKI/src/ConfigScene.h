#pragma once
/*
* ���������ʂ̃N���X
*/
#include "BaseScene.h"


class ConfigScene : public BaseScene {
public :
	ConfigScene(SceneChanger* changer);
	static ConfigScene* GetInstance();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	int* mPlHandle;	// Player�̉摜
	int *mEneHandles[2];	// Enemy�̉摜
	int *mWeaHandles[2];	// ����̉摜
	int *mIteHandles[3];	// Item�̉摜
	int* mIteBHandles[2];	// ItemBox�̉摜

	int mPlX, mPlY;	// Player�̉摜��xy���W
	int mEneXs[2], mEneYs[2];	// Enemy�̉摜��xy���W
	int mWeaXs[2], mWeaYs[2];	// ����̉摜��xy���W
	int mIteXs[3], mIteYs[3];	// Item�̉摜��xy���W
	int mIteBXs[3], mIteBYs[3];	// ItemBox�̉摜��xy���W

	int mExpStrFontHandles[2];	// �������Ɏg�p����t�H���g
	int mEscStrFontHandle;	// "���j���[��ʂɖ߂�iEsc�L�[�������j"�̕����̃t�H���g

private:
	static ConfigScene* mConfigScene;
};