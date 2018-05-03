#include "model/Player/db_player.h"

std::mutex PlayerDB::mx;

Player PlayerDB::create_player() {
	Player p(0);
	PlayerDB::mx.lock();
	try {
		std::cout << "db_player.h - Sending DB request to create new player" << std::endl;
		std::string req = "INSERT INTO PLAYERS (current_level, trivia_player) VALUES (1000,'none')";
		sql_link->update(req);

		std::cout << "db_player.h - Query done, returning infos about the player" << std::endl;
		req = "SELECT id_player FROM PLAYERS ORDER BY id_player DESC LIMIT 1";
		ExecuteResult r2 = sql_link->execute(req);
		std::cout << "db_player.h - Query done, examining result" << std::endl;
		if (r2.get_link_result() == NULL) {
			std::cout << "db_player.h - Error in query return" << std::endl;
		}
		while(r2.get_link_result()->next()) {
			std::cout << "db_player.h - Attributing the ID " << r2.get_link_result()->getInt("id_player") << " from " << r2.get_link_result() << std::endl;
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
	std::cout << "db_player.cpp - Reading all players" << std::endl;

	std::vector<Player> players;
	
	try {
		std::string req = "SELECT * FROM PLAYERS";
		ExecuteResult r = sql_link->execute(req);
		Player tmp;
		while(r.get_link_result()->next()) {
			tmp.setId(r.get_link_result()->getInt("id_player"));
			tmp.setLevel(r.get_link_result()->getDouble("current_level"));
			tmp.setTrivia(r.get_link_result()->getString("trivia_player"));
			players.push_back(tmp);
		}
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to read all players" << std::endl;
	}

	std::cout << "db_player.cpp - Read of all players ended" << std::endl;

	return players;
}

Player PlayerDB::read_player_from_id(int id) {
	std::cout << "db_player.cpp - Readind from player " << id << std::endl;		

	Player ret(-1);
	try {
		std::string req = "SELECT * FROM PLAYERS WHERE id_player=";
		req = req + std::to_string(id);
		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			ret.setId(r.get_link_result()->getInt("id_player"));
			ret.setLevel(r.get_link_result()->getDouble("current_level"));
			ret.setTrivia(r.get_link_result()->getString("trivia_player"));
		}
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to read player" << id << std::endl;		
	}
	
	std::cout << "db_player.cpp - Readind from player " << id << " ended, returning the result" << std::endl;		
	return ret;
}


Player PlayerDB::update_player(Player p){
	std::cout << "db_player.cpp - Updating player " << p.getId() << std::endl;		

	Player ret;
	PlayerDB::mx.lock();
	try {
		std::cout << "db_player.cpp - Checking the player exists ..." << std::endl;
		std::string req = "SELECT * FROM PLAYERS WHERE id_player=";
		req = req + std::to_string(p.getId());
		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			ret.setId(r.get_link_result()->getInt("id_player")); 
		}

		if (ret.getId() >= 0) {
			std::cout << "db_player.cpp - Updating the player..." << std::endl;
			std::string req = "UPDATE PLAYERS SET current_level=";
			req += std::to_string(p.getLevel()) + std::string(", trivia_player='") + p.getTrivia(); 
			req += std::string("' WHERE id_player=") + std::to_string(p.getId()) + std::string(";");
			sql_link->update(req);
			ret = p;
		}
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to update player" << p.getId() << std::endl;		
	}
	
	PlayerDB::mx.unlock();
	std::cout << "db_player.cpp - Readind from player " << p.getId() << " ended, returning the result" << std::endl;		
	return ret;
}

Player PlayerDB::delete_player_from_id(int id) {
	std::cout << "db_player.cpp - Deleting player " << id << std::endl;		
	Player ret(-1);

	try {
		std::string req = "DELETE FROM PLAYERS WHERE id_player=";
		req = req + std::to_string(id);
		sql_link->update(req);	
		ret.setId(id);
		ret.setLevel(0);
		ret.setTrivia("none");
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to delete player" << id << std::endl;		
	}

	std::cout << "db_player.cpp - Deleting player " << id << " ended, returning the result" << std::endl;		
	return ret;	
}
