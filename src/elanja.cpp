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
	out2 = fopen("Measures.dat", "w");
	out3 = fopen("alfa.dat", "w");
	out4 = fopen("degree.dat", "w");
	out5 = fopen("composition.dat", "w");
		
	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

     /* degree */
	double average_Knn[m.agents];

	/* Features Distribution*/
     double square_sum;
	double average_features[m.agents];
	double variance_features[m.agents];
	double AvAvFeatures[m.agents];
	double AvVarFeatures[m.agents];


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
/*
     STATISTICS TO BE PRINTED
*/
 
	/*  Average AvDegree first-neighbors vs degree */
 	for(i=0;i<m.agents;i++)
	{
		average_Knn[i] = 0;

		for(j=0;j<m.agents;j++)
		{
			if(m.A[i*m.agents+j] == 1)
			{
				average_Knn[i] += (double) m.degree[j];
			}
		}
		average_Knn[i] = average_Knn[i] / (double) m.degree[i];
	}

     /* Features Av e Var  */
	for(i=0;i<m.agents;i++)
	{
          average_features[i] = 0;
          variance_features[i] = 0;
          square_sum = 0;
		for(j=0;j<m.nFeatures;j++)
		{
			average_features[i] += m.features[j*m.agents + i];
               square_sum += pow(m.features[j*m.agents + i],2);
		}
          average_features[i] = average_features[i]  / (double) m.nFeatures;
          variance_features[i] =  (square_sum -  pow(average_features[i],2) )  / (double) (m.nFeatures - 1);
	}

     /* First Neighbors Features Av e Var  */
	for(i=0;i<m.agents;i++)
	{
		AvAvFeatures[i] = 0;
          AvVarFeatures[i] = 0;

		for(j=0;j<m.agents;j++)
		{
			if(m.A[i*m.agents+j] == 1)
			{
				AvAvFeatures[i] += average_features[j];
                    AvVarFeatures[i] += variance_features[j];
			}
		}
		AvAvFeatures[i] = AvAvFeatures[i] / (double) m.degree[i];
          AvVarFeatures[i] = AvVarFeatures[i] / (double) m.degree[i];
	}

     /* tvalue, number of potential friends for a given threshold.*/

     /*Print on files */ 
          for (i=0;i<m.agents;i++)
          {
               fprintf(out2,"%d %d %f %f %f %f %f\n",i,m.degree[i],average_Knn[i],average_features[i],variance_features[i],AvAvFeatures[i],AvVarFeatures[i]);
           
          }
     }	

	return 0;
}

