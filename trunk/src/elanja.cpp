#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/model.h"
#include "../h/const.h"


using namespace std;

int main(int argc, char **argv)
{
     int t, i, j = 0;
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
		m.init(AGENTS, RHO, FEATURES,THRESHOLD, MAX_NUM_FRIENDS);

	} else if (argc == 6) {

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
	} 	else 	{

          printf(">>>>>>>>>>>>>>>>>>>>>>>>> E R R O R <<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
		printf("	- usage: ./main <n AGENTS> <n FEATURES> <n MAX NUM of FRIEND> <n THRESHOLD> <n RHO> <n NUMBER OF ITERACTION>\n");
		exit(0);
	}

	/* Text file for printing the matrices */
	FILE *out;
	FILE *out2;	
	FILE *out3;
	FILE *out4;	
	FILE *out5;
	out = fopen("AM.dat", "w");	
	out2 = fopen("single_node.dat", "w");
	out3 = fopen("alfa.dat", "w");
	out4 = fopen("degree.dat", "w");
	out5 = fopen("composition.dat", "w");
		
	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

     printf("age=%d \n rho = %f \n thrs = %f \n feat= %d\n friend =%d\n",m.agents,m.rho,m.threshold,m.nFeatures,m.friends);


	/* Number of cicles of the system */
 	for(t=0; t<1; t++)
	{
		/* Makes a model's step */
	     m.step();
         /* Print adjacency Matrix */
          for(i=0;i<m.agents;i++)
          {
               for(j=0;j<m.agents;j++)
               {
                    fprintf(out,"%f ",m.A[i*m.agents +j]);
               }               
               fprintf(out,"\n");               
          }
     }
	

	return 0;
}

