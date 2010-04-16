#ifndef MODEL_H
#define MODEL_H

#include "agent.h"
#include "elanja-fltk.h"
#include "const.h"
#include <iostream>

class model{
public:
	void init(double lambda, double g_coef, double c_exp, int numAgents);
	void reinit(double lambda, double g_coef, double c_exp, int numAgents);
	void step();
	
	double agents;
	double population;
	double epsilon;
	
	int friendship;
	
	agent_t externAgent;
	int dist_capital[MAX_AGENTS];

	double tot_capital;
	double max_capital;
	double compute_price_variance(int i);
};

double urand();

#endif
