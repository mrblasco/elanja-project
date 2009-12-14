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
	double measure;


	double *p = malloc(sizeof(double)*COLUMN);
	double *q = malloc(sizeof(double)*COLUMN);
	double *R = malloc(sizeof(double)*COLUMN*COLUMN);

	int *A = malloc(sizeof(int)*COLUMN*COLUMN);
	int *B = malloc(sizeof(int)*COLUMN*COLUMN);

	int *degree = malloc(sizeof(int)*COLUMN);
	int *A_degree = malloc(sizeof(int)*COLUMN);
	int *B_degree = malloc(sizeof(int)*COLUMN);

	int *degree2 = malloc(sizeof(int)*COLUMN);
	int *A_degree2 = malloc(sizeof(int)*COLUMN);
	int *B_degree2 = malloc(sizeof(int)*COLUMN);

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
	for(i=0; i<COLUMN; i++)	
	{
		p[i] = 0.0; 
		q[i] = 0.0;
	}

	Bp_average = 0;
	Bq_average = 0;

	/* Initialize random number generator's seed to the current time */
	srand(time(NULL));

	/* Number of cicles of the system */
 	for(i=0; i<NITER; i++)
	{
		interaction(p, q, A, R, degree, A_degree, B_degree);
 		distance(A, A, B, degree, A_degree, B_degree, DISTANCE, out_1); 
 		update(p, q, degree, A_degree, B_degree);
		externalUpdate(A, p, q, EPSILON, degree);
	

		/*****************************/
	
		/* printing */
		
		alfa = 0;
		beta = 0;

		for(j=0; j<COLUMN; j++)
		{ 
			/* Composition */
			fprintf(out4,"%d\t",*(degree+j));
			fprintf(out5,"%f\t", (double) *(A_degree+j) / *(degree +j));
			
			/* necessary for integration measure */
			measure = *(degree+j) * T;	
			if(*(B_degree+j) < measure)
				beta++;

			if(*(A_degree+j)< measure)
				alfa++;

			/* Record each node's behavior */
			/*fprintf(out2, "%d\t", *(A_degree + j));*/
			fprintf(out2, "%d\t", *(degree+j));

		}
		
		/* Integration measure */
		fprintf(out3, "%f\t", (2 * alfa / COLUMN));
		fprintf(out3, "%f\n", (2 * beta / COLUMN));		

		fprintf(out2,"\n");
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

	} 


	/* Print matrices */
	/*fprintf(out, "Adjacency Matrix\n"); */
	for(i=0; i<COLUMN; i++)
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

