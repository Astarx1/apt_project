#include "controler/Player/PlayerControler.h"
#include "model/PlayerInformation/PlayerInformation.h"
#include "model/PlayerInformation/db_playerinformation.h"

PlayerControler::PlayerControler(ConMySQL * msql) : msql(msql), db(PlayerDB(msql)) {
	;
}

Player PlayerControler::create() {
	std::cout << "PlayerControler.cpp - Controling creation of a player" << std::endl;
	Player t = db.create_player();
	std::cout << "PlayerControler.cpp - Controling creation of players ended, returning the result" << std::endl;

	return t;		
}

std::vector<Player> PlayerControler::get() {
	std::cout << "PlayerControler.cpp - Controling get all players" << std::endl;
	std::vector<Player> t = db.read_players();
	std::cout << "PlayerControler.cpp - Controling read for all players ended, returning the result" << std::endl;

	return t;
}

Player PlayerControler::read_from_id(int id) {
	std::cout << "PlayerControler.cpp - Controling read for player id " << id << std::endl;
	Player t = db.read_player_from_id(id);
	std::cout << "PlayerControler.cpp - Controling read for player id " << id << " ended, returning the result" << std::endl;
	return t;
}

Player PlayerControler::delete_from_id(int id){
	std::cout << "PlayerControler.cpp - Controling read for player id " << id << std::endl;
	Player t = db.delete_player_from_id(id);	
	std::cout << "PlayerControler.cpp - Controling read for player id " << id << " ended, returning the result" << std::endl;
	return t;
}

Player PlayerControler::update_name(int id_player, std::string name){
	std::cout << "PlayerControler.cpp - Controling read for player id " << id_player << std::endl;

	PlayerInfoDB pidb(msql);
	std::vector<PlayerInformation> vpi = pidb.read_player_infos_from_player_id(id_player);
	
	int id = -1;
	for (unsigned int i = 0; i < vpi.size(); ++i)
		if (vpi[i].getType() == 0)
			id = i;
	
	if (id > 0) {
		pidb.update_info_value_from_info_id(id, name);
	}
	else {
		pidb.create_player_info(id_player, 0, name);
	}

	Player t = db.read_player_from_id(id);	

	std::cout << "PlayerControler.cpp - Controling read for player id " << id << " ended, returning the result" << std::endl;
	return t;
}
