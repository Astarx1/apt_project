#ifndef PLAYER_H
#define PLAYER_H

#include "usual.h"

class Player {
public:
	Player(int id) : id(id_player) {}
	~Player() {}
private:
	int id_player;
	float current_level;
	std::string trivia_player;
}

#endif