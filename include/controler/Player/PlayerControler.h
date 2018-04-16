#include "model/Player/db_player.h"
#include "model/MySQLLink.h"

class PlayerControler {
public:
	PlayerControler(ConMySQL * msql);
	Player create();
	Player read_from_id(int id);
	Player delete_from_id(int id);
	std::vector<Player> get();

private:
	PlayerDB db;	
	ConMySQL * msql;
};
