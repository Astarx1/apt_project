#include "controler/Game/GameControler.h"

#include "model/Game/db_game.h"
#include "model/GameInformation/db_gameinformation.h"
#include "model/Player/db_player.h"

#include <ctime>
#include <math.h>

#define CHANGE_CONSTANTE 10.0
#define ELO_CONSTANTE 400.0

GameControler::GameControler(ConMySQL * msql) : msql(msql) {
	;
}


std::vector<Game> GameControler::get() {
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
	    std::cout << "GameControler.cpp - Adding information about the winner ..." << std::endl;
		GameInfoDB game_info_db(msql);
		GameInformation gi = game_info_db.create_game_info(d.getId(), 0, std::to_string(winner)); 
	    std::cout << "GameControler.cpp - Updating players ..." << std::endl;
	    update_players(p1, p2, winner);
    }

    std::cout << "GameControler.cpp - Game creation ended, return values" << std::endl; 
    return d;
}

Game GameControler::delete_from_id(int id) {
	std::cout << "GameControler.cpp - deleting the game " << id << std::endl; 
    GameDB game_db(msql);
    GameInfoDB game_info_db(msql);
    game_info_db.delete_game_infos_from_game_id(id);
	Game d = game_db.delete_game_from_game_id(id);
	std::cout << "GameControler.cpp - Game deletion ended, return values" << std::endl; 
    return d;
}





double GameControler::compute_proba_victory(float elo_1, float elo_2) {
	double p = 1 / (1+pow(10, 0 - (elo_1 - elo_2) / ELO_CONSTANTE));
	std::cout << "GameControler.cpp - Proba victory computed : " << p << std::endl; 
	return p;
}

void GameControler::update_players(Player p1, Player p2, int winner) {
	PlayerDB pdb(msql);

	double lp1 = p1.getLevel();
	double lp2 = p2.getLevel();

	std::cout << "Update player infos : " << p1.getLevel() << " vs " << p2.getLevel() << std::endl;
	if (winner == 1) { 
		p1.setLevel(lp1 + CHANGE_CONSTANTE * (1 - compute_proba_victory(lp1, lp2)));
		p2.setLevel(lp2 + CHANGE_CONSTANTE * (0 - compute_proba_victory(lp2, lp1))); 
	}
	else {
		p1.setLevel(p1.getLevel() + CHANGE_CONSTANTE * (0 - compute_proba_victory(lp1, lp2)));
		p2.setLevel(p2.getLevel() + CHANGE_CONSTANTE * (1 - compute_proba_victory(lp2, lp1))); 
	}
	std::cout << "Update player infos : " << p1.getLevel() << " vs " << p2.getLevel() << std::endl;

	pdb.update_player(p1);
	pdb.update_player(p2);
}
