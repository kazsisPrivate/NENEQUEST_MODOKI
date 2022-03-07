#pragma once
/*
* ItemやEnemyが使用するエフェクト画像の読み込みおよび提供を行うクラス
*/


static class EffectGraphics {	// 画像の読み込み時間削減のためのクラス
public:
	static int* GetGraHandle(const int efeId);
	static void Initialize();
	static void Finalize();

private:
    static int mEfe1to3Handles[3];	// Effect1～3（Item5～7の効果）
	static int mArrowHitHandle;	// Arrowが当たったときのエフェクト
	static int mMgFireHandles[2];	// Enemy4, 5, 6が使用する火の玉（Enemy4, 5は赤い火の玉，Enemy6は青い火の玉）
	static int mSlashHandle[4];	// Enemy7が使用する鎌攻撃のエフェクト
	static int mBsFireBallHandles[2][2];	// EnemyBossが吐く火の玉(通常モードの火の玉と怒りモードの火の玉)
	static int mBsFireBreHandles[2];	// EnemyBossが吐く火の息の玉(通常モードの火の玉と怒りモードの火の玉)
};