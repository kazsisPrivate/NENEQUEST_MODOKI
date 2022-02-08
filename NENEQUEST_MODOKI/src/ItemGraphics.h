#pragma once

static class ItemGraphics {	// 画像の読み込み時間削減のためのクラス
public:
	static int* GetGraHandle(const int iteId);	// iteIdは各キャラのファイル名にある番号(Arrow（右向き）は15，Arrow（左向き）は16)
	static void Initialize();
	static void Finalize();

private:
    static int mIte1to11Handles[11];	// Item1～11
	static int mIte12to14Handles[3][2];	// Item12～14
	static int mArrowHandles[2];	// Arrow（左向きと右向き）
};