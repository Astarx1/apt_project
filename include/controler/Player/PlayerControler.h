#include "model/Player/db_player.h"
#include "model/MySQLLink.h"

class PlayerControler {
public:
	PlayerControler(ConMySQL * msql) : msql(msql), db(PlayerDB(msql)) {
		;
	}

	Player create() {
		return db.create_player();		
	}

private:
	PlayerDB db;	
	ConMySQL * msql;
};
