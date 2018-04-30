#include "model/PlayerInformation/db_playerinformation.h"

std::mutex PlayerInfoDB::mx;

PlayerInfoDB::PlayerInfoDB(ConMySQL * msql) : sql_link(msql) {}
PlayerInfoDB::~PlayerInfoDB() {}

std::vector<PlayerInformation> PlayerInfoDB::read_player_infos_from_player_id(int id) { 
	std::cout << "db_playerinformation.cpp - Readind infos from player " << id << std::endl;		

	std::vector<PlayerInformation> ret;
	try {
		std::string req = "SELECT * FROM PLAYERSINFOS WHERE id_player=";
		req = req + std::to_string(id);
		ExecuteResult r = sql_link->execute(req);

		while(r.get_link_result()->next()) {
			PlayerInformation n;
			n.setId(r.get_link_result()->getInt("id_info"));
			n.setIdPlayer(r.get_link_result()->getInt("id_player"));
			n.setType(r.get_link_result()->getInt("type"));
			n.setValue(r.get_link_result()->getString("value_info"));
		}
	}
	catch(...) {
		std::cout << "db_playerinformation.cpp - Unable to read infos for player " << id << std::endl;		
	}
	
	std::cout << "db_playerinformation.cpp - Reading infos from player " << id << " ended, returning the result" << std::endl;	
	return ret;
}

PlayerInformation PlayerInfoDB::create_player_info(int id_player, int type, std::string value) {
	PlayerInformation ret(-1);
	PlayerInfoDB::mx.lock();

	try {
		std::cout << "db_playerinformation.h - Creating DB request to create new player infos for player " << id_player << std::endl;
		std::string req = std::string("INSERT INTO PLAYERSINFOS (id_player, type, value_info) ");
		req = req + std::string("VALUES (") + std::to_string(id_player) + std::string(",") + std::to_string(type) + std::string(",");
		req = req + value + std::string(");");

		std::cout << "db_playerinformation.h - Creating DB request to create new player info : " << req << std::endl;

		sql_link->update(req);

		std::cout << "db_playerinformation.h - Query done, returning infos about the player " << std::endl;
		req = "SELECT * FROM PLAYERSSINFOS ORDER BY id_player DESC LIMIT 1";
		ExecuteResult r2 = sql_link->execute(req);
		std::cout << "db_playerinformation.h - Query done, examining result" << std::endl;
		if (r2.get_link_result() == NULL) {
			std::cout << "db_playerinformation.h - Error in query return" << std::endl;
		}
		while(r2.get_link_result()->next()) {
			ret.setId(r2.get_link_result()->getInt("id_info"));
			ret.setIdPlayer(r2.get_link_result()->getInt("id_player"));
			ret.setType(r2.get_link_result()->getInt("type"));
			ret.setValue(r2.get_link_result()->getString("value_info"));
		}
		std::cout << "db_playerinformation.h - Infos about player information got and will be sent" << std::endl;
	}
	catch(...) {
		std::cout << "db_playerinformation.h - error when creating the player information" << std::endl;
	}

	PlayerInfoDB::mx.unlock();

	return ret;
}

PlayerInformation PlayerInfoDB::delete_player_infos_from_player_id(int id_player) {
	std::cout << "db_player.cpp - Deleting player infos for player " << id_player << std::endl;		
	PlayerInformation ret(-1);

	try {
		std::string req = "DELETE FROM PLAYERSINFOS WHERE id_player=";
		req = req + std::to_string(id_player);
		sql_link->update(req);
		ret.setIdPlayer(id_player);	
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to delete player infos for player " << id_player << std::endl;		
	}

	std::cout << "db_player.cpp - Deleting player infos for player " << id_player << " ended, returning the result" << std::endl;		
	return ret;	
}

void PlayerInfoDB::update_info_value_from_info_id(int id, std::string value) {
	std::cout << "db_player.cpp - Updating info " << id << std::endl;		
	PlayerInformation ret(-1);

	try {
		std::string req = "UPDATE PLAYERSINFOS SET value=";
		req = req + value;
		req = req + " WHERE id_info=";
		req = req + std::to_string(id);
		sql_link->update(req);
		ret.setIdPlayer(id);	
	}
	catch(...) {
		std::cout << "db_player.cpp - Unable to update player infos " << id << std::endl;		
	}

	std::cout << "db_player.cpp - Updating player infos " << id << " ended, returning the result" << std::endl;		
}
