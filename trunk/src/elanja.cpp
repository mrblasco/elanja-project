#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/multiply.h"
#include "../h/const.h"
#include "../h/matrices.h"   

using namespace std;

int main(int argc, char **argv)
{
        int i, j = 0;
	double Bp_average,Bq_average;
	double alfa;
	double beta;
	double measure;

	/* Default values */

	int agents = 100; 	/* Number of agents of the system */
	int n_iter = 50;		/* Number of iteractions */
	int distance = 1;	/* Distance of Neighborhood */
	int m = 50;		/* Number of agents of each type */
	int graphic = 0;	/* Graphic flag */

	/* Set simulation variables */

	if(argc == 1)
	{
		printf("Using default parameters: \n");
		printf("	- agents 100\n");
		printf("	- number of iteraction 50\n");
		printf("	- distance of neighborhood 1\n");
		printf("	- number of agents of each type 50\n");
	}
	else if (argc == 4)
	{
		agents = atoi(argv[1]);
		n_iter = atoi(argv[2]);
		distance = atoi(argv[3]);
		m = agents/2;

		printf("Using parameters: \n");
		printf("	- agents %d\n", agents);
		printf("	- number of iteraction %d\n", n_iter);
		printf("	- distance of neighborhood %d\n", distance);
		printf("	- number of agents of each type %d\n", m);
	}
	else
	{
		printf(">>>>>>>>>>>> E R R O R <<<<<<<<<<< \n");
		printf("	- usage: ./elanja <n AGENTS> <n ITERACTION> <distance NEIGHBORHOOD>\n");
		exit(0);
	}
	

	double *p = (double*) malloc ((sizeof(double))*agents);
	double *q = (double*) malloc(sizeof(double)*agents);
	double *R = (double*) malloc(sizeof(double)*agents*agents);

	int *A = (int*) malloc(sizeof(int)*agents*agents);
	int *B = (int*) malloc(sizeof(int)*agents*agents);

	int *degree = (int*) malloc(sizeof(int)*agents);
	int *A_degree = (int*) malloc(sizeof(int)*agents);
	int *B_degree = (int*) malloc(sizeof(int)*agents);

	/* Text file for printing the matrices */
	FILE *out;
	FILE *out_1;
	FILE *out2;	
	FILE *out3;
	FILE *out4;	
	FILE *out5;
	out = fopen("matrix.dat", "w");	
	out_1 = fopen("degree1.dat", "w");
	out2 = fopen("single_node.dat", "w");
	out3 = fopen("alfa.dat", "w");
	out4 = fopen("degree.dat", "w");
	out5 = fopen("composition.dat", "w");
		
	/* Initialize meeting probability vectors */
	for(i=0; i<agents; i++)	
	{
		p[i] = 0.0; 
		q[i] = 0.0;
	}

	Bp_average = 0;
	Bq_average = 0;

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Number of cicles of the system */
 	for(i=0; i<n_iter; i++)
	{
		interaction(agents, m, distance, p, q, A, R, degree, A_degree, B_degree);
 		multiplyer(agents, m, distance, A, A, B, degree, A_degree, B_degree, distance, out_1); 
 		update(agents, p, q, degree, A_degree, B_degree);
	    /*  externalUpdate(agents, A, p, q, EPSILON, degree);*/
		
		alfa = 0;
		beta = 0;

		for(j=0; j<agents; j++)
		{ 
			/* Composition */
			fprintf(out4,"%d\t",*(degree+j));
			fprintf(out5,"%f\t", (double) *(A_degree+j) / *(degree +j));
			
			/* Necessary for integration measure */
			measure = *(degree+j) * T;	
			if(*(B_degree+j) < measure)
				beta++;

			if(*(A_degree+j)< measure)
				alfa++;

			/* Record each node's behavior */
			fprintf(out2, "%d\t", *(degree+j));

		}
		
		/* Integration measure */
		fprintf(out3, "%f\t", (2 * alfa / agents));
		fprintf(out3, "%f\n", (2 * beta / agents));		

		fprintf(out2,"\n");
		fprintf(out4,"\n");
		fprintf(out5,"\n");

		
		for(j=m/2; j<agents; j++)
		{ 
			Bp_average += p[j];				
			Bq_average += q[j];
		}

	
		Bp_average = (double) Bp_average / agents; 
		Bq_average = (double) Bq_average / agents; 
		printf("p-Average %f\t", Bp_average);
		printf("q-Average %f\t", Bq_average);
		printf("\n");

	} 

	/* Print matrices */
	for(i=0; i<agents; i++)
	{
		for(j=0; j<agents; j++)
		{
			fprintf(out, "%d\t", *(A+(i*agents)+j));
		}
		fprintf(out, "\n\n");
	}

	fprintf(out, "\n");

	free(p);
	free(q);
	free(R);
	free(A);
	free(B);
	free(degree);
	free(A_degree);
	free(B_degree);

	return agents;
}

