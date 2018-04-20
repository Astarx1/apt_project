#include "model/MySQLLink.h"
#include "model/Game/Game.h"
#include "model/Player/Player.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	Game create(int id_player_1, int id_player_2, std::string moves);
	Game create(int id_player_1, int id_player_2, std::string moves, int winner);
	std::vector<Game> get();
	
private:
	double compute_proba_victory(float elo_1, float elo_2);
	void update_players(Player p1, Player p2, int winner);
	ConMySQL * msql; 
};
