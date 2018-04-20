#include "model/MySQLLink.h"
#include "model/Game/Game.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	Game create(int id_player_1, int id_player_2, std::string moves);
	Game create(int id_player_1, int id_player_2, std::string moves, int winner);
	std::vector<Game> get();
	
private:
	double compute_proba_victory(int elo_1, int elo_2);
	void update_players(Player1 p1, Player2 p2, PlayerDB * pdb);
	ConMySQL * msql; 
};
