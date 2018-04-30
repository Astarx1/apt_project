#ifndef DB_PLAYER_INFO_H
#define DB_PLAYER_INFO_H

#include <mutex>

#include "usual.h"
#include "model/MySQLLink.h"
#include "model/ExecuteResult.h"
#include "model/Player/Player.h"
#include "model/PlayerInformation/PlayerInformation.h"

/* 
Info types :
- 0 : Name
*/
class PlayerInfoDB {
public:
	static std::mutex mx;

	PlayerInfoDB(ConMySQL * msql);
	~PlayerInfoDB();

	std::vector<PlayerInformation> read_player_infos_from_player_id(int id);
	PlayerInformation create_player_info(int id_player, int type, std::string value);
	PlayerInformation delete_player_infos_from_player_id(int id_player); 
	void update_info_value_from_info_id(int id, std::string value);

private:
	ConMySQL * sql_link;
};

#endif