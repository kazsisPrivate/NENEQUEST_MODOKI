#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetMouseDispFlag(true), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SetBackgroundColor(255, 255, 255);

	// �g�p����t�H���g�̒ǉ�
	AddFontResource("fonts/HGRSGU.TTC");
	AddFontResource("fonts/BROADW.TTC");
	AddFontResource("fonts/SHOWG.TTC");
	AddFontResource("fonts/RAVIE.TTC");
	AddFontResource("fonts/msgothic.TTC");

	SceneMgr* sceneMgr = SceneMgr::GetInstance();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr->Update();
		sceneMgr->Draw();
	}
	
	sceneMgr->Finalize();

	// �t�H���g�̍폜
	RemoveFontResource("fonts/HGRSGU.TTC");
	RemoveFontResource("fonts/BROADW.TTC");
	RemoveFontResource("fonts/SHOWG.TTC");
	RemoveFontResource("fonts/RAVIE.TTC");
	RemoveFontResource("fonts/msgothic.TTC");

	// DX���C�u�����I������
	DxLib_End(); 

	return 0;
}