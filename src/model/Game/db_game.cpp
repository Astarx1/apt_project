#include "model/Game/db_game.h"

std::mutex GameDB::mx;

GameDB::GameDB(ConMySQL * msql) : sql_link(msql) {}

std::vector<Game> GameDB::read_games() {
	std::cout << "db_player.cpp - Readind from games" << std::endl;		

	std::vector<Game> ret;
	try {
		std::string req = "SELECT * FROM GAMES";
		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			Game g;
			g.setId(r.get_link_result()->getInt("id_game"));
			g.setIdPlayer1(r.get_link_result()->getInt("id_player_1"));
			g.setIdPlayer2(r.get_link_result()->getInt("id_player_2"));
			g.setLevelPlayer1(r.get_link_result()->getDouble("level_player_1"));
			g.setLevelPlayer2(r.get_link_result()->getDouble("level_player_2"));
			g.setDateGame(r.get_link_result()->getInt("date_game"));
			g.setMoves(r.get_link_result()->getString("moves"));
			ret.push_back(g);
		}
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to read games" << std::endl;		
	}
	
	std::cout << "db_player.cpp - Reading from games ended, returning the result" << std::endl;	
	return ret;
}

Game GameDB::read_game_from_id(int id) { 
	std::cout << "db_player.cpp - Readind from game " << id << std::endl;		

	Game ret(-1);
	try {
		std::string req = "SELECT * FROM GAMES WHERE id_game=";
		req = req + std::to_string(id);
		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			ret.setId(r.get_link_result()->getInt("id_game"));
			ret.setIdPlayer1(r.get_link_result()->getInt("id_player_1"));
			ret.setIdPlayer2(r.get_link_result()->getInt("id_player_2"));
			ret.setLevelPlayer1(r.get_link_result()->getDouble("level_player_1"));
			ret.setLevelPlayer2(r.get_link_result()->getDouble("level_player_2"));
			ret.setDateGame(r.get_link_result()->getInt("date_game"));
			ret.setMoves(r.get_link_result()->getString("moves"));
		}
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to read game " << id << std::endl;		
	}
	
	std::cout << "db_player.cpp - Reading from game " << id << " ended, returning the result" << std::endl;	
	return ret;
}

Game GameDB::create_game(int id_player_1, int id_player_2, float level_player_1, float level_player_2, int date_game, std::string moves) {
	Game ret(-1);
	GameDB::mx.lock();

	try {
		std::cout << "db_player.h - Creating DB request to create new game" << std::endl;
		std::string req = std::string("INSERT INTO GAMES (id_player_1, level_player_1, id_player_2, level_player_2, date_game, moves) ");
		req = req + std::string("VALUES (") + std::to_string(id_player_1) + std::string(",") + std::to_string(id_player_2) + std::string(",");
		req = req + std::to_string(level_player_1) + std::string(",") + std::to_string(level_player_2) + std::string(",");
		req = req + std::to_string(date_game) + std::string(",") + moves + std::string(");");

		std::cout << "db_player.h - Creating DB request to create new game : " << req << std::endl;

		sql_link->update(req);

		std::cout << "db_player.h - Query done, returning infos about the game" << std::endl;
		req = "SELECT * FROM GAMES ORDER BY id_game DESC LIMIT 1";
		ExecuteResult r2 = sql_link->execute(req);
		std::cout << "db_player.h - Query done, examining result" << std::endl;
		if (r2.get_link_result() == NULL) {
			std::cout << "db_player.h - Error in query return" << std::endl;
		}
		while(r2.get_link_result()->next()) {
			ret.setId(r2.get_link_result()->getInt("id_game"));
			ret.setIdPlayer1(r2.get_link_result()->getInt("id_player_1"));
			ret.setIdPlayer2(r2.get_link_result()->getInt("id_player_2"));
			ret.setLevelPlayer1(r2.get_link_result()->getDouble("level_player_1"));
			ret.setLevelPlayer2(r2.get_link_result()->getDouble("level_player_2"));
			ret.setDateGame(r2.get_link_result()->getInt("date_game"));
			ret.setMoves(r2.get_link_result()->getString("moves"));
		}
		std::cout << "db_player.h - Infos about game got and will be sent" << std::endl;
	}
	catch(...) {
		std::cout << "db_player.h - error when creating the game" << std::endl;
	}

	GameDB::mx.unlock();

	return ret;
}

Game GameDB::delete_game_from_game_id(int id_game) {
	std::cout << "db_player.cpp - Deleting game " << id_game << std::endl;		
	Game ret(-1);

	try {
		std::string req = "DELETE FROM GAMES WHERE id_game=";
		req = req + std::to_string(id_game);
		sql_link->update(req);
		ret.setId(id_game);	
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to delete game" << id_game << std::endl;		
	}

	std::cout << "db_player.cpp - Deleting game " << id_game << " ended, returning the result" << std::endl;		
	return ret;	
}
