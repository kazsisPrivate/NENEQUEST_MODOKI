#pragma once
/*
* Sceneの変更を行うための列挙型とクラス
*/

typedef enum {	// シーン一覧
	eSceneMenu,
	eSceneGame,
	eSceneConfig,
	eSceneNone
} EScene ;

class SceneChanger {
public:
	virtual void ChangeScene(const EScene sceneNext) = 0;	// シーン変更
};