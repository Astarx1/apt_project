#include "model/Player/Player.h"

Player::Player(int id) : id_player(id) {}
Player::Player() {}
Player::~Player() {}

int Player::getId() { return id_player; }
bool Player::setId(int new_id) { 
	id_player = new_id; 
	return true;
}

float Player::getLevel() { return current_level; }
bool Player::setLevel(float new_level) { 
	current_level = new_level; 
	return true;
}

std::string Player::getTrivia() { return trivia_player; }
bool Player::setTrivia(std::string new_trivia) { 
	trivia_player = new_trivia; 
	return true;
}

std::string Player::to_json_string() {
    Json::Value val;
    
    val["id_player"] = id_player;
    val["current_level"] = current_level;
    val["trivia_player"] = trivia_player;

    return val.toStyledString();
}

Json::Value Player::to_json() {
	Json::Value val;

    val["id_player"] = id_player;
    val["current_level"] = current_level;
    val["trivia_player"] = trivia_player;

    return val;
}