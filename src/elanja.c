#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"
#include "../h/matrices.h"   


int main()
{
        int i, j = 0;
	double k,v;
	double Bp_average,Bq_average;
	double *p = malloc(sizeof(double)*COLUMN);
	double *q = malloc(sizeof(double)*COLUMN);
	double *R = malloc(sizeof(double)*ROW*COLUMN);

	int *A = malloc(sizeof(int)*ROW*COLUMN);
	int *B = malloc(sizeof(int)*ROW*COLUMN);

	int *degree = malloc(sizeof(int)*ROW);
	int *A_degree = malloc(sizeof(int)*ROW);
	int *B_degree = malloc(sizeof(int)*ROW);

	/*double p[COLUMN];
	double q[COLUMN];
        double R[ROW][COLUMN];
        int A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];*/

	/* Text file for printing the matrices */
	FILE *out;	
	out = fopen("matrix.dat", "w");	
	/*out2 = fopen("pq.dat", "w");*/


	/* Initialize meeting probability vectors */
	for(i=0; i<COLUMN; i++)	
	{
		p[i] = 0.5; 
		q[i] = 0.5;
	}

	Bp_average = 0;
	Bq_average = 0;
	/* Number of cicles of the system */
 	for(i=0; i<NITER; i++)
	{
		interaction(p, q, A, R, degree, A_degree, B_degree);
		update(p, q, degree, A_degree, B_degree);
		for(j=0; j<COLUMN; j++)
		{ 
		Bp_average += p[j];				
		Bq_average += q[j];
		}		
		Bp_average = (double) Bp_average / (double) COLUMN; 
		Bq_average = (double) Bq_average / (double) COLUMN; 
		printf("p-Average %f\t", Bp_average);
		printf("q-Average %f\t", Bq_average);
		printf("\n");
		
	} 
	/* Adjacency matrix of nodes at distance d <= 2 */
	multiply(A, A, B);


	/*	printf("Extragroup Meeting Probability %f\n", (double) v / (double) COLUMN);*/

	for(i=0; i<COLUMN; i++)
	{
		if(p[i]==1)
			k += 1.0;
		if(q[i]==0)
			v += 1.0;
	}


	/*printf("Degree\n");
	for(i=0; i<COLUMN; i++)
	{
		printf("%d\n", degree[i]);
	} */

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

	/*fprintf(out, "Random Matrix\n");
	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%f\t\t", R[i][j]);
		}
		fprintf(out, "\n");
	}*/
return COLUMN;
}

