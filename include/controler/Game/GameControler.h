#include "model/MySQLLink.h"
#include "model/Game/Game.h"
#include "model/Game/db_game.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	Game create(int id_player_1, int id_player_2, std::string moves);
	
private:
	ConMySQL * msql;
	GameDB db;
};
