#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#define ROW 8 		/* Number of rows */
#define COLUMN 8		/* Number of columns */
#define M 4		/* Number of type A agents */

using namespace std;

void interaction(double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	
/* Initialize matrices */
	for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        A[i][j] = 0; // adjacency matrix
	   }
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
}

void update((double) *p, (double) *q, (int) *degree, (int) *A_degree, (int) *B_degree){

	int i, j;

	for(i=0; i<ROW; i++)
     	{
		if(degree[i] != 0)
		{
			p[i] = A_degree[i] / degree[i];
			q[i] = B_degree[i] / degree[i];
		}
		else
		{
			printf("Coglioni state dividendo per 0!!!!!\t");
		}
     	}
}

