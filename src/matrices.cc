#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#define ROW 8 		/* Number of rows */
#define COLUMN 8		/* Number of columns */
#define M 4		/* Number of type A agents */

using namespace std;

int main() {
	int i, j = 0;
	double R[ROW][COLUMN];
	int A[ROW][COLUMN];
	int degree[ROW];
	int A_degree[ROW], B_degree[ROW];
	double p[ROW], q[ROW];
 
/* Initialize matrices */
	for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        R[i][j] = 0; // R random matrix
	        A[i][j] = 0; // adjacency matrix
	   }
        }
/* Initialize individual preference vectors */
	for(i=0; i<ROW; i++)
     {
		p[i] = .5; // vector of pref. towards a-type agents
		q[i] = .5; // vector of pref. towards b-type agents	
		degree[i] = 0;	
		A_degree[i] = 0;	
		B_degree[i] = 0;	
     } 


/* Link formation*/
/* R has random Upper-triangle and zeros on diagonal */
	for(i=0; i<ROW; i++)
     {
	   	for(j=i; j<COLUMN; j++) 
	   	{
			if(i==j) 
			{
				R[i][j] = 0;
			} else {
				R[i][j] = (rand() %10001) / (double) 10000;
			}
	   	}
	}
/* R is symmmetric */
	for(j=0; j<COLUMN; j++)
     {
		for(i=j; i<ROW; i++)
		{
			R[i][j] = R[j][i];
		}
     }

/* Adjacency Matrix */ 
	double link;
        for(i=0; i<ROW; i++)
        {
		for(j=i; j<COLUMN; j++)
		{
	   		if(j <= M && i <= M ) 
			{	
				link = (double) R[i][j] - p[i]*p[j];
			} else if (j > M  && i <= M ) 
			{
				link = (double) R[i][j] - q[i]*p[j];
			} else if (j > M && i > M) 
			{
				link = (double) R[i][j] - q[i]*q[j];	
			}
			if (link < 0) 
			{
				A[i][j] = 1; 		 
			}	 
		}
	  }
/* AM is symmmetric */
	for(j=0; j<COLUMN; j++)
     {
		for(i=j; i<ROW; i++)
		{
			A[i][j] = A[j][i];
	   	}
     }

/* Degree vector*/ 
	for(i=0; i<ROW; i++)
     {
		for(j=0; j<COLUMN; j++)
		{
			degree[i] += A[i][j];
	   	}
     }

/* Degree of A-type agents vector*/ 
	for(i=0; i<ROW; i++)
     {
		for(j=0; j<M; j++)
		{
			A_degree[i] += A[i][j];
	   	}
		for(j=M; j<COLUMN; j++)
		{
			B_degree[i] += A[i][j];
	   	}
     }


/*Print results:*/

/* Print Adjacency matrix*/
       printf("Adjacency Matrix:\n");
        for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	      printf("\t", A[i][j]);
	      cout << A[i][j];
	   }
	   printf("\n");
        }
/* Print degrees */
printf("Degree, A-degree, B-degree:\n");
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
}



