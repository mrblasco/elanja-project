#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"
#include "../h/util.h"

int main(){

	printf("arrivo qua!!!");

        int i, j;
	int p[COLUMN];
	int q[COLUMN];
        int R[ROW][COLUMN];
        int A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];

	/* Text file for printing the matrices */
	FILE *out;	
	out = fopen("prova.txt", "w");

	printf("arrivo qua!!!");	

	intraction(p, q, *A, *R, degree, A_degree, B_degree);

	for(i=0; i<ROW; i++)
	{
		for(j=0; j<COLUMN; j++)
		{
			fprintf(out, "%d\t\t", A[i][j]);
		}
		fprintf(out, "\n");
	}

	return 0;
}
