#include "DxLib.h"
#include "UpdateKey.h"


void UpdateKey::gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る

	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {	// i番のキーコードに対応するキーが押されていたら
			// 加算する
			key[i]++;     
		}
		else {	// 押されていなければ
			// 0にする
			key[i] = 0;   
		}
	}
}