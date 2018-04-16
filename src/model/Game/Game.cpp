#include "model/Game/Game.h"

Game::Game(int id) : id_game(id) {}
Game::Game() : id_game(-1) {}
~Game::Game() {}

int Game::getId() { return id_game; }
bool Game::setId(int new_id) {
	id_game = new_id;
	return id_game;
}

std::string Game::to_json_string() {
    Json::Value val;
    
    val["id_game"] = id_player;

    return val.toStyledString();
}

Json::Value Game::to_json() {
	Json::Value val;

    val["id_game"] = id_game;

    return val;
}