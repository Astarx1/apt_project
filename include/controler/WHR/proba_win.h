#ifndef PROBA_WIN_H
#define PROBA_WIN_H

#include "model/Player/Player.h"
#include "model/Player/db_player.h"

#include "model/Game/Game.h"
#include "model/Game/db_game.h"

#include "model/GameInformation/GameInformation.h"
#include "model/GameInformation/db_gameinformation.h"

#include "model/MySQLLink.h"
#include "model/ExecuteResult.h"

#define MIN_STEP 0.1
#define STEP 1
#define OMEGA 1
#define STPI 2.506 
#define ELO_CONSTANTE 400 

typedef struct likelihood_situation {
	std::vector<double> d;
	double gl;
} LS;

typedef struct double_double {
	double derivative;
	double value;
} DD;

class PlayerLinkedToGame {
public:
	PlayerLinkedToGame(int id) : id(id) {}
	~PlayerLinkedToGame() {}

	void update_player();

	std::vector<Game *> gs;
	std::vector<bool> f;
	int id;
};


class ProbaWin {
public:
	ProbaWin(ConMySQL * msql) : msql(msql), running(false) {}
	~ProbaWin() {}

	void update_pool_players();
	void running_algorithm(int round=-1);

private:
	ConMySQL * msql;
	bool running;

	void naive_max_log_implementation(PlayerLinkedToGame & p);

	LS likelihood(PlayerLinkedToGame & p);
	DD compute_likehood_situation(float r1, int t1, float r2, int t2, float ro, bool r1_winner);

	DD compute_log_proba_change(float l1, int t1, float l2, int t2);
	DD compute_log_proba_victory (float l1, float l2);
	double compute_proba_victory(float l1, float l2);

	std::vector<PlayerLinkedToGame> ps;
	std::vector<Game> gs;
};

#endif