#include "controler/Game/GameControler.h"
#include "model/Player/db_player.h"

#include <ctime>

GameControler::GameControler(ConMySQL * msql) : msql(msql), db(GameDB(msql)) {
	;
}

Game GameControler::create(int id_player_1, int id_player_2, std::string moves) {
    std::cout << "GameControler.cpp - Getting informations about time..." << std::endl; 
	int t = std::time(nullptr);
	
	PlayerDB pdb(msql);
    std::cout << "GameControler.cpp - Getting informations about player 1..." << std::endl; 
	Player p1 = pdb.read_player_from_id(id_player_1);
    std::cout << "GameControler.cpp - Getting informations about player 2..." << std::endl; 
	Player p2 = pdb.read_player_from_id(id_player_2);
    
    std::cout << "GameControler.cpp - creating the game..." << std::endl; 
	Game d = db.create_game(id_player_1, id_player_2, p1.getLevel(), p2.getLevel(), t, moves); 
    
    std::cout << "GameControler.cpp - Game creation ended, return values" << std::endl; 
    return d;
}
