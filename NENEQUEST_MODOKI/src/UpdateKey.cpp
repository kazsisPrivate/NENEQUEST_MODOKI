#include "DxLib.h"
#include "UpdateKey.h"


void UpdateKey::gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {	// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			// ���Z����
			key[i]++;     
		}
		else {	// ������Ă��Ȃ����
			// 0�ɂ���
			key[i] = 0;   
		}
	}
}