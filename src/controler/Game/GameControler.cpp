#include "controler/Player/GameControler.h"

GameControler::GameControler(ConMySQL * msql) : msql(msql), db(PlayerDB(msql)) {
	;
}
