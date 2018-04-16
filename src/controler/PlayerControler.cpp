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