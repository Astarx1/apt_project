#ifndef DB_PLAYER_H
#define DB_PLAYER_H

#include <mutex>

#include "usual.h"
#include "model/MySQLLink.h"
#include "model/ExecuteResult.h"
#include "Player.h"

class PlayerDB {
public:
	static std::mutex mx;
	PlayerDB(ConMySQL * msql) : sql_link(msql) 
	{}

	Player read_player_from_id(int id);
	Player create_player();
	Player delete_player_from_id(int id);
	std::vector<Player> read_players();

private:
	ConMySQL * sql_link;
};

#endif
