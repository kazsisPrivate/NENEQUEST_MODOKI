#pragma once

static class ItemGraphics {	// �摜�̓ǂݍ��ݎ��ԍ팸�̂��߂̃N���X
public:
	static int* GetGraHandle(const int iteId);	// iteId�͊e�L�����̃t�@�C�����ɂ���ԍ�(Arrow�i�E�����j��16�CArrow�i�������j��17)
	static void Initialize();
	static void Finalize();

private:
    static int mIte1to11Handle[11];	// Item1�`11
	static int mIte12to15Handle[4][2];	// Item12�`15
	static int mArrowHandle[2];	// Arrow�i�������ƉE�����j
};