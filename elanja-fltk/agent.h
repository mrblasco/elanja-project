#ifndef AGENT_H
#define AGENT_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"

typedef struct agent
{
	int x;
	int y;
	double capital;
	double prices[MAX_PRODUCTS];
	double needs[MAX_PRODUCTS];
	double trust[MAX_AGENTS];
	double affinity[MAX_AGENTS];
	double hue;
}agent_t;

void init_agent(agent_t * agent,int numProducts, int numAgents, int width, int height);

#endif
