#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SetBackgroundColor(255, 255, 255);

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr.Update();
		sceneMgr.Draw();
	}
	
	sceneMgr.Finalize();

	// DX���C�u�����I������
	DxLib_End(); 

	return 0;
}