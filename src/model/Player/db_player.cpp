#include "model/Player/db_player.h"

std::mutex PlayerDB::mx;

Player PlayerDB::create_player() {
	Player p(0);
	PlayerDB::mx.lock();
	try {
		std::string req = "INSERT INTO PLAYERS (current_level, trivia_player) VALUES (1000,'none')";
		ExecuteResult r = sql_link->execute(req);
		std::cout << "db_player.h - Query done, returning infos about the player" << std::endl;
		req = "SELECT id_player FROM PLAYERS ORDER BY id_player DESC LIMIT 1";
		ExecuteResult r2 = sql_link->execute(req);
		std::cout << "db_player.h - Query done, examining result" << std::endl;
		if (r2.get_link_result() == NULL) {
			std::cout << "db_player.h - Error in query return" << std::endl;
		}
		while(r2.get_link_result()->next()) {
			std::cout << "db_player.h - Attributing the ID " << r2.get_link_result()->getInt("id_player") << std::endl;
			p.setId(r2.get_link_result()->getInt("id_player"));
		}
		std::cout << "db_player.h - Infos about player got and will be sent" << std::endl;
	}
	catch(...) {
		std::cout << "db_player.h - error when creating the player" << std::endl;
	}
	PlayerDB::mx.unlock();

	return p;
}

std::vector<Player> PlayerDB::read_players() {
	std::vector<Player> players;
	
	try {
		std::string req = "SELECT * FROM PLAYERS";
		ExecuteResult r = sql_link->execute(req);
		while(r.get_link_result()->next()) {
			Player tmp;
			tmp.setId(r.get_link_result()->getInt("id_player"));
			tmp.setLevel(r.get_link_result()->getDouble("current_level"));
			tmp.setTrivia(r.get_link_result()->getString("trivia_player"));
			players.push_back(tmp);
		}
	}
	catch(...) {
		std::cout << "Unable to read all players" << std::endl;
	}

	return players;
}

Player PlayerDB::read_player_from_id(int id) {
	std::string req = "SELECT * FROM PLAYERS WHERE id_player=";
	req = req + std::to_string(id);
	ExecuteResult r = sql_link->execute(req);
	return Player(0);
}