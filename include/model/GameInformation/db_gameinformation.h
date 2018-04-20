#ifndef DB_GAME_H
#define DB_GAME_H

#include <mutex>

#include "usual.h"
#include "model/MySQLLink.h"
#include "model/ExecuteResult.h"
#include "model/Game/Game.h"
#include "model/GameInformation/GameInformation.h"

class GameInfoDB {
public:
	static std::mutex mx;
	GameDB(ConMySQL * msql);

	std::vector<GameInformation> read_gameinfos_from_game_id(int id);
	GameInformation create_game_info(int id_game, int type, std::string value);
	GameInformation delete_game_infos_from_game_id(int id_game); 

private:
	ConMySQL * sql_link;
};

#endif