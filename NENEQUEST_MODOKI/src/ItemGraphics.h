#pragma once

static class ItemGraphics {	// 画像の読み込み時間削減のためのクラス
public:
	static int* GetGraHandle(const int iteId);	// iteIdは各キャラのファイル名にある番号(Arrow（右向き）は16，Arrow（左向き）は17)
	static void Initialize();
	static void Finalize();

private:
    static int mIte1to11Handle[11];	// Item1～11
	static int mIte12to15Handle[4][2];	// Item12～15
	static int mArrowHandle[2];	// Arrow（左向きと右向き）
};