#include "model/Player/db_player.h"
#include "model/MySQLLink.h"

class PlayerControler {
public:
	PlayerControler(ConMySQL * msql);
	Player create();
	std::vector<Player> get();

private:
	PlayerDB db;	
	ConMySQL * msql;
};
