#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

void interaction(int agents, int m, int distance, double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	double link;
	
	/* Initialize matrices */
	for(i=0; i<agents; i++)
        {
	   for(j=0; j<agents; j++)
	   {
	        *(A+(i*agents)+j) = 0; /* adjacency matrix */
	   }
        }

	/* Link formation*/
	/* R has random Upper-triangle and zeros on diagonal */
	for(i=0; i<agents; i++)
     	{
	   	for(j=i; j<agents; j++) 
	   	{
			if(i==j) 
			{
				/* -2 => zero on diagonal (+2 ones) */
				*(R+(i*agents)+j) = -2.0; 
			
			} else {
				*(R+(i*agents)+j) = (double) (rand() %10001) / 10000;
			}
	   	}
	}
	/* R is symmmetric */
	for(j=0; j<agents; j++)
     	{
		for(i=j; i<agents; i++)
		{
			*(R+(i*agents)+j) = *(R+(j*agents)+i);
		}
     	}

	/* Adjacency matrix */ 
	for(i=0; i<agents; i++)
	{
		for(j=i; j<agents; j++)
		{
			if(j < m && i < m ) 
			{	
				link = (double) *(R+(i*agents)+j) - (*(p+i) * *(p+j)); /* provare con il + */
			} else if (j >= m  && i < m ) 
			{
				link = (double) *(R+(i*agents)+j) - (*(q+i) * *(p+j) );  /*  provare con il + */

			} else if (j >= m && i >= m) 
			{		
				link = (double) *(R+(i*agents)+j) - ( *(q+i) * *(q+j) );	
			}
			if (link < 0) 
			{
				*(A+(i*agents)+j) = 1; 		 
			}	 
		}
	}
	/* Am is symmmetric */
	for(j=0; j<agents; j++)
    	{
		for(i=j; i<agents; i++)
		{
			*(A+(i*agents)+j) = *(A+(j*agents)+i);
	   	}
     	}

	/* Initialize degree, A_degree, B_degree vectors to 0 at each iteraction */
	for(i=0; i<agents; i++)
	{
		*(degree+i) = 0;
		*(A_degree+i) = 0;
		*(B_degree+i) = 0;
	}
}

void update(int agents, double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;

	/* Calculate the new p and q probabilities */
	/* It is a linear combination of "relative degree" and connection composition*/
	/* Relative degree: degree / total nodes number */

	for(i=0; i<agents; i++)
	{	
		if(*(degree+i) > 0)
		{	 
 			*(p+i) = 0.1 + (0.5 * (double)  *(A_degree + i) / *(degree + i)); 
			*(q+i) = 0.1 + (0.5 * (double) *(B_degree + i) / *(degree + i)); 
		}
	}	
}

void externalUpdate(int agents, int *A, double *p, double *q, double epsilon, int *degree){

	double random;
	int pos;
	int tmp, i, j;

	for(i=0; i<agents; i++)
	{

		if(*(degree+i) != 1)		
		{
			random = (double) (rand() %1000) / 1000;
			if(random < epsilon)
			{

				pos = (rand() %(*(degree+i) -1));
				tmp = 0; 
				for (j=0; j<agents; j++)
				{
					if (tmp != -1 && j != i && *(A+(i*agents)+j) == 1) 
					{	
								tmp++;
							if(tmp == pos)
							{
								*(p+i) = *(p+j);
								*(q+i) = *(q+j);
								tmp = -1;
							}

					}
				}
			}
		}
	}
}

