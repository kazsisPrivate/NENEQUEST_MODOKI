#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetMouseDispFlag(true), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetBackgroundColor(255, 255, 255);

	// 使用するフォントの追加
	AddFontResource("fonts/HGRSGU.TTC");
	AddFontResource("fonts/BROADW.TTC");
	AddFontResource("fonts/SHOWG.TTC");
	AddFontResource("fonts/RAVIE.TTC");
	AddFontResource("fonts/msgothic.TTC");

	SceneMgr* sceneMgr = SceneMgr::GetInstance();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr->Update();
		sceneMgr->Draw();
	}
	
	sceneMgr->Finalize();

	// フォントの削除
	RemoveFontResource("fonts/HGRSGU.TTC");
	RemoveFontResource("fonts/BROADW.TTC");
	RemoveFontResource("fonts/SHOWG.TTC");
	RemoveFontResource("fonts/RAVIE.TTC");
	RemoveFontResource("fonts/msgothic.TTC");

	// DXライブラリ終了処理
	DxLib_End(); 

	return 0;
}