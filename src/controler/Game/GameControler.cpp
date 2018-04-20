#include "controler/Game/GameControler.h"

#include "model/Game/db_game.h"
#include "model/GameInformation/db_gameinformation.h"
#include "model/Player/db_player.h"

#include <ctime>

GameControler::GameControler(ConMySQL * msql) : msql(msql) {
	;
}


std::vector<Game> PlayerControler::get() {
	std::cout << "GameControler.cpp - Controling get all players" << std::endl;
    GameDB game_db(msql);
	std::vector<Game> t = game_db.read_games();
	std::cout << "GameControler.cpp - Controling read for all players ended, returning the result" << std::endl;

	return t;
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
    GameDB game_db(msql);
	Game d = game_db.create_game(id_player_1, id_player_2, p1.getLevel(), p2.getLevel(), t, moves); 
    
    std::cout << "GameControler.cpp - Game creation ended, return values" << std::endl; 
    return d;
}


Game GameControler::create(int id_player_1, int id_player_2, std::string moves, int winner) {
    std::cout << "GameControler.cpp - Getting informations about time..." << std::endl; 
	int t = std::time(nullptr);
	
	PlayerDB pdb(msql);
    std::cout << "GameControler.cpp - Getting informations about player 1..." << std::endl; 
	Player p1 = pdb.read_player_from_id(id_player_1);
    std::cout << "GameControler.cpp - Getting informations about player 2..." << std::endl; 
	Player p2 = pdb.read_player_from_id(id_player_2);
    
    std::cout << "GameControler.cpp - creating the game..." << std::endl; 
    GameDB game_db(msql);
	Game d = game_db.create_game(id_player_1, id_player_2, p1.getLevel(), p2.getLevel(), t, moves); 
    
    if (d.getId() != -1) {
	    std::cout << "Adding information about the winner ..." << std::endl;
		GameInfoDB game_info_db(msql);
		GameInformation gi = game_info_db.create_game_info(d.getId(), 0, std::to_string(winner)); 
    }

    std::cout << "GameControler.cpp - Game creation ended, return values" << std::endl; 
    return d;
}
