#pragma once
/*
* ボス（ドラゴン）
*/
#include "Enemy.h"
#include "BossFire.h"
#include "ItemChanger.h"
#include <vector>


class EnemyBoss : public Enemy {
public:
	EnemyBoss(EnemyChanger* changer, const int eneIdx, const int x, const int y);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void GetEneDataMap(std::map<std::string, int>* eneIntDataMap, std::vector<std::map<std::string, int>>* eneAXYMapVec,
		std::map<std::string, bool>* eneBoolDataMap) override;	// Enemyのデータを渡すために使用する

private:
	void UpdateSAP();	// hpに合わせた攻撃力やスピードに変化させる
	void Walk() override;
	void Attack();
	void SelectAttack();	// 行う攻撃を決める
	void SummonEnemy();	// Enemyを呼びだす攻撃
	void CreateEnemy();	// 新しくEnemyを生成する，SummonEnemyで呼びだす
	void DropItemBox();	// ItemBoxを落とす攻撃
	void Jump();	// ItemBoxを落とす攻撃中で行うジャンプ
	void FireAttack();	// 火の玉攻撃

	BossFire* mBossFire;
	int IMG_W = 958, IMG_H = 600;	// EnemyBossの画像サイズ

	const int ENEBOSS_X_MAX = 1210;	// EnemyBossのx軸方向の移動範囲の最大値
	const int ENEBOSS_X_MIN = 1090;	// EnemyBossのx軸方向の移動範囲の最小値
	const int ENEBOSS_FIRST_X = 1160;	// BossStageへの移行を終え，BossStageが始まる際のEnemyBossの最初のx座標
	std::vector<int> mAXs;	// 各攻撃のx座標
	std::vector<int> mAYs;	// 各攻撃のy座標
	std::vector<int> mHitRangeAWs;	// 各攻撃の当たり判定の範囲（幅）
	std::vector<int> mHitRangeAHs;	// 各攻撃の当たり判定の範囲（高さ）
	int mDirecX;	// EnemyBossの移動方向の向き（-1: 左向き，1: 右向き）
	int mAlphaValue;	// 表示するEnemyBossの画像の透明度，倒されたときに透過していくのに使用する

	const int ENEBOSS_ATTACK_NUM_MAX = 5;	// EnemyBossができる攻撃の最大数（FireBreathの火の玉5個制御が最大）
	const int HP_ANGRY = 30;	// EnemyBossが怒りだすhp，怒りだすと攻撃の種類や速度，攻撃力等が変化する
	
	unsigned long long mWatingFrameCnt;	// 攻撃と攻撃間のフレーム数のカウント，攻撃の始めるタイミングなどの制御に使用する
	bool mIsChangingSt;	// BossStageへの移行中のときtrue，EnemyBossのオブジェクトが作成されたときは移行中であり，規定の位置に移動し終えたらfalseになる

	int mAFrameCnt;	// 攻撃中のフレーム数のカウント，攻撃の時間制御に使用する
	const int ATTACK_FRAME_NUM = 240;	// このフレーム数毎に攻撃をするかどうかを決める
	bool mIsFireAttacking;	// 火の玉攻撃中のときtrueとなる
	bool mIsSummoningEne;	// Enemy呼び出し攻撃中のときtrue
	bool mIsDroppingIteB;	// ItemBox落とし攻撃のときtrue
	const int ENEMY_FIRST_Y_MIN = 290;	// enemyが生成される際の最初のy座標の最小値
	const int ENEMY_FIRST_Y_MAX = 610;	// enemyが生成される際の最初のy座標の最大値

	bool mIsJumping;	// ItemBox落とし中で行うジャンプ中だったらtrue
	int mYPrev, mYStart;	// ジャンプで使用する

	int* mIteBHandle;	// 落とすItemBoxの画像
	int mIteBImgW, mIteBImgH;	// 落とすItemBoxの画像サイズ
	EItem mIteBKind;	// 落とすItemの種類
	int mIteBX, mIteBY;	// ItemBox落としで落とすItemBoxのxy座標
	const int ITEMBOX_FIRST_X_MIN = 300;	// ItemBoxが生成された際の最初のy座標の最小値
	const int ITEMBOX_FIRST_X_MAX = 650;	// ItemBoxが生成された際の最初のy座標の最大値
	int mIteBDY;	// ItemBox落としで落とすItemBoxのy座標の増加量
	int mIteBHitRangeW, mIteBHitRangeH;	// 落とすItemBoxの当たり判定
	bool mIsCreatingIteB;	// ItemBoxを落下させ終えてから，ItemBoxをItemMgrの方で作ってもらっているときtrue 
	int mCreIteBFrameCnt;	// ItemBoxを落下させ終えてから，ItemBoxをItemMgrの方で作ってもらっている間のフレーム数
};