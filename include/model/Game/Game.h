#ifndef PLAYER_H
#define PLAYER_H

#include "usual.h"
#include <json/json.h>

class Game {
public:
	Game(int id);
	Game();
	~Game();

	int getId();
	bool setId(int new_id);

	std::string to_json_string();
	Json::Value to_json();
	
private:
	int id_game;
};

#endif