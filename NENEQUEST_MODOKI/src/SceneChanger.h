#pragma once

typedef enum {	// �V�[���ꗗ
	eSceneMenu,
	eSceneGame,
	eSceneConfig,
	//eScene_GameOver,
	eSceneNone
} EScene ;

class SceneChanger {
public:
	virtual void ChangeScene(const EScene sceneNext) = 0;	// �V�[���ύX
};