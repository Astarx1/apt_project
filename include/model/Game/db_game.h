#ifndef DB_GAME_H
#define DB_GAME_H

#include <mutex>

#include "usual.h"
#include "model/MySQLLink.h"
#include "model/ExecuteResult.h"
#include "model/Game/Game.h"

class GameDB {
public:
	static std::mutex mx;
	GameDB(ConMySQL * msql);

	Game read_game_from_id(int id);
	Game create_game(int id_player_1, int id_player_2, float level_player_1, float level_player_2, int date_game, std::string moves) ; 

private:
	ConMySQL * sql_link;
};

#endif