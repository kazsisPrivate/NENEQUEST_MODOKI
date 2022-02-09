
#include "Player_4.h"
#include "DxLib.h"
#include "HitJudge0.h"
#include "HitJudge1.h"
#include "HitJudge2.h"
#include "PlayerData.h"
#include "PowerBox.h"


Player_4::Player_4(PlayerChanger* changer) : Player(changer, CharaGraphics::GetGraHandle(0, 4)) {
}

void Player_4::Initialize() {
	HitJudge0::Initialize();
	HitJudge1::Initialize();
	HitJudge2::Initialize();
	PowerBox::SetPlPower(1);
	x = PlayerData::GetPlayerX(), y = PlayerData::GetPlayerY();
	hp = PlayerData::GetPlayerHP();
	ax = x + 160;
	ay = y + 20;
	hitRangeX = 33, hitRangeY = 60;
	hitRangeAX = 45, hitRangeAY = 60;
	sizeX = 500, sizeY = 283;
	//LoadDivGraph("images/player_4-1-1.png", 32, 2, 16, sizeX, sizeY, charaHandle);
	//charaHandle = GetGraph(0, 4, charaHandle);
	xcount = 0, ycount = 0;
	attackCount = 0;
	godCount = -1;
	jumpFlag = false;
	preAttackFlagS = false;
	preAttackFlagD = false;
	godFlag = false;
	arrow = new Arrow();
	arrow->Initialize();
	attackFlag = false;
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

void Player_4::Finalize() {
	/*for (int i = 0; i < 32; i++) {
		DeleteGraph(charaHandle[i]);
	}*/
	DeleteGraph(effectHandle);

	delete arrow;
}

void Player_4::Update() {
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
			if (weaponNum != 4 && weaponNum != 5 && weaponNum != 6) {
				if (weaponNum == 1) {
					mPlayerChanger->ChangePlayer(ePlayer_1);
				}
				else if (weaponNum == 2) {
					mPlayerChanger->ChangePlayer(ePlayer_2);
				}
				else {
					mPlayerChanger->ChangePlayer(ePlayer_3);
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
				if ((handleNumber > 7 && handleNumber < 16) || handleNumber > 23) {
					handleNumber = 8;
				}
				else {
					handleNumber = 0;
				}
			}

			Speed(); //playerの行う動作に適した速度に設定

			if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0 || key[KEY_INPUT_UP] != 0 || key[KEY_INPUT_DOWN] != 0) {
				Walk();
			}

			attackFlag = arrow->GetArrowFlag();

			if (attackCount == 0 && (jumpFlag == true || key[KEY_INPUT_A] == 1)) {
				Jump();
			}
			else if (attackCount != 0) { //attackCount > attackFlagがfalseになるのにかかる時間　ということが条件
				Attack();

				if (attackFlag == true) {
					arrow->Update();
				}
			}
			else if ((key[KEY_INPUT_S] == 1 || preAttackFlagS == true) && preAttackFlagD == false) { //この条件なら再びkey[KEY_INPUT_S] == 0に戻ったときに矢を放つ（attackFlag = true）の処理をさせることができる
				PreAttackS();
			}
			else if (key[KEY_INPUT_D] == 1 || preAttackFlagD == true) {
				PreAttackD();
			}

			PlayerData::SetPlayerXY(x, y);

			HitJudge();
		}
	}
}

