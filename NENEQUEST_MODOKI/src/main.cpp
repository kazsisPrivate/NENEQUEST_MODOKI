#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetMouseDispFlag(true), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	// 画面が非アクティブの際も動作を続けるようにする
	SetAlwaysRunFlag(TRUE);

	SetBackgroundColor(255, 255, 255);

	// 使用するフォントの追加
	AddFontResource("fonts/HGRSGU.TTC");
	AddFontResource("fonts/BROADW.TTF");
	AddFontResource("fonts/SHOWG.TTF");
	AddFontResource("fonts/RAVIE.TTF");
	AddFontResource("fonts/msgothic.ttc");

	SceneMgr* sceneMgr = SceneMgr::GetInstance();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr->Update();
		sceneMgr->Draw();
	}
	
	sceneMgr->Finalize();

	// フォントの削除
	RemoveFontResource("fonts/HGRSGU.TTC");
	RemoveFontResource("fonts/BROADW.TTF");
	RemoveFontResource("fonts/SHOWG.TTF");
	RemoveFontResource("fonts/RAVIE.TTF");
	RemoveFontResource("fonts/msgothic.ttc");

	// DXライブラリ終了処理
	DxLib_End(); 

	return 0;
}