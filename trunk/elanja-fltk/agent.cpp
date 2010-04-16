#include "agent.h"

void init_agent(agent_t * agent,int numProducts, int numAgents, int width, int height)
{
	int i;
	double need, tot_needs;
	
	agent->x=rand()%width;
	agent->y=rand()%height;
	//this->x=((int)((double)width/2.0))+((rand()%3)-1);
	//this->y=((int)((double)height/2.0))+((rand()%3)-1);
	
	agent->capital=INIT_CAPITAL;
	agent->hue=(double)rand()/(double)RAND_MAX;
	
	//agent->prices=new double[MAX_PRODUCTS];
	for(i=0;i<numProducts;i++){
		agent->prices[i] = (double)(rand()%RAND_MAX)/RAND_MAX;
	}
	
	//agent->needs=new double[MAX_PRODUCTS];
	for(i=0;i<numProducts;i++){
		need = (double)(rand()%RAND_MAX)/RAND_MAX;
		agent->needs[i] = need;
	}
	
	//this->trust=new double[numAgents];
	for(i=0;i<numAgents;i++){
		agent->trust[i] = 0.0;
	}

	//this->affinity=new double[numAgents];
	for(i=0;i<numAgents;i++){
		agent->affinity[i] = 0.0;
	}
}

