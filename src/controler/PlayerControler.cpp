#include "controler/Player/PlayerControler.h"

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
	return db.delete_player_from_id(id);	
}