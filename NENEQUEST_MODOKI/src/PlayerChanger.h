#pragma once

typedef enum {
	ePlayer1,
	ePlayer2,
	ePlayer3,
	ePlayer4,
	ePlayerNone
} EPlayer;

class PlayerChanger {
public:
	virtual void ChangePlayer(EPlayer playerNext) = 0;
};