#ifndef DB_PLAYER_H
#define DB_PLAYER_H

#include "usual.h"
#include "Player.h"

class PlayerDB {
public:
	Player read_player_from_id(int id) {
		std::string req = "SELECT * FROM PLAYERS WHERE id_player=";
		req = req << id;
		ExecuteResult r = sql_link->execute(req);
		return Player(0);
	}

	void create_player() {
		std::string req = "INSERT INTO PLAYERS (id_player, current_level, trivia_player) VALUES (,1000,'none')";
		ExecuteResult r = sql_link->execute(req);
	}

private:
	ConMySQL * sql_link;
}

#endif