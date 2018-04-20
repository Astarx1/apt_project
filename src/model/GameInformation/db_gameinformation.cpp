#include "model/GameInformation/db_gameinformation.h"

std::mutex PlayerDB::mx;

std::vector<GameInformation> GameInfoDB::read_gameinfos_from_game_id(int id) { 
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

GameInformation GameInfoDB::create_game_info(int id_game, int type, std::string value);
GameInformation GameInfoDB::delete_game_infos_from_game_id(int id_game);