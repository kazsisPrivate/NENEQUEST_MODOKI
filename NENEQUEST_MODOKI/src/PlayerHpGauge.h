#pragma once

// Player��hp�Q�[�W
#include "BasicFunc.h"


class PlayerHpGauge : public BasicFunc {
public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void SetPlayerHp(const int plHp);

private:
	int mPlHp;
	int mPlFaceHandle;
	int mGaugeColor;
};
