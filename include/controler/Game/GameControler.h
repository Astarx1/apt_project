#include "model/MySQLLink.h"
#include "model/Game/Game.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	Game create(int id_player_1, int id_player_2, std::string moves);
	Game create(int id_player_1, int id_player_2, std::string moves, int winner);
	
private:
	ConMySQL * msql; 
};