void Player_4::Draw() {
	if (godFlag == true) {
		if (godCount == -1) {
			godFlag = false;
		}
		else if (godCount > 80 || (godCount <= 60 && godCount > 40) || godCount <= 20) {
			handleNumber += 16;
			--godCount;
		}
		else {
			--godCount;
		}
	}
	DrawGraph(x - sizeX / 2, y - sizeY / 2 - 13, charaHandle[handleNumber], TRUE);
	//DrawBox(ax - 45, ay - 60, ax + 45, ay + 60, GetColor(0, 0, 0), TRUE);
	//DrawBox(x - hitRangeX, y - hitRangeY, x + hitRangeX, y + hitRangeY, GetColor(0, 0, 0), TRUE);

	if (attackFlag == true) {
		arrow->Draw();
	}

	if (isPower != 1 || iPower != 1) {
		DrawGraph(x - 114, y - 113, effectHandle, TRUE);
	}

	//DrawFormatString(100, 200, GetColor(255, 255, 255), "ys = %d", HitJudge0::playerALX);
	//DrawFormatString(100, 300, GetColor(255, 255, 255), "px = %d, ex = %d", HitJudge0::enemyALX1, x);
}

void Player_4::Speed() {
	if (key[KEY_INPUT_LEFT] != 0 || key[KEY_INPUT_RIGHT] != 0) {
		if (jumpFlag == true) {
			move = 0.8f;
		}
		else if (attackCount != 0 || preAttackFlagS == true || preAttackFlagD == true) {
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
		if (attackCount != 0 || preAttackFlagS == true || preAttackFlagD == true) {
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

void Player_4::Walk() {
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
		ix += 8;
		handleNumber = ix;
	}
	if (ycount != 0) {
		if ((handleNumber > 7 && handleNumber < 16) || handleNumber > 23) {
			iy += 8;
		}

		handleNumber = iy;
	}

}

void Player_4::Attack() {
	handleNumber += 4;

	--attackCount;
}

void Player_4::Jump() {
	if ((handleNumber > 7 && handleNumber < 16) || handleNumber > 23) {
		handleNumber = 14;
	}
	else {
		handleNumber = 6;
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

void Player_4::PreAttackS() {
	handleNumber += 2;

	if (key[KEY_INPUT_S] == 1) {
		preAttackFlagS = true;
	}

	if (key[KEY_INPUT_S] == 0) {
		if ((handleNumber > 7 && handleNumber < 16) || handleNumber > 23) {
			ax = x - 20;
			ay = y + 20;

			arrow->StartArrow(ax, ay, 2);
		}
		else {
			ax = x + 20;
			ay = y + 20;

			arrow->StartArrow(ax, ay, 1);
		}

		preAttackFlagS = false;
		attackCount = 90; //矢を放った後の硬直する時間も含んでいる
	}
}

void Player_4::PreAttackD() {
	handleNumber += 2;

	if (key[KEY_INPUT_D] == 1) {
		preAttackFlagD = true;
	}

	if (key[KEY_INPUT_D] == 0) {
		if ((handleNumber > 7 && handleNumber < 16) || handleNumber > 23) {
			ax = x - 20;
			ay = y + 20;

			arrow->StartArrow(ax, ay, 4);
		}
		else {
			ax = x + 20;
			ay = y + 20;

			arrow->StartArrow(ax, ay, 3);
		}

		preAttackFlagD = false;
		attackCount = 120;
	}
}

void Player_4::HitJudge() {
	HitJudge0::SetPlRange(x, y, hitRangeX, hitRangeY);
	HitJudge1::SetPlRange(x, y, hitRangeX, hitRangeY);
	HitJudge2::SetPlRange(x, y, hitRangeX, hitRangeY);

	if (godFlag == false) {
		eneJudge0 = HitJudge0::PEJudge();
		eneJudge1 = HitJudge1::PEJudge();
		eneJudge2 = HitJudge2::PEJudge();
		eneAJudge0 = HitJudge0::EaPJudge();
		eneAJudge1 = HitJudge1::EaPJudge();
		eneAJudge2 = HitJudge2::EaPJudge();
	}

	if (icount == 1) {
		iJudge0 = false;
		iJudge1 = false;
		icount++;
	}
	else if (icount == 2) {
		icount = 0;
	}
	else {
		iJudge0 = HitJudge0::PIJudge();
		iJudge1 = HitJudge1::PIJudge();
	}

	if (iJudge0 == true || iJudge1 == true) {
		if (iJudge0 == true) {
			weaponNum = PowerBox::GetWpn0Num();

			if (weaponNum == 6) { //6は自強化系のItemを表す
				iPower = PowerBox::GetIPower0();
				isPower = PowerBox::GetISPower0();
			}

			ihPower = PowerBox::GetIHPower0();
		}
		else {
			weaponNum = PowerBox::GetWpn1Num();

			if (weaponNum == 6) { //6は自強化系のItemを表す
				iPower = PowerBox::GetIPower1();
				isPower = PowerBox::GetISPower1();
			}

			ihPower = PowerBox::GetIHPower1();
		}

		hp = hp + ihPower;
		if (hp < 0) {
			hp = 0;
		}
		else if (hp > 10) {
			hp = 10;
		}
		PlayerData::SetPlayerHP(hp);

		if (isPower != 1 && weaponNum == 6) {
			iscount = 600;

			if (isPower == 2) {
				effectHandle = LoadGraph("images/effect_1.png");
			}
			else {
				isPower = 0.5;
				effectHandle = LoadGraph("images/effect_2.png");
			}
		}
		else if (iPower != 1 && weaponNum == 6) {
			ipcount = 600;
			PowerBox::SetPlPower(iPower);
			effectHandle = LoadGraph("images/effect_3.png");
		}

		icount++;
	}

	if (eneJudge0 == true || eneJudge1 == true || eneJudge2 == true || eneAJudge0 == true || eneAJudge1 == true || eneAJudge2 == true) {
		if (eneJudge0 == true) {
			enePower = PowerBox::GetEnePower0();
			eneJudge0 = false;
		}
		else if (eneJudge1 == true) {
			enePower = PowerBox::GetEnePower1();
			eneJudge1 = false;
		}
		else if (eneJudge2 == true) {
			enePower = PowerBox::GetEnePower2();
			eneJudge2 = false;
		}
		else if (eneAJudge0 == true) {
			enePower = PowerBox::GetEneAPower0();
			eneAJudge0 = false;
		}
		else if (eneAJudge1 == true) {
			enePower = PowerBox::GetEneAPower1();
			eneAJudge1 = false;
		}
		else {
			enePower = PowerBox::GetEneAPower2();
			eneAJudge2 = false;
		}

		hp = hp - enePower;
		if (hp < 0) {
			hp = 0;
		}
		else if (hp > 10) {
			hp = 10;
		}
		PlayerData::SetPlayerHP(hp);
		godCount = 100;
		godFlag = true;
	}
}

void Player_4::BossStart() {

	attackFlag = arrow->GetArrowFlag();

	if (attackFlag == true) {
		arrow->Update();
	}

	prev_x = x;
	prev_y = y;
	prev_xcount = xcount;
	prev_ycount = ycount;

	if (x > 353) {
		x -= 2;

		/*if (xcount > 0) {
		xcount = 0;
		}*/
		--xcount;
	}
	if (x < 349) {
		x += 2;

		/*if (xcount < 0) {
		xcount = 0;
		}*/
		++xcount;
	}
	if (y > 453) {
		y -= 2;

		/*if (ycount > 0) {
		ycount = 0;
		}*/
		--ycount;
	}
	if (y < 449) {
		prev_y = y;
		y += 2;

		/*if (ycount < 0) {
		ycount = 0;
		}*/
		++ycount;
	}


	if (y == prev_y && x == prev_x) {
		handleNumber = 0;
	}
	else {
		if (xcount != prev_xcount) {
			ix = abs(xcount) % 40 / 20;

			if (xcount > 0) {
				ix += 0;
				handleNumber = ix;
			}
			else if (xcount < 0) {
				ix += 8;
				handleNumber = ix;
			}
		}

		if (prev_ycount != prev_ycount && ycount != 0) {
			if ((handleNumber > 5 && handleNumber < 12) || handleNumber > 17) {
				iy += 8;
			}

			handleNumber = iy;
		}
	}

	PlayerData::SetBscount(bscount + 1);
	bscount++;
}