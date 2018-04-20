#include "model/MySQLLink.h"
#include "model/Game/Game.h"
#include "model/Player/Player.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	std::vector<Game> get();
	Game create(int id_player_1, int id_player_2, std::string moves);
	Game create(int id_player_1, int id_player_2, std::string moves, int winner);
	Game delete_from_id(int id);
	
private:
	double compute_proba_victory(float elo_1, float elo_2);
	void update_players(Player p1, Player p2, int winner);
	ConMySQL * msql; 
};
