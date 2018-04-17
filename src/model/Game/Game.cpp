#include "model/Game/Game.h"

Game::Game(int id) : id_game(id) {}
Game::Game() : id_game(-1) {}
Game::~Game() {}

int Game::getId() { return id_game; }
bool Game::setId(int new_id) {
	id_game = new_id;
	return true;
}

int Game::getIdPlayer1() { return id_player_1; }
bool Game::setIdPlayer1(int new_id) {
	id_player_1 = new_id;
	return true;
}

int Game::getIdPlayer2()  { return id_player_2; }
bool Game::setIdPlayer2(int new_id) {
	id_player_2 = new_id;
	return true;
}

float Game::getLevelPlayer1() { return level_player_1; };
bool Game::setLevelPlayer1(float new_level) {
	level_player_1 = new_level;
	return true;
}

float Game::getLevelPlayer2() { return level_player_2; };
bool Game::setLevelPlayer2(float new_level) {
	level_player_2 = new_level;
	return true;
}

int Game::getDateGame() { return date_game; };
bool Game::setDateGame(int new_timestamp) {
	date_game = new_timestamp;
	return true;
}

std::string Game::getMoves() { return moves; }
bool Game::setMoves(std::string new_moves) {
	moves = new_moves;
	return true;
}

std::string Game::to_json_string() {
    Json::Value val;
    
    val["id_game"] = id_game;
    val["id_player_1"] = id_player_1;
    val["id_player_2"] = id_player_2;
    val["level_player_1"] = level_player_1;
    val["level_player_2"] = level_player_2;
    val["date_game"] = date_game;
    val["moves"] = moves;

    return val.toStyledString();
}

Json::Value Game::to_json() {
	Json::Value val;

    val["id_game"] = id_game;
    val["id_player_1"] = id_player_1;
    val["id_player_2"] = id_player_2;
    val["level_player_1"] = level_player_1;
    val["level_player_2"] = level_player_2;
    val["date_game"] = date_game;
    val["moves"] = moves;

    return val;
}