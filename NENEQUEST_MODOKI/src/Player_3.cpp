#include "Player_3.h"
#include "DxLib.h"
#include "HitJudge0.h"
#include "HitJudge1.h"
#include "HitJudge2.h"
#include "PlayerData.h"
#include "PowerBox.h"

Player_3::Player_3(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 3)) {
}

void Player_3::Initialize() {
	HitJudge0::Initialize();
	HitJudge1::Initialize();
	HitJudge2::Initialize();
	PowerBox::SetPlPower(3);
	x = PlayerData::GetPlayerX(), y = PlayerData::GetPlayerY();
	hp = PlayerData::GetPlayerHP();
	ax = x + 160;
	ay = y + 20;
	hitRangeX = 33, hitRangeY = 60;
	hitRangeAX = 35, hitRangeAY = 60;
	sizeX = 500, sizeY = 283;
	//LoadDivGraph("images/player_3-1-1.png", 24, 2, 12, sizeX, sizeY, charaHandle);
	//GetGraph(0, 3, charaHandle);
	xcount = 0, ycount = 0;
	attackCount = 0;
	godCount = -1;
	jumpFlag = false;
	attackFlag = false;
	godFlag = false;
	icount = 0;
	iscount = PlayerData::GetIscount();
	ipcount = PlayerData::GetIpcount();
	effectNum = PlayerData::GetEffectNum();
	weaponNum = 5;
	ihPower = 0;
	bscount = PlayerData::GetBscount();
	deadCount = 0;

	if (effectNum == 0) {
		isPower = 1;
		iPower = 1;
	}
	else if (effectNum == 1) {
		isPower = 2;
		iPower = 1;
		effectHandle = LoadGraph("images/effect_1.png");
	}
	else if (effectNum == 2) {
		isPower = 0.5;
		iPower = 1;
		effectHandle = LoadGraph("images/effect_2.png");
	}
	else {
		isPower = 1;
		iPower = 2;
		effectHandle = LoadGraph("images/effect_3.png");
	}
}

void Player_3::Finalize() {
	/*for (int i = 0; i < 24; i++) {
		DeleteGraph(charaHandle[i]);
	}*/
	DeleteGraph(effectHandle);
}

void Player_3::Update() {
	if (hp == 0) {
		if (deadCount == 120) {
			PlayerData::SetDeadFlag(true);
		}

		handleNumber = 0;

		deadCount++;
	}
	else {
		bossFlag = PlayerData::GetBossFlag();

		if (bossFlag == true && bscount <= 1280) {
			BossStart();
		}
		else {
			if (weaponNum != 3 && weaponNum != 5 && weaponNum != 6) {
				if (weaponNum == 1) {
					mPlayerChanger->ChangePlayer(ePlayer_1);
				}
				else if (weaponNum == 2) {
					mPlayerChanger->ChangePlayer(ePlayer_2);
				}
				else {
					mPlayerChanger->ChangePlayer(ePlayer_4);
				}

				PlayerData::SetIscount(iscount);
				PlayerData::SetIpcount(ipcount);
			}

			gpUpdateKey();

			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0) {
				xcount = 0;
			}
			if (key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				ycount = 0;
			}
			if (key[KEY_INPUT_LEFT] == 0 && key[KEY_INPUT_RIGHT] == 0 && key[KEY_INPUT_UP] == 0 && key[KEY_INPUT_DOWN] == 0) {
				if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
					handleNumber = 6;
				}
				else {
					handleNumber = 0;
				}
			}

			Speed(); //player‚Ìs‚¤“®ì‚É“K‚µ‚½‘¬“x‚ÉÝ’è

			if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0 || key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
				Walk();
			}

			if (attackCount == 0 && (jumpFlag == true || key[KEY_INPUT_A] == 1)) {
				Jump();
			}
			else if (attackCount != 0 || key[KEY_INPUT_S] == 1) {
				Attack();
			}

			PlayerData::SetPlayerXY(x, y);

			HitJudge();
		}
	}
}

void Player_3::Draw() {
	if (godFlag == true) {
		if (godCount == -1) {
			godFlag = false;
		}
		else if (godCount > 80 || (godCount <= 60 && godCount > 40) || godCount <= 20) {
			handleNumber += 12;
			--godCount;
		}
		else {
			--godCount;
		}
	}
	DrawGraph(x - sizeX / 2, y - sizeY / 2 - 13, charaHandle[handleNumber], TRUE);
	//DrawBox(ax - 35, ay - 60, ax + 35, ay + 60, GetColor(0, 0, 0), TRUE);

	if (isPower != 1 || iPower != 1) {
		DrawGraph(x - 114, y - 113, effectHandle, TRUE);
	}

	//DrawFormatString(100, 200, GetColor(255, 255, 255), "ys = %d", godCount);
	//DrawFormatString(100, 300, GetColor(255, 255, 255), "px = %d, ex = %d", HitJudge0::playerALX, HitJudge0::enemyLX);
}

