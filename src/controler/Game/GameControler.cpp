#include "controler/Game/GameControler.h"

GameControler::GameControler(ConMySQL * msql) : msql(msql), db(GameDB(msql)) {
	;
}

Game GameControler::create(int id_player_1, int id_player_2, std::string moves) {
	;
}
