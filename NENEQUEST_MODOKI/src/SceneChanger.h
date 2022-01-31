#pragma once

typedef enum {	// シーン一覧
	eSceneMenu,
	eSceneGame,
	eSceneConfig,
	//eScene_GameOver,
	eSceneNone
} EScene ;

class SceneChanger {
public:
	virtual void ChangeScene(const EScene sceneNext) = 0;	// シーン変更
};