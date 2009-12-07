#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h/const.h"
#include "../h/matrices.h"   


int main()
{
        int i, j = 0;
	double Bp_average,Bq_average;
	double alfa;
	double beta;


	double *p = malloc(sizeof(double)*COLUMN);
	double *q = malloc(sizeof(double)*COLUMN);
	double *R = malloc(sizeof(double)*ROW*COLUMN);

	int *A = malloc(sizeof(int)*ROW*COLUMN);
	int *B = malloc(sizeof(int)*ROW*COLUMN);

	int *degree = malloc(sizeof(int)*ROW);
	int *A_degree = malloc(sizeof(int)*ROW);
	int *B_degree = malloc(sizeof(int)*ROW);

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

	/* Initialize meeting probability vectors */
	for(i=0; i<COLUMN; i++)	
	{
		p[i] = 0.5; 
		q[i] = 0.5;
	}

	Bp_average = 0;
	Bq_average = 0;

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Number of cicles of the system */
 	for(i=0; i<NITER; i++)
	{
		interaction(p, q, A, R, degree, A_degree, B_degree);
		distance(A, A, B, degree, A_degree, B_degree, DISTANCE); 
 		update(p, q, degree, A_degree, B_degree);
		externalUpdate(A, p, q, EPSILON, degree);
		for(j=0; j<COLUMN; j++)
		{ 
			fprintf(out4,"%d\t",*(degree+j));
			fprintf(out5,"%f\t", (double) *(A_degree+j) / *(degree +j));
		}
		fprintf(out4,"\n");
		fprintf(out5,"\n");

		
		for(j=M/2; j<COLUMN; j++)
		{ 
			Bp_average += p[j];				
			Bq_average += q[j];
		}

		
		Bp_average = (double) Bp_average / COLUMN; 
		Bq_average = (double) Bq_average / COLUMN; 
		printf("p-Average %f\t", Bp_average);
		printf("q-Average %f\t", Bq_average);
		printf("\n");

		/* Computation of alfa at each time step */ 
		alfa = 0;
		beta = 0;
		for(j=0; j<COLUMN; j++)
		{
			if(*(B_degree+j)==0)
				beta++;

			if(*(A_degree+j)==0)
				alfa++;
		}

	/* Single node Behavior */
		fprintf(out2, "%d\t", *(A_degree + COLUMN/2));
		fprintf(out2, "%d\n", *(A_degree));

	/* Integration measure */
		fprintf(out3, "%f\t", alfa);
		fprintf(out3, "%f\n", beta);		
	} 

	/*	printf("Extragroup Meeting Probability %f\n", (double) v / (double) COLUMN);

	for(i=0; i<COLUMN; i++)
	{
		if(p[i]==1)
			k += 1.0;
		if(q[i]==0)
			v += 1.0;
	} */


	/*printf("Degree\n");
	for(i=0; i<COLUMN; i++)
	{
		printf("%d\n", degree[i]);
	}*/

	/* Print matrices */
	/*fprintf(out, "Adjacency Matrix\n"); */
	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%d\t", *(A+(i*COLUMN)+j));
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

	return COLUMN;
}

