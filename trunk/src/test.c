#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "../h/const.h"
#include "../h/util.h"

int main(){

        int i, j;
	double p[COLUMN];
	double q[COLUMN];
        double R[ROW][COLUMN];
        double A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];

	/* Text file for printing the matrices */
	FILE *out;	
	out = fopen("prova.txt", "w");


	p[1] = 34.1;
	p[2] = 34.1;
	p[3] = 34.1;
	
	intraction(p, q, *A, *R, degree, A_degree, B_degree);

	for(i=0; i<COLUMN; i++)
	{
		fprintf(out, "%f\t", p[i]);
	}
	fprintf(out, "\n\n");

	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%f\t\t", A[i][j]);
		}
		fprintf(out, "\n");
	}

	/*fprintf(out, "\n\n");

	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%d\t\t", R[i][j]);
		}
		fprintf(out, "\n");
	}*/
	return 0;
}
