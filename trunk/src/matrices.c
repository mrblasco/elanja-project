#include <stdio.h>
#include <stdlib.h>
#include "../h/const.h"

void interaction(double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	double link;
	
	/* Initialize matrices */
	for(i=0; i<COLUMN; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        *(A+(i*COLUMN)+j) = 0; /* adjacency matrix */
	   }
        }

	/* Link formation*/
	/* R has random Upper-triangle and zeros on diagonal */
	for(i=0; i<COLUMN; i++)
     	{
	   	for(j=i; j<COLUMN; j++) 
	   	{
			if(i==j) 
			{
				/* -2 => zero on diagonal (+2 ones) */
				*(R+(i*COLUMN)+j) = -2.0; 
			
			} else {
				*(R+(i*COLUMN)+j) = (double) (rand() %10001) / 10000;
			}
	   	}
	}
	/* R is symmmetric */
	for(j=0; j<COLUMN; j++)
     	{
		for(i=j; i<COLUMN; i++)
		{
			*(R+(i*COLUMN)+j) = *(R+(j*COLUMN)+i);
		}
     	}

	/* Adjacency Matrix */ 
	for(i=0; i<COLUMN; i++)
	{
		for(j=i; j<COLUMN; j++)
		{
			if(j < M && i < M ) 
			{	
				link = (double) *(R+(i*COLUMN)+j) - (*(p+i) * *(p+j)); /* provare con il + */
			} else if (j >= M  && i < M ) 
			{
				link = (double) *(R+(i*COLUMN)+j) - (*(q+i) * *(p+j) );  /*  provare con il + */

			} else if (j >= M && i >= M) 
			{		
				link = (double) *(R+(i*COLUMN)+j) - ( *(q+i) * *(q+j) );	
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
		for(i=j; i<COLUMN; i++)
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
}

void update(double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;
	int control;	

	/* Calculate the new p and q probabilities */
	/* It is a linear combination of "relative degree" and connection composition*/
	/* Relative degree: degree / total nodes number */
	control = 0;
	for(i=0; i<COLUMN; i++)
	{	
		if(*(degree+i) > 0)
		{	 
/*		control++; */
 			*(p+i) =  0.1 +  ( 0.1 * (double) *(A_degree + i) / *(degree + i)); 		
			*(q+i) =  0.1 +  ( 0.1 * (double) *(B_degree + i) / *(degree + i));
			/*printf("%f\t", *(p+i));
			printf("%f\n", *(q+i));*/

		}
/*		else 
		{

			*(p+i) *=  0.9;	
			*(q+i) *=  0.9;
			*(p+i) *=  (double) *(degree + i) / COLUMN;	
			*(q+i) *=  (double) *(degree + i) / COLUMN;
		}*/
		
	}	
	/*printf("%d\n",control);	*/

}

void externalUpdate(int *A, double *p, double *q, double epsilon, int *degree){

	double random;
	int pos;
	int tmp, i, j;

	for(i=0; i<COLUMN; i++)
	{

		if(*(degree+i) != 1)		
		{
			random = (double) (rand() %1000) / 1000;
			if(random < epsilon)
			{

				pos = (rand() %(*(degree+i) -1));
				tmp = 0; 
				for (j=0; j<COLUMN; j++)
				{
					if (tmp != -1 && j != i && *(A+(i*COLUMN)+j) == 1) /* -1 controllo che rompe il "for" successivo*/
					{	
						/*if(j != i)
						{
							if(*(A+(i*COLUMN)+j) == 1)*/
								tmp++;
							if(tmp == pos)
							{
								*(p+i) = *(p+j);
								*(q+i) = *(q+j);
								tmp = -1;
							}
						/*}*/
					}
				}
			}
		}
	}
}

