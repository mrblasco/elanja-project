#include "model.h"

model m; // istanza del modello
int t; // counter delle iterazioni
extern bool externAgentOn;
extern bool dinamicProductsOn;
extern int W,H;

void model::init(double lambda, double g_coef, double c_exp, int numAgents){
	int i;
	
	this->agents = agents;
	this->population = population;
	this->epsilon = epsilon;
	this->friendship = friendship;
	//this->dist_capital = new int[numAgents/2]; //(int *)malloc(sizeof(int)*(int)numAgents/2);
	
	t = 0;
}

void model::reinit(double agents, double population, double epsilon, int friendship){
	int i;
	
	this->friendship = friendship;
	this->agents = agents;

	
	//agente esterno
	//init_agent(&(this->externAgent),MAX_PRODUCTS, friendship, 560, 475);
	
	t = 0;
}

void model::step(){
	/* QUA DENTRO METTEREMO LE NOSTRE FUNZIONI INTERACTION E MULTIPLY */
}

double urand(){
	return (double)(rand()%RAND_MAX)/(double)RAND_MAX;
}


