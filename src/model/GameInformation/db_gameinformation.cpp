#include "model/GameInformation/db_gameinformation.h"

std::mutex GameInfoDB::mx;

GameInfoDB::GameInfoDB(ConMySQL * msql) : sql_link(msql) {}
GameInfoDB::~GameInfoDB() {}

std::vector<GameInformation> GameInfoDB::read_gameinfos_from_game_id(int id) { 
	std::cout << "db_gameinformation.cpp - Readind infos from game " << id << std::endl;		

	std::vector<GameInformation> ret;
	try {
		std::string req = "SELECT * FROM GAMESINFOS WHERE id_game=";
		req = req + std::to_string(id) + std::string(";");
		std::cout << "db_gameinformation.cpp - Executing : " << req << std::endl;

		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			GameInformation n;
			n.setId(r.get_link_result()->getInt("id_info"));
			n.setIdGame(r.get_link_result()->getInt("id_game"));
			n.setType(r.get_link_result()->getInt("type_info"));
			n.setValue(r.get_link_result()->getString("value_info"));
			ret.push_back(n);
		}
	}
	catch(...) {
		std::cout << "db_gameinformation.cpp - Unable to read infos for game " << id << std::endl;		
	}
	
	std::cout << "db_gameinformation.cpp - Reading infos from game " << id << " ended, returning the result" << std::endl;	
	return ret;
}

GameInformation GameInfoDB::create_game_info(int id_game, int type, std::string value) {
	GameInformation ret(-1);
	GameInfoDB::mx.lock();

	try {
		std::cout << "db_gameinformation.h - Creating DB request to create new game infos for game " << id_game << std::endl;
		std::string req = std::string("INSERT INTO GAMESINFOS (id_game, type_info, value_info) ");
		req = req + std::string("VALUES (") + std::to_string(id_game) + std::string(",") + std::to_string(type) + std::string(",");
		req = req + value + std::string(");");

		std::cout << "db_gameinformation.h - Creating DB request to create new game info : " << req << std::endl;

		sql_link->update(req);

		std::cout << "db_gameinformation.h - Query done, returning infos about the game" << std::endl;
		req = "SELECT * FROM GAMESINFOS ORDER BY id_game DESC LIMIT 1";
		ExecuteResult r2 = sql_link->execute(req);
		std::cout << "db_gameinformation.h - Query done, examining result" << std::endl;
		if (r2.get_link_result() == NULL) {
			std::cout << "db_gameinformation.h - Error in query return" << std::endl;
		}
		while(r2.get_link_result()->next()) {
			ret.setId(r2.get_link_result()->getInt("id_info"));
			ret.setIdGame(r2.get_link_result()->getInt("id_game"));
			ret.setType(r2.get_link_result()->getInt("type"));
			ret.setValue(r2.get_link_result()->getString("value_info"));
		}
		std::cout << "db_gameinformation.h - Infos about game information got and will be sent" << std::endl;
	}
	catch(...) {
		std::cout << "db_gameinformation.h - error when creating the game information" << std::endl;
	}

	GameInfoDB::mx.unlock();

	return ret;
}

GameInformation GameInfoDB::delete_game_infos_from_game_id(int id_game) {
	std::cout << "db_player.cpp - Deleting game infos for game " << id_game << std::endl;		
	GameInformation ret(-1);

	try {
		std::string req = "DELETE FROM GAMESINFOS WHERE id_game=";
		req = req + std::to_string(id_game);
		sql_link->update(req);
		ret.setIdGame(id_game);	
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to delete game infos for game " << id_game << std::endl;		
	}

	std::cout << "db_player.cpp - Deleting game infos for game " << id_game << " ended, returning the result" << std::endl;		
	return ret;	
}