void Player_3::Speed() {
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {
		if (jumpFlag == true) {
			move = 0.8f;
		}
		else if (attackCount != 0) {
			move = 0.5f;
		}
		else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
			move = 0.625f;
		}
		else {
			move = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
		if (attackCount != 0) {
			move = 0.5f;
		}
		else {
			move = 0.80f;
		}
	}

	if (iscount != -1) {
		if (iscount == 0) {
			isPower = 1;
			PlayerData::SetEffectNum(0);
			DeleteGraph(effectHandle);
		}

		iscount--;
	}

	if (ipcount != -1) {
		if (ipcount == 0) {
			iPower = 1;
			PowerBox::SetPlPower(1);
			PlayerData::SetEffectNum(0);
			DeleteGraph(effectHandle);
		}

		ipcount--;
	}
}

void Player_3::Walk() {
	if (bossFlag == false) {
		if (key[KEY_INPUT_LEFT] != 0) {
			if (x > 53) {
				x -= (int)(4 * move * isPower);
			}

			if (xcount > 0) {
				xcount = 0;
			}
			--xcount;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {
			if (x < 1147) {
				x += (int)(4 * move * isPower);
			}

			if (xcount < 0) {
				xcount = 0;
			}
			++xcount;
		}
		if (key[KEY_INPUT_UP] != 0 && jumpFlag == false) {
			if (y > 242) {
				y -= (int)(4 * move * isPower);
			}

			if (ycount > 0) {
				ycount = 0;
			}
			--ycount;
		}
		if (key[KEY_INPUT_DOWN] != 0 && jumpFlag == false) {
			if (y < 598) {
				y += (int)(4 * move * isPower);
			}

			if (ycount < 0) {
				ycount = 0;
			}
			++ycount;
		}
	}
	else {
		if (key[KEY_INPUT_LEFT] != 0) {
			if (x > 53) {
				x -= (int)(4 * move * isPower);
			}

			if (xcount > 0) {
				xcount = 0;
			}
			--xcount;
		}
		if (key[KEY_INPUT_RIGHT] != 0) {
			if (x < 686 || (x < 900 && y > 401 && y < 494)) {
				x += (int)(4 * move * isPower);
			}

			if (xcount < 0) {
				xcount = 0;
			}
			++xcount;
		}
		if (key[KEY_INPUT_UP] != 0 && jumpFlag == false) {
			if ((y > 242 && x < 690) || (y > 405 && x < 904)) {
				y -= (int)(4 * move * isPower);
			}

			if (ycount > 0) {
				ycount = 0;
			}
			--ycount;
		}
		if (key[KEY_INPUT_DOWN] != 0 && jumpFlag == false) {
			if ((y < 598 && x < 690) || (y < 490 && x < 894)) {
				y += (int)(4 * move * isPower);
			}

			if (ycount < 0) {
				ycount = 0;
			}
			++ycount;
		}
	}

	ix = abs(xcount) % 40 / 20;
	iy = abs(ycount) % 40 / 20;

	if (xcount > 0) {
		ix += 0;
		handleNumber = ix;
	}
	else if (xcount < 0) {
		ix += 6;
		handleNumber = ix;
	}
	if (ycount != 0) {
		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
			iy += 6;
		}

		handleNumber = iy;
	}
}

void Player_3::Attack() {
	handleNumber += 2;

	if (attackCount != 0) {
		--attackCount;
	}
	else {
		attackFlag = true;
		attackCount = 30;
		if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
			ax = x - 160;
			ay = y + 20;
		}
		else {
			ax = x + 160;
			ay = y + 20;
		}
	}
}

void Player_3::Jump() {
	if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
		handleNumber = 10;
	}
	else {
		handleNumber = 4;
	}

	if (jumpFlag == true) {
		y_temp = y;
		y += (y - y_prev) + 1;
		y_prev = y_temp;

		if (y == y_start) {
			jumpFlag = false;
		}
	}

	else {
		jumpFlag = true;
		y_start = y;
		y_prev = y;
		y = y - 17;
	}
}