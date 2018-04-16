#ifndef PLAYER_H
#define PLAYER_H

#include "usual.h"
#include <json/json.h>

class Player {
public:
	Player(int id);
	Player();
	~Player();

	int getId();
	bool setId(int new_id);

	float getLevel();
	bool setLevel(float new_level);

	std::string getTrivia();
	bool setTrivia(std::string new_trivia);

	std::string to_json_string();
	Json::Value to_json();
	
private:
	int id_player;
	float current_level;
	std::string trivia_player;
};

#endif
