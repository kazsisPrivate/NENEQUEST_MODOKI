#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetMouseDispFlag(true), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	// ��ʂ���A�N�e�B�u�̍ۂ�����𑱂���悤�ɂ���
	SetAlwaysRunFlag(TRUE);

	SetBackgroundColor(255, 255, 255);

	// �g�p����t�H���g�̒ǉ�
	AddFontResource("fonts/HGRSGU.TTC");
	AddFontResource("fonts/BROADW.TTF");
	AddFontResource("fonts/SHOWG.TTF");
	AddFontResource("fonts/RAVIE.TTF");
	AddFontResource("fonts/msgothic.ttc");

	SceneMgr* sceneMgr = SceneMgr::GetInstance();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr->Update();
		sceneMgr->Draw();
	}
	
	sceneMgr->Finalize();

	// �t�H���g�̍폜
	RemoveFontResource("fonts/HGRSGU.TTC");
	RemoveFontResource("fonts/BROADW.TTF");
	RemoveFontResource("fonts/SHOWG.TTF");
	RemoveFontResource("fonts/RAVIE.TTF");
	RemoveFontResource("fonts/msgothic.ttc");

	// DX���C�u�����I������
	DxLib_End(); 

	return 0;
}