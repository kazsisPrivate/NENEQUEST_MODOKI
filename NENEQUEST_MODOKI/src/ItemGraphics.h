#pragma once

static class ItemGraphics {	// �摜�̓ǂݍ��ݎ��ԍ팸�̂��߂̃N���X
public:
	static int* GetGraHandle(const int iteId);	// iteId�͊e�L�����̃t�@�C�����ɂ���ԍ�(Arrow�i�E�����j��15�CArrow�i�������j��16)
	static void Initialize();
	static void Finalize();

private:
    static int mIte1to11Handles[11];	// Item1�`11
	static int mIte12to14Handles[3][2];	// Item12�`14
	static int mArrowHandles[2];	// Arrow�i�������ƉE�����j
};