#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/model.h"
#include "../h/const.h"


using namespace std;

int main(int argc, char **argv)
{

	/* Create an istance of model */
	model m;

	/* Various index for loops */ 
	int i,j,n,a,b,t,f,s; 

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Set simulation variables */
	if(argc == 1)
	{
		printf("Using default parameters: \n");
		printf("	- linear edge agents %d\n", EDGE_AGENTS);
		printf("	- agents %d\n",AGENTS);
		printf("	- features %d\n",NFEATURES);
		printf("	- number of possible values for any feature %d\n",POS_FEATURES);
		printf("	- number of iterations %d\n", N_ITER);
		printf("	- degree %d\n", OUTDEGREE);
		printf("	- delta %f\n", DELTA);
		printf("	- maxSide %d\n", MAXSIDE);

		/* Set model parameters */
		m.init(EDGE_AGENTS, AGENTS, NFEATURES, POS_FEATURES, N_ITER, OUTDEGREE, DELTA, MAXSIDE);

	} else if (argc == 8) {

		/* Set model parameters */
		m.init(atoi(argv[1]),atoi(argv[1])*atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),atoi(argv[6]),atoi(argv[7]));

		printf("Using parameters: \n");
		printf("	- linear edge agents %d\n", m.edge_agents);
		printf("	- agents %d\n", m.agents);
		printf("	- features %d\n", m.nFeatures);
		printf("	- number of possible values for any feature %d\n", m.pos_features);
		printf("	- number of iterations %d\n", m.n_iter);
		printf("	- degree %d\n", m.outdegree);
		printf("	- delta %f\n", m.delta);
		printf("	- maxSide %d\n", m.maxSide);

	} 	else 	{

          printf(">>>>>>>>>>>>>>>>>>>>>>>>> E R R O R <<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
		printf("	- usage: ./main <n LINEAR EDGE AGENTS> <n NUMBER of FEATURES> <n POSSIBLE FEATURES> <n NUMBER OF ITERACTION> <DEGREE> <DELTA> <MAXSIDE> <RANDOM>\n");
		exit(0);
	}

	
     m.step();

}

