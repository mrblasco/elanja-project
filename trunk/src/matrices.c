#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

void interaction(double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	double link;
	
	/* Initialize matrices */
	for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        *(A+(i*COLUMN)+j) = 0; /* adjacency matrix */
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
				/* -2 => zero on diagonal (+2 ones) */
				*(R+(i*COLUMN)+j) = -2.0; 
			
			} else {
				*(R+(i*COLUMN)+j) = (rand() %10001) / (double) 10000;
			}
	   	}
	}
	/* R is symmmetric */
	for(j=0; j<COLUMN; j++)
     	{
		for(i=j; i<ROW; i++)
		{
			*(R+(i*COLUMN)+j) = *(R+(j*COLUMN)+i);
		}
     	}

	/* Adjacency Matrix */ 
        for(i=0; i<ROW; i++)
        {
		for(j=i; j<COLUMN; j++)
		{
	   		if(j < M && i < M ) 
			{	
				link = (double) *(R+(i*COLUMN)+j) - *(p+i) * *(p+j);
				/*printf("Posizione %d %d = %f; dato da %f %f \n", i, j, link, *(p+i), *(p+j));*/
			} else if (j >= M  && i < M ) 
			{
				link = (double) *(R+(i*COLUMN)+j) - *(q+i)* *(p+j);
				/*printf("Posizione %d %d = %f; dato da %f %f \n", i, j, link, *(q+i), *(p+j));*/
			} else if (j >= M && i >= M) 
			{
				link = (double) *(R+(i*COLUMN)+j) - *(q+i) * *(q+j);	
				/*printf("Posizione %d %d = %f; dato da %f %f \n", i, j, link, *(q+i), *(q+j));*/
			}
			if (link < 0) 
			{
				*(A+(i*COLUMN)+j) = 1; 		 
			}	 
		}
	  }
	/* AM is symmmetric */
	for(j=0; j<COLUMN; j++)
    	{
		for(i=j; i<ROW; i++)
		{
			*(A+(i*COLUMN)+j) = *(A+(j*COLUMN)+i);
	   	}
     	}

	/* Initialize degree, A_degree, B_degree vectors to 0 at each iteraction */
	for(i=0; i<COLUMN; i++)
	{
		*(degree+i) = 0;
		*(A_degree+i) = 0;
		*(B_degree+i) = 0;
	}

	/* Degree vector*/ 
	for(i=0; i<ROW; i++)
     	{
		for(j=0; j<COLUMN; j++)
		{
			*(degree+i) += *(A+(i*COLUMN)+j);
	   	}
     	}

	/* Degree of A-type agents vector*/ 
	for(i=0; i<ROW; i++)
     	{
		for(j=0; j<M; j++)
		{
			*(A_degree+i) += *(A+(i*COLUMN)+j);
	   	}
		for(j=M; j<COLUMN; j++)
		{
			*(B_degree+i) += *(A+(i*COLUMN)+j);
	   	}
     	}
}

void update(double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;

	/* Calculate the new p and q probabilities */
	/* It is a linear combination of "relative degree" and connection composition*/
	/* Relative degree: degree / total nodes number */
	
	for(i=0; i<COLUMN; i++)
     	{
		if(*(degree+i) != 0)
		{	
			*(p+i) = 0.01 + 0.3 * (double) *(degree+i) / (double) COLUMN +  (double) *(A_degree+i) / (double) COLUMN;
			*(q+i) = 0.01 + 0.3 * (double) *(degree+i) / (double) COLUMN +  (double) *(B_degree+i) / (double) COLUMN;
			/*if (*(p+i)==0) 
				*(p+i) = 0.5;
			if (*(q+i)==0)		
				*(q+i) = 0.5;*/			
		}
		else
		{
			printf("Divided by zero!!!!\t");
		}
     	}
}

