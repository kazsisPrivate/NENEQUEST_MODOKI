#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);
    // DXライブラリ初期化処理
    if (DxLib_Init() < 0) {
        //エラーなら終了する
        return -1;
    }
    //描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);
    // 画面モードの変更
    SetGraphMode(800, 600, 32);
    // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        DrawFormatString(0, 0, GetColor(255, 255, 255), "ESCキーで終了します");
        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
            break;
        }
    }

    DxLib_End();    // DXライブラリ終了処理
    return 0;
}