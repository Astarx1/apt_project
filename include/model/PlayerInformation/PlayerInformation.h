#ifndef PLAYERINFORMATION_H
#define PLAYERINFORMATION_H

#include "usual.h"
#include <json/json.h>

class PlayerInformation {
public:
	PlayerInformation();
	PlayerInformation(int id);
	~PlayerInformation();

	int getId();
	bool setId(int new_id);

	int getIdPlayer();
	bool setIdPlayer(int new_id);

	int getType();
	bool setType(int new_type);

	std::string getValue();
	bool setValue(std::string new_value);

	std::string to_json_string();
	Json::Value to_json();
	
private:
	int id_player_information;
	int id_player;
	int type;
	std::string value;
};

#endif