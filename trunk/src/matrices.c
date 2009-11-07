#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "../h/const.h"

void interaction(double *p, double *q, int *A, double *R, int *degree, int *A_degree, int *B_degree) {

	int i, j;
	
	/* Initialize matrices */
	for(i=0; i<ROW; i++)
        {
	   for(j=0; j<COLUMN; j++)
	   {
	        *(A+i+(j*sizeof(int))) = 0; // adjacency matrix
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
				*(R+i+(j*sizeof(double))) = 0;
			} else {
				*(R+i+(j*sizeof(double))) = (rand() %10001) / (double) 10000;
			}
	   	}
	}
	/* R is symmmetric */
	for(j=0; j<COLUMN; j++)
     	{
		for(i=j; i<ROW; i++)
		{
			*(R+i+(j*sizeof(double))) = *(R+j+(i*sizeof(double)));
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
				link = (double) *(R+i+(j*sizeof(double))) - *(p+i) * *(p+j);
			} else if (j > M  && i <= M ) 
			{
				link = (double) *(R+i+(j*sizeof(double))) - *(q+i)* *(p+j);
			} else if (j > M && i > M) 
			{
				link = (double) *(R+i+(j*sizeof(double))) - *(q+i) * *(q+j);	
			}
			if (link < 0) 
			{
				*(A+i+(j*sizeof(int))) = 1; 		 
			}	 
		}
	  }
	/* AM is symmmetric */
	for(j=0; j<COLUMN; j++)
    	{
		for(i=j; i<ROW; i++)
		{
			*(A+i+(j*sizeof(int))) = *(A+j+(i*sizeof(int)));
	   	}
     	}

	/* Degree vector*/ 
	for(i=0; i<ROW; i++)
     	{
		for(j=0; j<COLUMN; j++)
		{
			*(degree+i) += *(A+i+(j*sizeof(int)));
	   	}
     	}

	/* Degree of A-type agents vector*/ 
	for(i=0; i<ROW; i++)
     	{
		for(j=0; j<M; j++)
		{
			*(A_degree+i) += *(A+i+(j*sizeof(int)));
	   	}
		for(j=M; j<COLUMN; j++)
		{
			*(B_degree+i) += *(A+i+(j*sizeof(int)));
	   	}
     	}
}

void update(double *p, double *q, int *degree, int *A_degree, int *B_degree){

	int i;

	for(i=0; i<ROW; i++)
     	{
		if(*(degree+i) != 0)
		{
			*(p+i) = *(A_degree+i) / *(degree+i);
			*(q+i) = *(B_degree+i) / *(degree+i);
		}
		else
		{
			printf("Coglioni state dividendo per 0!!!!!\t");
		}
     	}
}

