#pragma once

#include "Player.h"
#include "UpdateKey.h"
#include "Arrow.h"

class Player_4 : public UpdateKey, Player {
public:
	Player_4(PlayerChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Speed() override;
	void Walk() override;
	void Jump() override;
	void Attack() override;
	void PreAttackS(); //�|����Ђ��Ă͂��邪�܂��������Ă��Ȃ���Ԃ̂Ƃ�
	void PreAttackD();
	void HitJudge() override; //Player_4�ɂ����Ă̂ݍU���̓����蔻��̎������قȂ邽��
	void BossStart() override;

private:
	Arrow* arrow;
	//int charaHandle[32];
	bool preAttackFlagS; //�����O�̏�Ԃł���Ƃ��i�L�[����w�𗣂��Ζ����Ă��Ԃ̂Ƃ��jtrue
	bool preAttackFlagD;
};