#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/model.h"
#include "../h/const.h"

using namespace std;

int main(int argc, char **argv)
{
        int i, j = 0;
	int n_iter;

	/* Create an istance of model */
	model m;

	/* Set simulation variables */

	if(argc == 1)
	{
		printf("Using default parameters: \n");
		printf("	- agents 100\n");
		printf("	- features 5\n");
		printf("	- max number of friends 20\n");
		printf("	- threshold 0.20\n");
		printf("	- fraction of nodes with renewed features 0.10\n");
		
		/* Set number of iteration */
		n_iter = 200;
		/* Set model parameters */
		m.init(AGENTS,FEATURES,MAX_NUM_FRIENDS,THRESHOLD,RHO);
	}
	else if (argc == 4)
	{

		/* Set number of iteration */
		n_iter = atoi(argv[6]);
		/* Set model parameters */
		m.init(atoi(argv[1]),atoi(argv[5]),atoi(argv[2]),atoi(argv[4]),atoi(argv[3]));

		printf("Using parameters: \n");
		printf("	- agents %d\n", m.agents);
		printf("	- features %d", m.nFeatures);
		printf("	- max number of friends %d\n", m.friends);
		printf("	- threshold %f\n", m.threshold);
		printf("	- fraction of nodes with renewed features %f\n", m.rho);
	}
	else
	{
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>> E R R O R <<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
		printf("	- usage: ./main <n AGENTS> <n FEATURES> <n MAX NUM of FRIEND> <n THRESHOLD> <n RHO> <n NUMBER OF ITERACTION>\n");
		exit(0);
	}

	/* Text file for printing the matrices */
	FILE *out;
	FILE *out2;	
	FILE *out3;
	FILE *out4;	
	FILE *out5;
	out = fopen("matrix.dat", "w");	
	out2 = fopen("single_node.dat", "w");
	out3 = fopen("alfa.dat", "w");
	out4 = fopen("degree.dat", "w");
	out5 = fopen("composition.dat", "w");
		

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Number of cicles of the system */
 	for(i=0; i<n_iter; i++)
	{
		/* Makes a model's step */
		m.step();
	} 
	printf("\n \n \n ");
	printf("Dovrei aver fatto un sacco di raba ma non sono sicuro quindi dovete controllarmi inserendo i dati nei file!!! HAHHAHAHHAHAHHAHAHHAHAHHAHHAHAHAHHA \n");
		printf("\n \n \n ");

	

	return 0;
}

