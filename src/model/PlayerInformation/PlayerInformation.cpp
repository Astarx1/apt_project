#include "model/PlayerInformation/PlayerInformation.h"


PlayerInformation::PlayerInformation(int id) : id_player_information(id) {}
PlayerInformation::PlayerInformation() : id_player_information(-1) {}
PlayerInformation::~PlayerInformation() {}

int PlayerInformation::getId() {
    return id_player_information;
}
bool PlayerInformation::setId(int new_id) {
    id_player_information = new_id;
    return true;
}

int PlayerInformation::getIdPlayer() {
    return id_player;
}
bool PlayerInformation::setIdPlayer(int new_id) {
    id_player = new_id;
    return true;
}

int PlayerInformation::getType() {
    return type;
}
bool PlayerInformation::setType(int new_type) {
    type = new_type;
    return true;
}

std::string PlayerInformation::getValue() {
    return value;
}
bool PlayerInformation::setValue(std::string new_value) {
    value = new_value;
}

std::string PlayerInformation::to_json_string() {
    Json::Value val;
    
    val["id_player_information"] = id_player_information;
    val["id_player"] = id_player;
    val["type"] = type;
    val["value"] = value;

    return val.toStyledString();
}

Json::Value PlayerInformation::to_json() {
	Json::Value val;

    val["id_player_information"] = id_player_information;
    val["id_player"] = id_player;
    val["type"] = type;
    val["value"] = value;

    return val;
}