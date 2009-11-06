#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "../h/matrices.h"

#define ROW 3 		/* Number of rows */
#define COLUMN 3		/* Number of columns */

using namespace std;

int main()
{
        int i, j = 0;
	double p[COLUMN];
	double q[COLUMN];
        double R[ROW][COLUMN];
        int A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];

	FILE *out;	/* File per vedere se vengono salvati alcuni ack che spedisce il monitor */
	out = fopen("pippo.txt", "w");


	/* Initialize meeting probability vectors */
	for(i=0; i<COLUMN; i++)
        {
	        p[i] = 0.5; 
		q[i] = 0.5;
        }

 	
	interaction(p, q, *A, *R, degree, A_degree, B_degree);


	for(i=0; i<4; i++)
	{
		fprintf(out, "0 ");
	}
	fprintf(out, "\t");
	
/*	/*Print results:

	fprintf(out, "Arrivato ack positivo pacchetto %d \n", *(int *)&buffTCPMonitor[1]);

	/* Print Adjacency matrix
       printf("Adjacency Matrix:\n");
        for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
		fprintf(out, "%d \n", A[i][j]);
	      printf("\t", A[i][j]);
	      cout << A[i][j];
	   }
	   printf("\n");
        }
	/* Print degrees 
	printf("    Degree, A-degree, B-degree:\n");
        for(i=0; i<ROW; i++)
        {
	   	printf("\t", degree[i]);
	     cout << degree[i];
		cout << "\t";
	     cout << A_degree[i];
		cout << "\t";
	     cout << B_degree[i];
		printf("\n");
	   }
*/
}

