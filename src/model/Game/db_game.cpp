#include "model/Game/db_game.h"

GameDB::GameDB(ConMySQL * msql) : sql_link(msql) {}

Game GameDB::read_game_from_id(int id) { 
	return Game(); 
}