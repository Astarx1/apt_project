#include "controler/Game/GameControler.h"

GameControler::GameControler(ConMySQL * msql) : msql(msql), db(GameDB(msql)) {
	;
}
