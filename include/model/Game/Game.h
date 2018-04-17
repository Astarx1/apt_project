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

	int getIdPlayer1();
	bool setIdPlayer1(int new_id);

	int getIdPlayer2();
	bool setIdPlayer2(int new_id);

	float getLevelPlayer1();
	bool setLevelPlayer1(float new_level);

	float getLevelPlayer2();
	bool setLevelPlayer2(float new_level);

	int getDateGame();
	bool setDateGame(int new_timestamp);

	std::string getMoves();
	bool setMoves(std::string new_moves);

	std::string to_json_string();
	Json::Value to_json();
	
private:
	int id_game;
	int id_player_1;
	int id_player_2;
	float level_player_1;
	float level_player_2;
	int date_game;
	std::string moves;
};

#endif