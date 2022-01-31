#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), SetGraphMode(1280, 720, 16), SetWindowStyleMode(7), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SetBackgroundColor(255, 255, 255);

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		sceneMgr.Update();
		sceneMgr.Draw();
	}
	
	sceneMgr.Finalize();

	// DXライブラリ終了処理
	DxLib_End(); 

	return 0;
}