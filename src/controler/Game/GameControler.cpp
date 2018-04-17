#include "controler/Game/GameControler.h"
#include "model/Player/db_player.h"

#include <ctime>

GameControler::GameControler(ConMySQL * msql) : msql(msql), db(GameDB(msql)) {
	;
}

Game GameControler::create(int id_player_1, int id_player_2, std::string moves) {
	int t = std::time(nullptr);
	PlayerDB pdb(msql);
	Player p1 = pdb.read_player_from_id(id_player_1);
	Player p2 = pdb.read_player_from_id(id_player_2);
	db.create_game(id_player_1, id_player_2, p1.getLevel(), p2.getLevel(), t, moves); 
}
