#include "model/GameInformation/GameInformation.h"


GameInformation::GameInformation();
GameInformation::~GameInformation();

int GameInformation::getId() {
    return id_game_information;
}
bool GameInformation::setId(int new_id) {
    id_game_information = new_id;
    return true;
}

int GameInformation::getIdGame() {
    return id_game;
}
bool GameInformation::setIdGame(int new_id) {
    id_game = new_id;
    return true;
}

int GameInformation::getType() {
    return type;
}
bool GameInformation::setType(in new_type) {
    type = new_type;
    return true;
}

int GameInformation::getValue() {
    return value;
}
bool GameInformation::setValue(std::string new_value) {
    value = new_value;
}

std::string GameInformation::to_json_string() {
    Json::Value val;
    
    val["id_game_information"] = id_game_information;
    val["id_game"] = id_game;
    val["type"] = type;
    val["value"] = value;

    return val.toStyledString();
}

Json::Value Player::to_json() {
	Json::Value val;

    val["id_game_information"] = id_game_information;
    val["id_game"] = id_game;
    val["type"] = type;
    val["value"] = value;

    return val;
}