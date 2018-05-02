#ifndef PROBA_WIN_H
#define PROBA_WIN_H

#include "model/Player/Player.h"
#include "model/Game/Game.h"

#define MIN_STEP 0.1
#define STEP 1
#define OMEGA 1
#define STPI 2.506 

class PlayerLinkedToGame {
public:
	PlayerLinkedToGame();
	~PlayerLinkedToGame();

	std::vector<Game *> gs;
	std::vector<bool> f;
}


class ProbaWin {
public:
	ProbaWin();
	~ProbaWin();

private:
	std::vector<float> likelihood(PlayerLinkedToGame & p, float starting_value=1000, float starting_time=0);

	float compute_proba_victory (Game *);

	std::vector<PlayerLinkedToGame> ps;
	std::vector<Game> gs;
};