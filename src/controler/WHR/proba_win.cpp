#include "controler/WHR/proba_win.h"
#include <cmath>

void ProbaWin::running_algorithm() {
	running = true;	
	while(running) {
		update_pool_players();
		for (auto p: ps) {
			naive_max_log_implementation(p);
		}
	}	 
}

void ProbaWin::update_pool_players() {
	GameDB gdb(msql);
	GameInfoDB gidb(msql);
	PlayerDB pdb(msql);

	gs.clear();
	gs = gdb.read_games();
	
	std::vector<Player> tmpps = pdb.read_players();
	ps.clear();
	for (auto p: tmpps) {
		PlayerLinkedToGame tmp(p.getId());
		for (int i = 0; i < gs.size(); ++i) {
			std::vector<GameInformation> gis = gidb.read_gameinfos_from_game_id(gs[i].getId());
			for (auto gi: gis) { 
				if (gi.getType() == 0) {
					int winner = std::stoi(gi.getValue());			
					if(gs[i].getIdPlayer1() == p.getId()) {
						tmp.gs.push_back(&gs[i]);
						if (winner == 1)
							tmp.f.push_back(true);
						else
							tmp.f.push_back(false);
					} 
					if(gs[i].getIdPlayer2() == p.getId()) {
						tmp.gs.push_back(&gs[i]);
						if (winner == 1)
							tmp.f.push_back(false);
						else
							tmp.f.push_back(true);
					}
					break; 
				}
			}
		}
	}
}

void ProbaWin::naive_max_log_implementation(PlayerLinkedToGame & p) {
	LS l = likelihood(p);
	double lh = l.gl;
	double tmp_lh = lh + 1000;

	while (tmp_lh/lh > MIN_STEP) {
		tmp_lh = lh;
		for (int i = 1; i < p.gs.size(); ++i) {
			p.gs[i]->setLevelPlayer1(p.gs[i]->getLevelPlayer1() + l.d[i-1]*STEP);
		}
		l = likelihood(p);
	}
}

LS ProbaWin::likelihood(PlayerLinkedToGame & p) {
	LS r;
	for (int i=1; i < p.gs.size(); ++i) {
		DD d = compute_likehood_situation(	p.gs[i]->getLevelPlayer1(), p.gs[i]->getDateGame(), p.gs[i-1]->getLevelPlayer1(), p.gs[i-1]->getDateGame(),
											p.gs[i]->getLevelPlayer2(), p.f[i]);
		r.gl += d.value;
		r.d.push_back(d.derivative);
	}
	return r;
} 

DD ProbaWin::compute_likehood_situation(float r1, int t1, float r2, int t2, float ro, bool r1_winner) {
	DD dd1 = compute_log_proba_change(r1, t1, r2, t2);
	DD dd2;
	if (r1_winner) 
		dd2 = compute_log_proba_victory(r1, ro);
	else
		dd2 = compute_log_proba_victory(ro, r1);
	DD ret;
	ret.derivative = dd2.derivative + dd1.derivative;
	ret.value = dd2.value + dd1.value;
	return ret; 
}

DD ProbaWin::compute_log_proba_change(float l1, int t1, float l2, int t2) {
	DD ret;
	ret.derivative = (l2-l1)/OMEGA;
	ret.value = std::log10(1/(std::sqrt(abs(t2-t1))*OMEGA*STPI)) - ((l1-l2)*(l1-l2)/(2*(t2-t1)*OMEGA));

	return ret;
}

DD ProbaWin::compute_log_proba_victory (float l1, float l2) {
	DD ret;
	ret.derivative = 1/l1 - 1/(l1+l2);
	ret.value = log10(compute_proba_victory(l1, l2));
	return ret;
}

double ProbaWin::compute_proba_victory(float l1, float l2) {
	double p = 1 / (1+pow(10, 0 - (l1 - l2) / ELO_CONSTANTE));
	std::cout << "GameControler.cpp - Proba victory computed : " << p << std::endl; 
	return p;
}