/*使用する基本的な関数セット*/

#pragma once


class BasicFunc {
public:
	virtual void Initialize() = 0;	// 初期化処理
	virtual void Finalize() = 0;	// 終了処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理
};
