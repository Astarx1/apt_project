#ifndef PLAYER_H
#define PLAYER_H

#include "usual.h"
#include <json/json.h>

class Player {
public:
	Player(int id) : id_player(id) {}
	Player() {}
	~Player() {}

	int getId() { return id_player; }
	bool setId(int new_id) { id_player = new_id; }

	float getLevel() { return current_level; }
	bool setLevel(float new_level) { current_level = new_level; }

	std::string getTrivia() { return trivia_player; }
	bool setTrivia(std::string new_trivia) { trivia_player = new_trivia; }

	std::string to_json_string() {
	    Json::Value val;
	    val["id_player"] = id_player;
	    return val.toStyledString();
	}

	Json::Value to_json() {
		Json::Value val;
	    val["id_player"] = id_player;
	    return val;
	}
private:
	int id_player;
	float current_level;
	std::string trivia_player;
};

#endif
