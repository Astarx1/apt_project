#include "controler/Player/PlayerControler.h"

PlayerControler::PlayerControler(ConMySQL * msql) : msql(msql), db(PlayerDB(msql)) {
	;
}

Player PlayerControler::create() {
	return db.create_player();		
}

std::vector<Player> PlayerControler::get() {
	return db.read_players();
}

Player PlayerControler::read_from_id(int id) {
	return db.read_player_from_id(id);
}

Player PlayerControler::delete_from_id(int id){
	return db.delete_player_from_id(id);	
}