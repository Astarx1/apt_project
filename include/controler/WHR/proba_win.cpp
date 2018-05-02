#include "controler/WRH/proba_win.h"
#include <cmath>

typedef struct likelihood_situation {
	std::vector<double> d;
	double gl;
} LS;

typedef struct double_double {
	double derivative;
	double value;
} DD;

double naive_max_log_implementation(PlayerLinkedToGame & p) {
	LS l = likelihood(p);
	double lh = l.gl;
	double tmp_lh = likelihood + 1000;

	while (tmp_lh/lh > MIN_STEP) {
		for (int i = 1; i < p.gs.size(); ++i) {
			p.gs[i].setLevelPlayer1(p.gs[i].getLevelPlayer1() + l.d[i-1]*STEP);
		}
		l = likelihood(p);
	}
}

LS likelihood(PlayerLinkedToGame & p) {
	LS r;
	for (int i=1; i < p.gs.size(); ++i) {
		if (p.f[1]) { 
			DD d = compute_likehood_situation(p.gs[i].getLevelPlayer1(), p.gs[i].getDateGame(), p.gs[i-1].getLevelPlayer1(), p.gs[i-1].getDateGame(), p.gs[i].getLevelPlayer2())
			r.gl += d.value;
			r.d.push_back(d.derivative);
		}  
	}
	return r;
} 

DD compute_likehood_situation(float r1, int t1, float r2, int t2, float ro) {
	DD dd1 = compute_log_proba_change(r1, t1, r2, t2);
	DD dd2 = compute_log_proba_victory(r1, ro);
	DD ret;
	ret.derivative = dd2.derivative + dd1.derivative;
	ret.value = dd2.value + dd1.value;
	return ret; 
}

// Compute the probability of having such elo change during this time (r1(t1)-r2(t2) ~ N(0, omega))
DD compute_log_proba_change(float l1, int t1, float l2, int t2) {
	DD ret;
	ret.derivative = (l2-l1)/OMEGA;
	ret.value = std::log10(1/(std::sqrt(abs(t2-t1))*OMEGA*STPI)) - ((l1-l2)*(l1-l2)/(2*(t2-t1)*OMEGA));

	return ret;
}

// Compute the Elo equation
DD compute_log_proba_victory (float l1, float l2) {
	DD ret;
	ret.derivative = 1/l1 - 1/(l1+l2);
	ret.value = log10(compute_proba_victory(float l1, l2));
	return ret;
}

double compute_proba_victory(float l1, l2) {
	double p = 1 / (1+pow(10, 0 - (elo_1 - elo_2) / ELO_CONSTANTE));
	std::cout << "GameControler.cpp - Proba victory computed : " << p << std::endl; 
	return p;
}