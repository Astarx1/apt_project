#ifndef GAMEINFORMATION_H
#define GAMEINFORMATION_H

#include "usual.h"
#include <json/json.h>

class GameInformation {
public:
	GameInformation();
	~GameInformation();

	int getId();
	bool setId(int new_id);

	int getIdGame();
	bool setIdGame(int new_id);

	int getType();
	bool setType(in new_type);

	int getValue();
	bool setValue(std::string new_value);

	std::string to_json_string();
	Json::Value to_json();
	
private:
	int id_game_information;
	int id_game;
	int type;
	std::string value;
};

#endif