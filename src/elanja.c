#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "../h/const.h"
#include "../h/matrices.h"

int main()
{
        int i, j = 0;
	double p[COLUMN];
	double q[COLUMN];
        double R[ROW][COLUMN];
        int A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];

	/* Text file for printing the matrices */
	FILE *out;	
	out = fopen("pippo.txt", "w");


	/* Initialize meeting probability vectors */
	for(i=0; i<COLUMN; i++)
        {
	        p[i] = 0.5; 
		q[i] = 0.5;
        }


	/* Number of cicles of the system */
 	for(i=0; i<NITER; i++)
	{
		interaction(p, q, *A, *R, degree, A_degree, B_degree);
		update(p, q, degree, A_degree, B_degree);
	}


	/* Print matrices */
	fprintf(out, "Adjacency Matrix\n");
	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%d\t\t", A[i][j]);
		}
		fprintf(out, "\n");
	}

	fprintf(out, "\n");

	fprintf(out, "Random Matrix\n");
	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%f\t\t", R[i][j]);
		}
		fprintf(out, "\n");
	}
}

