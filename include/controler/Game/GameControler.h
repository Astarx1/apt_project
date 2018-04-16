#include "model/MySQLLink.h"
#include "model/Game/Game.h"
#include "model/Game/db_game.h"

class GameControler {
public:
	GameControler(ConMySQL * msql);
	Game create();
	
private:
	ConMySQL * msql;
	GameDB db;
};
