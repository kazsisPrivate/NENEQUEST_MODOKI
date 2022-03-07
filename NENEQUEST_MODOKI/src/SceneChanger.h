#pragma once
/*
* Scene�̕ύX���s�����߂̗񋓌^�ƃN���X
*/

typedef enum {	// �V�[���ꗗ
	eSceneMenu,
	eSceneGame,
	eSceneConfig,
	eSceneNone
} EScene ;

class SceneChanger {
public:
	virtual void ChangeScene(const EScene sceneNext) = 0;	// �V�[���ύX
};